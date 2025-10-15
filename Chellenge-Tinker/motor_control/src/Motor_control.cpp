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
 *
 */

#include <memory>
#include <atomic>
#include <functional>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/bool.hpp"
// hardware_msg messages
#include "hardware_msg/msg/board_parameters.hpp"
#include "hardware_msg/msg/imu.hpp"
#include "hardware_msg/msg/imu_parameters.hpp"
#include "hardware_msg/msg/motor_data.hpp"
#include "hardware_msg/msg/motor_parameters.hpp"
#include "hardware_msg/msg/motors_commands.hpp"
#include "hardware_msg/msg/motors_states.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "comm.h"
#include "spi_node.h"
#include "spi.h"
#include "sys_time.h"
#include <pthread.h>
#include <signal.h>
#include <errno.h>

#define SPI_TEST 0 /**< Флаг тестирования SPI */

#define USE_USB 0    /**< Флаг использования USB */
#define USE_SERIAL 0 /**< Флаг использования Serial */

#define MOTOR_ID 0 /**< ID мотора по умолчанию */

#define EN_SPI_BIG 1         /**< Флаг использования расширенного SPI */
#define CAN_LINK_COMM_VER1 0 /**< Версия CAN протокола 1 */
#define CAN_LINK_COMM_VER2 1 /**< Версия CAN протокола 2 (3 BLDC Param DIV) */

#if EN_SPI_BIG
#if CAN_LINK_COMM_VER1
#define SPI_SEND_MAX 85 /**< Максимальный размер SPI пакета для версии 1 */
#else
#define SPI_SEND_MAX 120 + 20 + 20 /**< Максимальный размер SPI пакета для версии 2 */
#endif
#else
#define SPI_SEND_MAX 40 /**< Максимальный размер SPI пакета для малого режима */
#endif

#define EN_MULTI_THREAD 1                          /**< Флаг многопоточности */
#define NO_THREAD 0                                /**< Флаг отсутствия потоков */
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0])) /**< Макрос для вычисления размера массива */
#define MEM_SPI 0001                               /**< Идентификатор SPI памяти */
#define MEM_SIZE 2048                              /**< Размер памяти */

#if NO_THREAD && !EN_MULTI_THREAD
static uint32_t speed = 150000 * 4; /**< Скорость SPI для однопоточного режима */
#define DELAY_SPI 250               /**< Задержка SPI в микросекундах */
#else
static uint32_t speed = 20000000; /**< Скорость SPI для многопоточного режима */
#define DELAY_SPI 250 /**< Задержка SPI в микросекундах */
#endif

float spi_loss_cnt = 0;      /**< Счетчик потерь SPI пакетов */
int spi_connect = 0;         /**< Флаг подключения SPI */
float mems_usb_loss_cnt = 0; /**< Счетчик потерь USB пакетов MEMS */
int mems_usb_connect = 0;    /**< Флаг подключения MEMS USB */

_MEMS mems; /**< Структура данных MEMS */
using namespace std;

_SPI_RX spi_rx; /**< Структура данных приема SPI */
_SPI_TX spi_tx; /**< Структура данных передачи SPI */

uint8_t spi_tx_buf[SPI_BUF_SIZE] = {0}; /**< Буфер передачи SPI */
uint8_t spi_rx_buf[SPI_BUF_SIZE] = {0}; /**< Буфер приема SPI */
int spi_tx_cnt_show = 0;                /**< Счетчик передачи для отображения */
int spi_tx_cnt = 0;                     /**< Счетчик передачи SPI */

uint8_t usb_tx_buf[SPI_BUF_SIZE] = {0}; /**< Буфер передачи USB */
uint8_t usb_rx_buf[SPI_BUF_SIZE] = {0}; /**< Буфер приема USB */
int usb_tx_cnt = 0;                     /**< Счетчик передачи USB */
int usb_rx_cnt = 0;                     /**< Счетчик приема USB */

uint8_t tx[SPI_BUF_SIZE] = {};   /**< Временный буфер передачи */
uint8_t rx[ARRAY_SIZE(tx)] = {}; /**< Временный буфер приема */

/**
 * @brief Установка целочисленного значения в SPI буфер
 *
 * @param i Целое число для установки
 *
 * @details
 * Разбивает 32-битное целое число на 4 байта и записывает в буфер передачи.
 * Использует little-endian порядок байтов.
 */
