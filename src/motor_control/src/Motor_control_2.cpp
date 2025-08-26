/**
 * @file Motor_control.cpp
 * @brief ROS2 узел для управления моторами через SPI интерфейс
 *
 * @details
 * Реализует взаимодействие между ROS2 и аппаратным обеспечением через SPI.
 * Обеспечивает:
 * - Прием команд управления моторами из ROS2 топиков
 * - Передачу данных на контроллер двигателей через SPI
 * - Прием данных с IMU и энкодеров двигателей
 * - Публикацию состояний двигателей и IMU данных
 * - Визуализацию в RViz через JointState
 */

#include <memory>
#include <atomic>
#include <functional>
#include <chrono>
#include <mutex>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/bool.hpp"
// tinker_msgs messages
#include "tinker_msgs/msg/control_cmd.hpp"
#include "tinker_msgs/msg/imu_state.hpp"
#include "tinker_msgs/msg/low_cmd.hpp"
#include "tinker_msgs/msg/low_state.hpp"
#include "tinker_msgs/msg/motor_cmd.hpp"
#include "tinker_msgs/msg/motor_state.hpp"
#include "tinker_msgs/msg/one_motor_cmd.hpp"
#include "tinker_msgs/srv/motor_list.hpp"
#include "sensor_msgs/msg/joint_state.hpp"

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include "comm.h"
#include "spi_node.h"
#include "spi.h"
#include "sys_time.h"
#include <pthread.h>
#include <signal.h>
#include <errno.h>

#define SPI_TEST 0
#define USE_USB 0
#define USE_SERIAL 0
#define EN_SPI_BIG 1
#define CAN_LINK_COMM_VER1 0
#define CAN_LINK_COMM_VER2 1

#if EN_SPI_BIG
#if CAN_LINK_COMM_VER1
#define SPI_SEND_MAX 85
#else
#define SPI_SEND_MAX 160 // 120 + 20 + 20
#endif
#else
#define SPI_SEND_MAX 40
#endif

#define EN_MULTI_THREAD 1
#define NO_THREAD 0
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define MEM_SPI 0001
#define MEM_SIZE 2048

#if NO_THREAD && !EN_MULTI_THREAD
static uint32_t speed = 150000 * 4;
#define DELAY_SPI 250
#else
static uint32_t speed = 20000000;
#define DELAY_SPI 250
#endif

float spi_loss_cnt = 0;
int spi_connect = 0;
float mems_usb_loss_cnt = 0;
int mems_usb_connect = 0;

using namespace std;

// Глобальные буферы SPI (остаются, т.к. используются в низкоуровневом SPI)
uint8_t spi_tx_buf[SPI_BUF_SIZE] = {0};
uint8_t spi_rx_buf[SPI_BUF_SIZE] = {0};
int spi_tx_cnt_show = 0;
int spi_tx_cnt = 0;

uint8_t usb_tx_buf[SPI_BUF_SIZE] = {0};
uint8_t usb_rx_buf[SPI_BUF_SIZE] = {0};
int usb_tx_cnt = 0;
int usb_rx_cnt = 0;

uint8_t tx[SPI_BUF_SIZE] = {};
uint8_t rx[ARRAY_SIZE(tx)] = {};

// Вспомогательные функции сериализации (без изменений)
static void setDataInt_spi(int i)
{
    spi_tx_buf[spi_tx_cnt++] = ((i << 24) >> 24);
    spi_tx_buf[spi_tx_cnt++] = ((i << 16) >> 24);
    spi_tx_buf[spi_tx_cnt++] = ((i << 8) >> 24);
    spi_tx_buf[spi_tx_cnt++] = (i >> 24);
}

static void setDataFloat_spi(float f)
{
    int i = *(int *)&f;
    spi_tx_buf[spi_tx_cnt++] = ((i << 24) >> 24);
    spi_tx_buf[spi_tx_cnt++] = ((i << 16) >> 24);
    spi_tx_buf[spi_tx_cnt++] = ((i << 8) >> 24);
    spi_tx_buf[spi_tx_cnt++] = (i >> 24);
}