static void setDataInt_spi(int i)
{
    spi_tx_buf[spi_tx_cnt++] = ((i << 24) >> 24);
    spi_tx_buf[spi_tx_cnt++] = ((i << 16) >> 24);
    spi_tx_buf[spi_tx_cnt++] = ((i << 8) >> 24);
    spi_tx_buf[spi_tx_cnt++] = (i >> 24);
}

/**
 * @brief Установка значения с плавающей точкой в SPI буфер
 *
 * @param f Число с плавающей точкой для установки
 *
 * @details
 * Преобразует float в целое число через указатели и записывает в буфер
 * как 4 байта в little-endian порядке.
 */
static void setDataFloat_spi(float f)
{
    int i = *(int *)&f;
    spi_tx_buf[spi_tx_cnt++] = ((i << 24) >> 24);
    spi_tx_buf[spi_tx_cnt++] = ((i << 16) >> 24);
    spi_tx_buf[spi_tx_cnt++] = ((i << 8) >> 24);
    spi_tx_buf[spi_tx_cnt++] = (i >> 24);
}

/**
 * @brief Установка значения с плавающей точкой в SPI буфер с масштабированием
 *
 * @param f Число с плавающей точкой
 * @param size Масштабирующий коэффициент
 *
 * @details
 * Масштабирует float, преобразует в int16_t и записывает в буфер как 2 байта.
 */
static void setDataFloat_spi_int(float f, float size)
{
    int16_t _temp;
    _temp = f * size;
    spi_tx_buf[spi_tx_cnt++] = BYTE1(_temp);
    spi_tx_buf[spi_tx_cnt++] = BYTE0(_temp);
}

/**
 * @brief Извлечение числа с плавающей точкой из данных SPI
 *
 * @param data Указатель на буфер данных
 * @param anal_cnt Указатель на счетчик анализа (увеличивается на 4)
 * @return float Извлеченное число с плавающей точкой
 */
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

/**
 * @brief Извлечение числа с плавающей точкой из данных SPI с масштабированием
 *
 * @param data Указатель на буфер данных
 * @param anal_cnt Указатель на счетчик анализа (увеличивается на 2)
 * @param size Масштабирующий коэффициент
 * @return float Извлеченное число с плавающей точкой
 */
static float floatFromData_spi_int(unsigned char *data, int *anal_cnt, float size)
{
    float temp = 0;
    temp = (float)((int16_t)(*(data + *anal_cnt + 0) << 8) | *(data + *anal_cnt + 1)) / size;
    *anal_cnt += 2;
    return temp;
}

/**
 * @brief Извлечение символа из данных SPI
 *
 * @param data Указатель на буфер данных
 * @param anal_cnt Указатель на счетчик анализа (увеличивается на 1)
 * @return char Извлеченный символ
 */
static char charFromData_spi(unsigned char *data, int *anal_cnt)
{
    int temp = *anal_cnt;
    *anal_cnt += 1;
    return *(data + temp);
}

/**
 * @brief Извлечение целого числа из данных SPI
 *
 * @param data Указатель на буфер данных
 * @param anal_cnt Указатель на счетчик анализа (увеличивается на 4)
 * @return int Извлеченное целое число
 */
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

/**
 * @brief Нормализация угла в диапазон [-180, 180] градусов
 *
 * @param x Исходный угол в градусах
 * @return float Нормализованный угол в диапазоне [-180, 180]
 */
float To_180_degrees(float x)
{
    return (x > 180 ? (x - 360) : (x < -180 ? (x + 360) : x));
}

/**
 * @brief Декодирование данных, полученных от STM32 через SPI
 *
 * @param data_buf Буфер полученных данных
 * @param num Размер буфера данных
 * @return int Результат декодирования: 1 - успех, 0 - ошибка
 *
 * @details
 * Выполняет:
 * - Проверку контрольной суммы
 * - Проверку заголовка пакета (0xFF 0xFB)
 * - Декодирование данных IMU и двигателей
 * - Обновление структуры spi_rx
 */