static void setDataFloat_spi_int(float f, float size)
{
    int16_t _temp = static_cast<int16_t>(f * size);
    spi_tx_buf[spi_tx_cnt++] = BYTE1(_temp);
    spi_tx_buf[spi_tx_cnt++] = BYTE0(_temp);
}

static float floatFromData_spi(unsigned char *data, int *anal_cnt)
{
    int i = 0x00;
    i |= (*(data + *anal_cnt + 3) << 24);
    i |= (*(data + *anal_cnt + 2) << 16);
    i |= (*(data + *anal_cnt + 1) << 8);
    i |= (*(data + *anal_cnt + 0));
    *anal_cnt += 4;
    return *(float *)&i;
}

static float floatFromData_spi_int(unsigned char *data, int *anal_cnt, float size)
{
    float temp = (float)((int16_t)(*(data + *anal_cnt + 0) << 8) | *(data + *anal_cnt + 1)) / size;
    *anal_cnt += 2;
    return temp;
}

static char charFromData_spi(unsigned char *data, int *anal_cnt)
{
    int temp = *anal_cnt;
    *anal_cnt += 1;
    return *(data + temp);
}

static int intFromData_spi(unsigned char *data, int *anal_cnt)
{
    int i = 0x00;
    i |= (*(data + *anal_cnt + 3) << 24);
    i |= (*(data + *anal_cnt + 2) << 16);
    i |= (*(data + *anal_cnt + 1) << 8);
    i |= (*(data + *anal_cnt + 0));
    *anal_cnt += 4;
    return i;
}

float To_180_degrees(float x)
{
    return (x > 180 ? (x - 360) : (x < -180 ? (x + 360) : x));
}

// Обновлённая функция: принимает выходной буфер
int slave_rx(uint8_t *data_buf, int num, _SPI_RX &rx_out)
{
    static int cnt_err_sum = 0;
    uint8_t sum = 0;
    uint8_t i;
    uint8_t temp;
    int anal_cnt = 4;

    for (i = 0; i < (num - 1); i++)
    {
        sum += *(data_buf + i);
    }

    if (!(sum == *(data_buf + num - 1)))
    {
        cnt_err_sum++;
        printf("SPI ERROR: sum err=%d sum_cal=0x%X sum=0x%X\n",
               cnt_err_sum, sum, *(data_buf + num - 1));
        return 0;
    }

    if (!(*(data_buf) == 0xFF && *(data_buf + 1) == 0xFB))
    {
        printf("SPI ERROR: Invalid header! Expected 0xFF 0xFB, got 0x%02X 0x%02X\n",
               *(data_buf), *(data_buf + 1));
        return 0;
    }

    if (*(data_buf + 2) == 26)
    {
        spi_loss_cnt = 0;
        if (spi_connect == 0)
        {
            printf("Hardware::Hardware SPI-STM32 Link3-Sbus Yunzhuo!!!=%d!!!\n", spi_connect);
            spi_connect = 1;
        }

        rx_out.att[0] = floatFromData_spi(data_buf, &anal_cnt);
        rx_out.att[1] = floatFromData_spi(data_buf, &anal_cnt);
        rx_out.att[2] = floatFromData_spi(data_buf, &anal_cnt);

        rx_out.att_rate[0] = floatFromData_spi(data_buf, &anal_cnt);
        rx_out.att_rate[1] = floatFromData_spi(data_buf, &anal_cnt);
        rx_out.att_rate[2] = floatFromData_spi(data_buf, &anal_cnt);

        rx_out.acc_b[0] = floatFromData_spi(data_buf, &anal_cnt);
        rx_out.acc_b[1] = floatFromData_spi(data_buf, &anal_cnt);
        rx_out.acc_b[2] = floatFromData_spi(data_buf, &anal_cnt);

        for (int i = 0; i < 10; i++)
        {
            if (anal_cnt + 6 > num)
            {
                printf("SPI ERROR: Buffer overflow in motor data parsing! anal_cnt=%d, num=%d, motor=%d\n",
                       anal_cnt, num, i);
                break;
            }

            rx_out.q[i] = floatFromData_spi_int(data_buf, &anal_cnt, CAN_POS_DIV);
            rx_out.dq[i] = floatFromData_spi_int(data_buf, &anal_cnt, CAN_POS_DIV);
            rx_out.tau[i] = floatFromData_spi_int(data_buf, &anal_cnt, CAN_T_DIV);

            temp = charFromData_spi(data_buf, &anal_cnt);
            rx_out.connect_motor[i] = (temp % 100) / 10;
            rx_out.ready[i] = temp % 10;
        }
    }
    else
    {
        return 0;
    }

    return 1;
}