int slave_rx(uint8_t *data_buf, int num)
{
    static int cnt_err_sum = 0;
    uint8_t id;
    uint8_t sum = 0;
    uint8_t i;
    uint8_t temp;
    int anal_cnt = 4;

    // Вычисление контрольной суммы
    for (i = 0; i < (num - 1); i++)
    {
        sum += *(data_buf + i);
    }

    // Проверка контрольной суммы
    if (!(sum == *(data_buf + num - 1)))
    {
        cnt_err_sum++;
        printf("SPI ERROR: sum err=%d sum_cal=0x%X sum=0x%X\n",
               cnt_err_sum, sum, *(data_buf + num - 1));
        return 0;
    }

    // Проверка заголовка пакета
    if (!(*(data_buf) == 0xFF && *(data_buf + 1) == 0xFB))
    {
        printf("SPI ERROR: Invalid header! Expected 0xFF 0xFB, got 0x%02X 0x%02X\n",
               *(data_buf), *(data_buf + 1));
        return 0;
    }

    // Декодирование пакета с ID 26
    if (*(data_buf + 2) == 26)
    {
        spi_loss_cnt = 0;
        if (spi_connect == 0)
        {
            printf("Hardware::Hardware SPI-STM32 Link3-Sbus Yunzhuo!!!=%d!!!\n", spi_connect);
            spi_connect = 1;
        }

        // Декодирование данных IMU
        spi_rx.att[0] = floatFromData_spi(spi_rx_buf, &anal_cnt);
        spi_rx.att[1] = floatFromData_spi(spi_rx_buf, &anal_cnt);
        spi_rx.att[2] = floatFromData_spi(spi_rx_buf, &anal_cnt);

        spi_rx.att_rate[0] = floatFromData_spi(spi_rx_buf, &anal_cnt);
        spi_rx.att_rate[1] = floatFromData_spi(spi_rx_buf, &anal_cnt);
        spi_rx.att_rate[2] = floatFromData_spi(spi_rx_buf, &anal_cnt);

        spi_rx.acc_b[0] = floatFromData_spi(spi_rx_buf, &anal_cnt);
        spi_rx.acc_b[1] = floatFromData_spi(spi_rx_buf, &anal_cnt);
        spi_rx.acc_b[2] = floatFromData_spi(spi_rx_buf, &anal_cnt);

        // Декодирование данных двигателей
        for (int i = 0; i < 10; i++)
        {
            // Проверка на переполнение буфера
            if (anal_cnt + 6 > num)
            {
                printf("SPI ERROR: Buffer overflow in motor data parsing! anal_cnt=%d, num=%d, motor=%d\n",
                       anal_cnt, num, i);
                break;
            }

            spi_rx.q[i] = floatFromData_spi_int(spi_rx_buf, &anal_cnt, CAN_POS_DIV);
            spi_rx.dq[i] = floatFromData_spi_int(spi_rx_buf, &anal_cnt, CAN_POS_DIV);
            spi_rx.tau[i] = floatFromData_spi_int(spi_rx_buf, &anal_cnt, CAN_T_DIV);

            temp = charFromData_spi(spi_rx_buf, &anal_cnt);
            spi_rx.connect_motor[i] = (temp % 100) / 10;
            spi_rx.ready[i] = temp % 10;
        }
    }
    else
    {
        // Неизвестный ID пакета - игнорируем
        return 0;
    }

    return 1;
}

/**
 * @brief Формирование и отправка команд на контроллер двигателей
 *
 * @param sel Идентификатор типа команды (45 - основные команды)
 *
 * @details
 * Формирует SPI пакет с командами управления:
 * - Состояние двигателей (включение, сброс)
 * - Калибровка IMU
 * - Уставки положения, скорости и момента
 * - Коэффициенты PID регулятора
 */