// Обновлённая функция: принимает tx_data и mems_data
void can_board_send(char sel, const _SPI_TX &tx_data, const _MEMS &mems_data)
{
    int i;
    char sum_t = 0;
    spi_tx_cnt = 0;

    spi_tx_buf[spi_tx_cnt++] = 0xFE;
    spi_tx_buf[spi_tx_cnt++] = 0xFC;
    spi_tx_buf[spi_tx_cnt++] = sel;
    spi_tx_buf[spi_tx_cnt++] = 0;

    switch (sel)
    {
    case 45:
        spi_tx_buf[spi_tx_cnt++] = tx_data.en_motor * 100 + (tx_data.reset_q * 2)* 10 + tx_data.reset_err;
        spi_tx_buf[spi_tx_cnt++] = mems_data.Acc_CALIBRATE * 100 + mems_data.Gyro_CALIBRATE * 10 + mems_data.Mag_CALIBRATE;
        spi_tx_buf[spi_tx_cnt++] = tx_data.beep_state;

        for (int id = 0; id < 10; id++)
        {
            setDataFloat_spi_int(tx_data.q_set[id], CAN_POS_DIV);
            setDataFloat_spi_int(tx_data.dq_set[id], CAN_DPOS_DIV);
            setDataFloat_spi_int(tx_data.tau_ff[id], CAN_T_DIV);
            setDataFloat_spi_int(tx_data.kp, CAN_GAIN_DIV_P);
            setDataFloat_spi_int(tx_data.kd, CAN_GAIN_DIV_D);
        }
        break;

    default:
        // Заполняем нулями, если нужно
        for (int id = 0; id < 10; id++)
        {
            setDataFloat_spi(0);
            setDataFloat_spi(0);
            setDataFloat_spi(0);
        }
        break;
    }

    spi_tx_buf[3] = (spi_tx_cnt)-4;
    for (i = 0; i < spi_tx_cnt; i++)
        sum_t += spi_tx_buf[i];
    spi_tx_buf[spi_tx_cnt++] = sum_t;

    if (spi_tx_cnt > SPI_SEND_MAX)
        printf("spi_tx_cnt=%d over flow!!!\n", spi_tx_cnt);
    spi_tx_cnt_show = spi_tx_cnt;
}