void can_board_send(char sel)
{
    int i;
    static float t_temp = 0;
    char id = 0;
    char sum_t = 0, _cnt = 0;
    static char bldc_id_sel = 0;
    spi_tx_cnt = 0;

    // Заголовок пакета
    spi_tx_buf[spi_tx_cnt++] = 0xFE;
    spi_tx_buf[spi_tx_cnt++] = 0xFC;
    spi_tx_buf[spi_tx_cnt++] = sel;
    spi_tx_buf[spi_tx_cnt++] = 0;

    // Формирование данных в зависимости от типа команды
    switch (sel)
    {
    case 45: // Основные команды управления
        spi_tx_buf[spi_tx_cnt++] = spi_tx.en_motor * 100 + spi_tx.reset_q * 10 + spi_tx.reset_err;
        spi_tx_buf[spi_tx_cnt++] = mems.Acc_CALIBRATE * 100 + mems.Gyro_CALIBRATE * 10 + mems.Mag_CALIBRATE;
        spi_tx_buf[spi_tx_cnt++] = spi_tx.beep_state;

        // Данные для 10 двигателей
        for (int id = 0; id < 10; id++)
        {
            setDataFloat_spi_int(spi_tx.q_set[id], CAN_POS_DIV);
            setDataFloat_spi_int(spi_tx.dq_set[id], CAN_DPOS_DIV);
            setDataFloat_spi_int(spi_tx.tau_ff[id], CAN_T_DIV);
            setDataFloat_spi_int(spi_tx.kp, CAN_GAIN_DIV_P);
            setDataFloat_spi_int(spi_tx.kd, CAN_GAIN_DIV_D);
        }
        break;

    default:
        // Пустые данные для неизвестных команд
        for (int id = 0; id < 10; id++)
        {
            setDataFloat_spi(0);
            setDataFloat_spi(0);
            setDataFloat_spi(0);
        }
        break;
    }

    // Установка длины данных и контрольной суммы
    spi_tx_buf[3] = (spi_tx_cnt)-4;
    for (i = 0; i < spi_tx_cnt; i++)
        sum_t += spi_tx_buf[i];
    spi_tx_buf[spi_tx_cnt++] = sum_t;

    // Проверка на переполнение буфера
    if (spi_tx_cnt > SPI_SEND_MAX)
        printf("spi_tx_cnt=%d over flow!!!\n", spi_tx_cnt);
    spi_tx_cnt_show = spi_tx_cnt;
}

/**
 * @brief Передача данных через SPI и прием ответа
 *
 * @param fd Файловый дескриптор SPI
 * @param sel Идентификатор типа команды
 *
 * @details
 * Выполняет полный цикл обмена данными:
 * 1. Формирование команды
 * 2. Отправка через SPI
 * 3. Прием и парсинг ответа
 * 4. Обработка ошибок связи
 */