class Motor_control : public rclcpp::Node
{
public:
    Motor_control()
        : rclcpp::Node("dual_io_node"),
          mems_{} // инициализация нулями
    {
        RCLCPP_INFO(this->get_logger(), "Hardware::Thread_SPI started");

        Cycle_Time_Init();
        fd = SPISetup(0, speed);

        if (fd == -1)
        {
            RCLCPP_ERROR(this->get_logger(), "init spi failed!");
            return;
        }

        // Инициализация издателей для tinker_msgs
        imu_state_pub_ = this->create_publisher<tinker_msgs::msg::IMUState>("imu/state", 10);
        low_state_pub_ = this->create_publisher<tinker_msgs::msg::LowState>("low/state", 10);
        joint_state_pub_ = this->create_publisher<sensor_msgs::msg::JointState>("/robot_joints", 10);

        // Подписки для tinker_msgs
        low_cmd_sub_ = this->create_subscription<tinker_msgs::msg::LowCmd>(
            "low/cmd", 10,
            std::bind(&Motor_control::on_low_cmd, this, std::placeholders::_1));

        control_cmd_sub_ = this->create_subscription<tinker_msgs::msg::ControlCmd>(
            "control/cmd", 10,
            std::bind(&Motor_control::on_control_cmd, this, std::placeholders::_1));

        one_motor_cmd_sub_ = this->create_subscription<tinker_msgs::msg::OneMotorCmd>(
            "motor/cmd", 10,
            std::bind(&Motor_control::on_one_motor_cmd, this, std::placeholders::_1));

        // Сервис для получения списка моторов
        motor_list_service_ = this->create_service<tinker_msgs::srv::MotorList>(
            "motor/list",
            std::bind(&Motor_control::handle_motor_list, this,
                     std::placeholders::_1, std::placeholders::_2));

        joint_names_ = {
            "joint_l_yaw", "joint_l_roll", "joint_l_pitch", "joint_l_knee", "joint_l_ankle",
            "joint_r_yaw", "joint_r_roll", "joint_r_pitch", "joint_r_knee", "joint_r_ankle"};

        using namespace std::chrono_literals;
        timer_ = this->create_wall_timer(1ms, std::bind(&Motor_control::on_timer, this));

        // Инициализация массивов
        std::fill_n(spi_tx_.q_set, 10, 0.0f);
        std::fill_n(spi_tx_.dq_set, 10, 0.0f);
        std::fill_n(spi_tx_.tau_ff, 10, 0.0f);

        // Инициализация параметров моторов по умолчанию
        spi_tx_.kp = 0.0f;
        spi_tx_.kd = 0.0f;
        spi_tx_.en_motor = false;
        spi_tx_.reset_q = false;
        spi_tx_.reset_err = false;
        spi_tx_.beep_state = 0.0f;
    }

private:
    // Подписчики для tinker_msgs
    rclcpp::Subscription<tinker_msgs::msg::LowCmd>::SharedPtr low_cmd_sub_;
    rclcpp::Subscription<tinker_msgs::msg::ControlCmd>::SharedPtr control_cmd_sub_;
    rclcpp::Subscription<tinker_msgs::msg::OneMotorCmd>::SharedPtr one_motor_cmd_sub_;

    // Издатели для tinker_msgs
    rclcpp::Publisher<tinker_msgs::msg::IMUState>::SharedPtr imu_state_pub_;
    rclcpp::Publisher<tinker_msgs::msg::LowState>::SharedPtr low_state_pub_;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_pub_;

    // Сервис
    rclcpp::Service<tinker_msgs::srv::MotorList>::SharedPtr motor_list_service_;

    std::vector<std::string> joint_names_;

    // Защищённые данные — теперь ВСЕ внутри класса
    _SPI_TX spi_tx_;
    _SPI_RX spi_rx_;
    _MEMS mems_;

    std::mutex motor_cmd_mutex_;
    std::mutex control_cmd_mutex_;
    std::mutex imu_params_mutex_;

    int fd = 0;
    rclcpp::TimerBase::SharedPtr timer_;

    void on_low_cmd(const tinker_msgs::msg::LowCmd::SharedPtr msg)
    {
        std::lock_guard<std::mutex> lock(motor_cmd_mutex_);

        if (msg->motor_cmd.size() != 10)
        {
            RCLCPP_WARN(this->get_logger(), "LowCmd must contain exactly 10 motor commands!");
            return;
        }

        for (int i = 0; i < 10; ++i)
        {
            spi_tx_.q_set[i] = msg->motor_cmd[i].position;
            spi_tx_.dq_set[i] = msg->motor_cmd[i].velocity;
            spi_tx_.tau_ff[i] = msg->motor_cmd[i].torque;
            spi_tx_.kp = msg->motor_cmd[i].kp;
            spi_tx_.kd = msg->motor_cmd[i].kd;
        }

        RCLCPP_DEBUG(this->get_logger(), "Updated motor commands from LowCmd for 10 motors");
    }

    void on_control_cmd(const tinker_msgs::msg::ControlCmd::SharedPtr msg)
    {
        std::lock_guard<std::mutex> lock(control_cmd_mutex_);

        // Обработка команд управления (ENABLE, DISABLE, SET_ZERRO_POSITION, CLEAR_ERROR)
        switch (msg->cmd)
        {
            case 252: // ENABLE
                spi_tx_.en_motor = true;
                RCLCPP_INFO(this->get_logger(), "Motor %d: ENABLE command", msg->motor_id);
                break;
            case 253: // DISABLE
                spi_tx_.en_motor = false;
                RCLCPP_INFO(this->get_logger(), "Motor %d: DISABLE command", msg->motor_id);
                break;
            case 254: // SET_ZERRO_POSITION
                spi_tx_.reset_q = true;
                RCLCPP_INFO(this->get_logger(), "Motor %d: SET_ZERRO_POSITION command", msg->motor_id);
                break;
            case 251: // CLEAR_ERROR
                spi_tx_.reset_err = true;
                RCLCPP_INFO(this->get_logger(), "Motor %d: CLEAR_ERROR command", msg->motor_id);
                break;
            default:
                RCLCPP_WARN(this->get_logger(), "Unknown control command: %d for motor %d",
                           msg->cmd, msg->motor_id);
                break;
        }
    }

    void on_one_motor_cmd(const tinker_msgs::msg::OneMotorCmd::SharedPtr msg)
    {
        std::lock_guard<std::mutex> lock(motor_cmd_mutex_);

        if (msg->motor_id >= 0 && msg->motor_id < 10)
        {
            spi_tx_.q_set[msg->motor_id] = msg->position;
            spi_tx_.dq_set[msg->motor_id] = msg->velocity;
            spi_tx_.tau_ff[msg->motor_id] = msg->torque;
            spi_tx_.kp = msg->kp;
            spi_tx_.kd = msg->kd;

            RCLCPP_DEBUG(this->get_logger(), "Updated motor %d: pos=%.3f, vel=%.3f, trq=%.3f",
                        msg->motor_id, msg->position, msg->velocity, msg->torque);
        }
        else
        {
            RCLCPP_WARN(this->get_logger(), "Invalid motor ID: %d (must be 0-9)", msg->motor_id);
        }
    }

    void handle_motor_list(const std::shared_ptr<tinker_msgs::srv::MotorList::Request> request,
                          std::shared_ptr<tinker_msgs::srv::MotorList::Response> response)
    {
        // Заполняем ответ данными о моторах
        // В реальной реализации здесь нужно получить актуальные данные из конфигурации
        response->active_joint_names = joint_names_;

        // Инициализируем массивы с данными по умолчанию
        response->motor_id = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        response->motor_group = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1}; // пример: 0 - левая нога, 1 - правая нога

        // Устанавливаем лимиты (примерные значения)
        response->position_max = std::vector<float>(10, 3.14f);  // ±180 градусов
        response->position_min = std::vector<float>(10, -3.14f);
        response->velocity_max = std::vector<float>(10, 10.0f);  // рад/с
        response->torque_max = std::vector<float>(10, 10.0f);    // Н·м
        response->torque_alarm = std::vector<float>(10, 8.0f);   // Н·м

        // Температурные лимиты
        response->temperature_mosfet_max = std::vector<int16_t>(10, 100);  // °C
        response->temperature_rotor_max = std::vector<int16_t>(10, 120);   // °C
        response->temperature_mosfet_alarm = std::vector<int16_t>(10, 80); // °C
        response->temperature_rotor_alarm = std::vector<int16_t>(10, 100); // °C