void transfer(int fd, int sel)
{
    static uint8_t state, rx_cnt;
    static uint8_t _data_len2 = 0, _data_cnt2 = 0;
    static int parser_timeout = 0;
    int ret;
    uint8_t data = 0;

    // Формирование команды- заполняет spi_tx_buf данными из spi_tx структуры
    can_board_send(sel);

    // Отправка данных через SPI
    ret = SPIDataRW(0, spi_tx_buf, rx, SPI_SEND_MAX);

    if (ret < 1)
    {
        printf("SPI ERROR: Reopen! ret=%d\n", ret);
        SPISetup(0, speed); // Повторная инициализация при ошибке
    }
    else
    {
        // Парсинг принятых данных
        for (int i = 0; i < SPI_SEND_MAX; i++)
        {
            data = rx[i];
            parser_timeout++;

            // Таймаут парсера
            if (parser_timeout > 1000)
            {
                state = 0;
                parser_timeout = 0;
            }

            // Конечный автомат для парсинга пакета
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
            else if (state == 2 && data > 0 && data < 0XF1)
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

                slave_rx(spi_rx_buf, _data_cnt2 + 5);
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

/**
 * @class Motor_control
 * @brief ROS2 узел для управления двигателями через SPI
 *
 * @details
 * Основной класс узла, обеспечивающий:
 * - Инициализацию SPI интерфейса
 * - Подписку на ROS2 топики команд
 * - Публикацию состояний и данных датчиков
 * - Циклический обмен данными с аппаратурой
 */
class Motor_control : public rclcpp::Node
{
public:
    /**
     * @brief Конструктор узла Motor_control
     */
    Motor_control()
        : rclcpp::Node("dual_io_node")
    {

        char buf_mem[MEM_SIZE] = {1, 2};

        RCLCPP_INFO(this->get_logger(), "Hardware::Thread_SPI started");

        // Инициализация системного времени и SPI
        Cycle_Time_Init();
        fd = SPISetup(0, speed);

        if (fd == -1)
        {
            RCLCPP_ERROR(this->get_logger(), "init spi failed!");
            return;
        }

        // Инициализация издателей
        imu_pub_ = this->create_publisher<hardware_msg::msg::Imu>("imu/data", 10);
        motors_states_pub_ = this->create_publisher<hardware_msg::msg::MotorsStates>("motors/states", 10);
        motor_data_pub_ = this->create_publisher<hardware_msg::msg::MotorData>("motor/data", 10);
        joint_state_pub_ = this->create_publisher<sensor_msgs::msg::JointState>("/robot_joints", 10);

        // Имена суставов для URDF визуализации
        joint_names_ = {
            "joint_l_yaw",
            "joint_l_roll",
            "joint_l_pitch",
            "joint_l_knee",
            "joint_l_ankle",
            "joint_r_yaw",
            "joint_r_roll",
            "joint_r_pitch",
            "joint_r_knee",
            "joint_r_ankle"};

        // Инициализация подписчиков
        motors_cmd_sub_ = this->create_subscription<hardware_msg::msg::MotorsCommands>(
            "motors/commands", 10,
            std::bind(&Motor_control::on_motors_commands, this, std::placeholders::_1));
        board_params_sub_ = this->create_subscription<hardware_msg::msg::BoardParameters>(
            "control_board/commands", 10,
            std::bind(&Motor_control::on_board_parameters, this, std::placeholders::_1));
        imu_params_sub_ = this->create_subscription<hardware_msg::msg::ImuParameters>(
            "imu/commands", 10,
            std::bind(&Motor_control::on_imu_parameters, this, std::placeholders::_1));
        motor_params_sub_ = this->create_subscription<hardware_msg::msg::MotorParameters>(
            "motor/params", 10,
            std::bind(&Motor_control::on_motor_parameters, this, std::placeholders::_1));

        // Таймер для циклического обмена данными
        using namespace std::chrono_literals;
        timer_ = this->create_wall_timer(1ms, std::bind(&Motor_control::on_timer, this));
    }

private:
    // Подписчики
    rclcpp::Subscription<hardware_msg::msg::MotorsCommands>::SharedPtr motors_cmd_sub_;
    rclcpp::Subscription<hardware_msg::msg::BoardParameters>::SharedPtr board_params_sub_;
    rclcpp::Subscription<hardware_msg::msg::ImuParameters>::SharedPtr imu_params_sub_;
    rclcpp::Subscription<hardware_msg::msg::MotorParameters>::SharedPtr motor_params_sub_;

    // Издатели
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr value_pub_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr flag_pub_;
    rclcpp::Publisher<hardware_msg::msg::Imu>::SharedPtr imu_pub_;
    rclcpp::Publisher<hardware_msg::msg::MotorsStates>::SharedPtr motors_states_pub_;
    rclcpp::Publisher<hardware_msg::msg::MotorData>::SharedPtr motor_data_pub_;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_pub_;
    std::vector<std::string> joint_names_; /**< Имена суставов для URDF */

    /**
     * @brief Обработчик команд управления моторами
     *
     * @param msg Сообщение с командами управления
     */
    void on_motors_commands(const hardware_msg::msg::MotorsCommands::SharedPtr msg)
    {
        spi_tx.q_set[MOTOR_ID] = msg->target_pos;
        spi_tx.dq_set[MOTOR_ID] = msg->target_vel;
        spi_tx.tau_ff[MOTOR_ID] = msg->target_trq;

        RCLCPP_INFO(this->get_logger(),
                    "Received motor commands - Motor ID: %d, Target Pos: %.3f, Target Vel: %.3f, Target Trq: %.3f",
                    MOTOR_ID,
                    msg->target_pos,
                    msg->target_vel,
                    msg->target_trq);

        RCLCPP_DEBUG(this->get_logger(),
                     "SPI TX values - q_set[%d]: %.3f, dq_set[%d]: %.3f, tau_ff[%d]: %.3f",
                     MOTOR_ID, spi_tx.q_set[MOTOR_ID],
                     MOTOR_ID, spi_tx.dq_set[MOTOR_ID],
                     MOTOR_ID, spi_tx.tau_ff[MOTOR_ID]);
    }

    /**
     * @brief Обработчик параметров платы управления
     *
     * @param msg Сообщение с параметрами платы
     */
    void on_board_parameters(const hardware_msg::msg::BoardParameters::SharedPtr msg)
    {
        spi_tx.beep_state = msg->beep_state;
    }

    /**
     * @brief Обработчик параметров IMU
     *
     * @param msg Сообщение с параметрами IMU
     */
    void on_imu_parameters(const hardware_msg::msg::ImuParameters::SharedPtr msg)
    {
        mems.Acc_CALIBRATE = msg->acc_calibrate;
        mems.Gyro_CALIBRATE = msg->gyro_calibrate;
        mems.Mag_CALIBRATE = msg->msg_calibrate;
    }

    /**
     * @brief Обработчик параметров двигателей
     *
     * @param msg Сообщение с параметрами двигателей
     */
    void on_motor_parameters(const hardware_msg::msg::MotorParameters::SharedPtr msg)
    {
        spi_tx.kp = msg->kp;
        spi_tx.kd = msg->kd;
        spi_tx.en_motor = msg->enable;
        spi_tx.reset_q = msg->reset_zero;
        spi_tx.reset_err = msg->reset_error;
    }

    /**
     * @brief Таймерный callback для циклического обмена данными
     *
     * @details
     * Выполняется каждую 1 мс:
     * - Обмен данными через SPI
     * - Публикация состояний IMU и двигателей
     * - Публикация JointState для RViz
     * - Логирование частоты обмена
     */
    void on_timer()
    {
        static int counter = 0;
        static auto last_time = this->now();

        // Обмен данными через SPI, отправка spi_tx, а прием spi_rx
        transfer(1, 45);

        counter++;
        // Логирование частоты каждую секунду
        if (counter % 1000 == 0)
        {
            auto now = this->now();
            auto dt = (now - last_time).seconds();
            RCLCPP_INFO(this->get_logger(), "SPI frequency: %.1f Hz", 1000.0 / dt);
            last_time = now;

            RCLCPP_INFO(this->get_logger(), "Motor command: pos=%.3f, vel=%.3f, trq=%.3f",
                        spi_tx.q_set[MOTOR_ID], spi_tx.dq_set[MOTOR_ID], spi_tx.tau_ff[MOTOR_ID]);
        }

        // Публикация данных IMU
        hardware_msg::msg::Imu imu_msg;
        imu_msg.roll = spi_rx.att[0];
        imu_msg.pitch = spi_rx.att[1];
        imu_msg.yaw = spi_rx.att[2];
        imu_pub_->publish(imu_msg);

        // Публикация состояний двигателей
        hardware_msg::msg::MotorsStates motors_states_msg;
        motors_states_msg.current_pos = spi_rx.q[MOTOR_ID];
        motors_states_msg.current_vel = spi_rx.dq[MOTOR_ID];
        motors_states_msg.current_trq = spi_rx.tau[MOTOR_ID];
        motors_states_pub_->publish(motors_states_msg);

        // Публикация данных двигателя
        hardware_msg::msg::MotorData motor_data_msg;
        motor_data_msg.id = MOTOR_ID;
        motor_data_msg.connect = spi_rx.connect_motor[MOTOR_ID];
        motor_data_msg.motor_connected = spi_rx.connect_motor[MOTOR_ID];
        motor_data_msg.ready = spi_rx.ready[MOTOR_ID];
        motor_data_pub_->publish(motor_data_msg);

        // Публикация JointState для URDF визуализации
        sensor_msgs::msg::JointState js;
        js.header.stamp = this->get_clock()->now();
        js.name = joint_names_;
        js.position.assign(joint_names_.size(), 0.0);
        if (!joint_names_.empty())
        {
            js.position[0] = spi_rx.q[MOTOR_ID]; // joint_l_yaw
        }
        joint_state_pub_->publish(js);
    }

    rclcpp::TimerBase::SharedPtr timer_; /**< Таймер для циклического выполнения */
    int fd = 0;                          /**< Файловый дескриптор SPI */
};

/**
 * @brief Основная функция программы
 *
 * @param argc Количество аргументов командной строки
 * @param argv Аргументы командной строки
 * @return int Код завершения программы
 */
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Motor_control>());
    rclcpp::shutdown();
    return 0;
}