        // Электрические лимиты
        response->voltage_max = std::vector<int16_t>(10, 50);    // В
        response->voltage_min = std::vector<int16_t>(10, 40);    // В
        response->current_max = std::vector<int16_t>(10, 20);    // А
        response->current_alarm = std::vector<int16_t>(10, 15);  // А

        RCLCPP_INFO(this->get_logger(), "Motor list service called");
    }

    void transfer_with_tx(int sel, const _SPI_TX &tx_data, const _MEMS &mems_data)
    {
        static uint8_t state = 0;
        static uint8_t _data_len2 = 0, _data_cnt2 = 0;
        static int parser_timeout = 0;
        int ret;
        uint8_t data = 0;

        can_board_send(sel, tx_data, mems_data);

        ret = SPIDataRW(0, spi_tx_buf, rx, SPI_SEND_MAX);

        if (ret < 1)
        {
            RCLCPP_ERROR(this->get_logger(), "SPI ERROR: Reopen! ret=%d", ret);
            SPISetup(0, speed);
        }
        else
        {
            for (int i = 0; i < SPI_SEND_MAX; i++)
            {
                data = rx[i];
                parser_timeout++;

                if (parser_timeout > 1000)
                {
                    state = 0;
                    parser_timeout = 0;
                }

                if (state == 0 && data == 0xFF)
                {
                    state = 1;
                    spi_rx_buf[0] = data;
                    parser_timeout = 0;
                }
                else if (state == 1 && data == 0xFB)
                {
                    state = 2;
                    spi_rx_buf[1] = data;
                    parser_timeout = 0;
                }
                else if (state == 1 && data == 0xFF)
                {
                    spi_rx_buf[0] = data;
                    parser_timeout = 0;
                }
                else if (state == 2 && data > 0 && data < 0xF1)
                {
                    state = 3;
                    spi_rx_buf[2] = data;
                    parser_timeout = 0;
                }
                else if (state == 3 && data < SPI_BUF_SIZE)
                {
                    if (data < 50 || data > 150)
                    {
                        state = 0;
                        parser_timeout = 0;
                        continue;
                    }
                    state = 4;
                    spi_rx_buf[3] = data;
                    _data_len2 = data;
                    _data_cnt2 = 0;
                    parser_timeout = 0;
                }
                else if (state == 4 && _data_len2 > 0)
                {
                    _data_len2--;
                    spi_rx_buf[4 + _data_cnt2++] = data;
                    if (_data_len2 == 0)
                    {
                        state = 5;
                        parser_timeout = 0;
                    }
                }
                else if (state == 5)
                {
                    state = 0;
                    spi_rx_buf[4 + _data_cnt2] = data;
                    parser_timeout = 0;

                    // Парсим в локальную структуру
                    _SPI_RX temp_rx;
                    if (slave_rx(spi_rx_buf, _data_cnt2 + 5, temp_rx))
                    {
                        spi_rx_ = temp_rx; // обновляем состояние
                    }
                }
                else
                {
                    if (data == 0xFF)
                    {
                        state = 1;
                        spi_rx_buf[0] = data;
                    }
                    else
                    {
                        state = 0;
                    }
                }
            }
        }
    }

    void on_timer()
    {
        static int counter = 0;
        static auto last_time = this->now();

        _SPI_TX local_tx;
        _MEMS local_mems;
        {
            std::lock_guard<std::mutex> lock1(motor_cmd_mutex_);
            std::lock_guard<std::mutex> lock2(control_cmd_mutex_);
            std::lock_guard<std::mutex> lock3(imu_params_mutex_);
            local_tx = spi_tx_;
            local_mems = mems_;
        }

        transfer_with_tx(45, local_tx, local_mems);

        counter++;
        if (counter % 1000 == 0)
        {
            auto now = this->now();
            auto dt = (now - last_time).seconds();
            RCLCPP_INFO(this->get_logger(), "SPI frequency: %.1f Hz", 1000.0 / dt);
            last_time = now;

            RCLCPP_INFO(this->get_logger(), "Motor 0 command: pos=%.3f, vel=%.3f, trq=%.3f",
                        local_tx.q_set[0], local_tx.dq_set[0], local_tx.tau_ff[0]);
        }

        // Публикация IMUState
        auto imu_state_msg = std::make_unique<tinker_msgs::msg::IMUState>();
        imu_state_msg->timestamp_state = this->get_clock()->now();

        // Заполняем данные IMU (пример - в реальности нужно преобразовать данные из spi_rx_)
        imu_state_msg->rpy[0] = spi_rx_.att[0]; // roll
        imu_state_msg->rpy[1] = spi_rx_.att[1]; // pitch
        imu_state_msg->rpy[2] = spi_rx_.att[2]; // yaw

        imu_state_msg->gyroscope[0] = spi_rx_.att_rate[0];
        imu_state_msg->gyroscope[1] = spi_rx_.att_rate[1];
        imu_state_msg->gyroscope[2] = spi_rx_.att_rate[2];

        imu_state_msg->accelerometer[0] = spi_rx_.acc_b[0];
        imu_state_msg->accelerometer[1] = spi_rx_.acc_b[1];
        imu_state_msg->accelerometer[2] = spi_rx_.acc_b[2];

        // Кватернион (нужно вычислить из RPY или получить от IMU)
        // Пока заполняем единичным кватернионом
        imu_state_msg->quaternion[0] = 1.0;
        imu_state_msg->quaternion[1] = 0.0;
        imu_state_msg->quaternion[2] = 0.0;
        imu_state_msg->quaternion[3] = 0.0;

        imu_state_msg->temperature = 25; // примерная температура

        imu_state_pub_->publish(std::move(imu_state_msg));

        // Публикация LowState
        auto low_state_msg = std::make_unique<tinker_msgs::msg::LowState>();
        low_state_msg->timestamp_state = this->get_clock()->now();
        low_state_msg->tick = counter;

        // Заполняем IMU состояние
        low_state_msg->imu_state = *imu_state_msg;

        // Заполняем состояния моторов
        low_state_msg->motor_state;
        for (int i = 0; i < 10; ++i)
        {
            auto& motor_state = low_state_msg->motor_state[i];
            motor_state.timestamp_state = this->get_clock()->now();
            motor_state.position = spi_rx_.q[i];
            motor_state.velocity = spi_rx_.dq[i];
            motor_state.torque = spi_rx_.tau[i];

            // Определяем состояние мотора на основе флагов подключения и готовности
            if (spi_rx_.connect_motor[i] && spi_rx_.ready[i])
            {
                motor_state.error = tinker_msgs::msg::MotorState::ENABLE;
            }
            else if (!spi_rx_.connect_motor[i])
            {
                motor_state.error = tinker_msgs::msg::MotorState::LOSS_CONNECTION;
            }
            else
            {
                motor_state.error = tinker_msgs::msg::MotorState::DISABLING;
            }

            // Температуры (примерные значения)
            motor_state.temperature_mosfet = 40;
            motor_state.temperature_rotor = 45;
        }

        low_state_pub_->publish(std::move(low_state_msg));

        // JointState для RViz
        auto js = std::make_unique<sensor_msgs::msg::JointState>();
        js->header.stamp = this->get_clock()->now();
        js->name = joint_names_;
        js->position.resize(10);
        for (int i = 0; i < 10; ++i)
        {
            js->position[i] = spi_rx_.q[i];
        }
        joint_state_pub_->publish(std::move(js));
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    // Рекомендуется использовать MultiThreadedExecutor, если планируете расширение
    rclcpp::spin(std::make_shared<Motor_control>());
    rclcpp::shutdown();
    return 0;
}