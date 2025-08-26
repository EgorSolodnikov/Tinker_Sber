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

#define SPI_TEST 0

#define USE_USB 0
#define USE_SERIAL 0

#define MOTOR_ID 0


#define EN_SPI_BIG 1
#define CAN_LINK_COMM_VER1 0
#define CAN_LINK_COMM_VER2 1//3 BLDC Param DIV
#if EN_SPI_BIG
#if CAN_LINK_COMM_VER1
    #define SPI_SEND_MAX  85
#else
    #define SPI_SEND_MAX  120+20+20//equal to stm32 spi send cnt
    // #define SPI_SEND_MAX 254
#endif
#else
#define SPI_SEND_MAX  40
#endif
#define EN_MULTI_THREAD 1
#define NO_THREAD 0
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define MEM_SPI 0001
#define MEM_SIZE 2048

#if NO_THREAD&&!EN_MULTI_THREAD
static uint32_t speed = 150000*4;//3Mhz 死机
#define DELAY_SPI 250//us
#else
static uint32_t speed = 20000000;//odroid 20M  upbord 2M  raspberrypi 5M
#define DELAY_SPI 250//us
#endif
float spi_loss_cnt = 0;
int spi_connect = 0;
float mems_usb_loss_cnt = 0;
int mems_usb_connect = 0;
_MEMS mems;
using namespace std;

_SPI_RX spi_rx;
_SPI_TX spi_tx;

uint8_t spi_tx_buf[SPI_BUF_SIZE] = {0};
uint8_t spi_rx_buf[SPI_BUF_SIZE] = {0};
int spi_tx_cnt_show=0;
int spi_tx_cnt = 0;

uint8_t usb_tx_buf[SPI_BUF_SIZE] = {0};
uint8_t usb_rx_buf[SPI_BUF_SIZE] = {0};
int usb_tx_cnt = 0;
int usb_rx_cnt = 0;

uint8_t tx[SPI_BUF_SIZE] = {};
uint8_t rx[ARRAY_SIZE(tx)] = {};


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

static void setDataFloat_spi_int(float f,float size)
{
    int16_t _temp;
    _temp=f*size;
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
    float temp=0;
    temp=(float)((int16_t)(*(data + *anal_cnt + 0)<<8)|*(data + *anal_cnt + 1))/size;
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
    return (x>180?(x-360):(x<-180?(x+360):x));
}

int slave_rx(uint8_t *data_buf, int num)//接收解码--------------from stm32
{
    static int cnt_err_sum=0;
    uint8_t id;
    uint8_t sum = 0;
    uint8_t i;
    uint8_t temp;
    int anal_cnt = 4;


    for (i = 0; i < (num - 1); i++) {
        sum += *(data_buf + i);
    }

    // for(i=0;i<num;i++)
    // {
    //     printf("0x%02x ",*(data_buf + i));
    // }
    // printf("\n");

    if (!(sum == *(data_buf + num - 1))){
        cnt_err_sum++;
        printf("SPI ERROR: sum err=%d sum_cal=0x%X sum=0x%X\n",
               cnt_err_sum, sum, *(data_buf + num - 1));
        return 0;
    }

    if (!(*(data_buf) == 0xFF && *(data_buf + 1) == 0xFB)){
        printf("SPI ERROR: Invalid header! Expected 0xFF 0xFB, got 0x%02X 0x%02X\n", 
               *(data_buf), *(data_buf + 1));
        return 0;
    }

    //printf("spi_rx_buf[2]=%d\n", *(data_buf + 2));
    if (*(data_buf + 2) == 26) //------------------old version---------- use now=======================2022/4/16
    {
        spi_loss_cnt = 0;
        if (spi_connect==0)
        {
            printf("Hardware::Hardware SPI-STM32 Link3-Sbus Yunzhuo!!!=%d!!!\n",spi_connect);
            spi_connect = 1;
        }

        // Защита доступа к spi_rx данным
        
        spi_rx.att[0] = floatFromData_spi(spi_rx_buf, &anal_cnt);
        spi_rx.att[1] = floatFromData_spi(spi_rx_buf, &anal_cnt);
        spi_rx.att[2] = floatFromData_spi(spi_rx_buf, &anal_cnt);

        spi_rx.att_rate[0] = floatFromData_spi(spi_rx_buf, &anal_cnt);
        spi_rx.att_rate[1] = floatFromData_spi(spi_rx_buf, &anal_cnt);
        spi_rx.att_rate[2] = floatFromData_spi(spi_rx_buf, &anal_cnt);

        spi_rx.acc_b[0] = floatFromData_spi(spi_rx_buf, &anal_cnt);
        spi_rx.acc_b[1] = floatFromData_spi(spi_rx_buf, &anal_cnt);
        spi_rx.acc_b[2] = floatFromData_spi(spi_rx_buf, &anal_cnt);

      

        // printf("Roll=%.2f, Pitch=%.2f, Yaw=%.2f, GyroX=%.2f, GyroY=%.2f, GyroZ=%.2f, AccX=%.2f, AccY=%.2f, AccZ=%.2f\n",
        //     spi_rx.att[0], spi_rx.att[1], spi_rx.att[2],
        //     spi_rx.att_rate[0], spi_rx.att_rate[1], spi_rx.att_rate[2],
        //     spi_rx.acc_b[0], spi_rx.acc_b[1], spi_rx.acc_b[2]);

        for (int i = 0; i < 10; i++)
        {
            // Проверка на переполнение буфера
            if (anal_cnt + 6 > num) { // 6 байт для q, dq, tau (по 2 байта) + 1 байт для temp
                printf("SPI ERROR: Buffer overflow in motor data parsing! anal_cnt=%d, num=%d, motor=%d\n", 
                       anal_cnt, num, i);
                break;
            }
            
            spi_rx.q[i] = floatFromData_spi_int(spi_rx_buf, &anal_cnt,CAN_POS_DIV);
            spi_rx.dq[i] = floatFromData_spi_int(spi_rx_buf, &anal_cnt,CAN_POS_DIV);
            spi_rx.tau[i] = floatFromData_spi_int(spi_rx_buf, &anal_cnt,CAN_T_DIV);

            temp = charFromData_spi(spi_rx_buf, &anal_cnt);
            // printf("temp = %d\n", temp);
            spi_rx.connect_motor[i] = (temp % 100) / 10;
            spi_rx.ready[i] = temp % 10;

            // if(spi_rx.connect_motor[i] == 1){
            //     printf("q[%d] = %f, dq[%d] = %f, tau[%d] = %f\n", i, spi_rx.q[i], i, spi_rx.dq[i], i, spi_rx.tau[i]);
            // }
        }

    } 
    else {
        // Неизвестный ID пакета - игнорируем
        return 0;
    }
  
    return 1;
}

void can_board_send(char sel)//发送到单片机
{
    //printf("can_board_send sel=%d\n",sel);
    int i;
    static float t_temp = 0;
    char id = 0;
    char sum_t = 0, _cnt = 0;
    static char bldc_id_sel=0;
    spi_tx_cnt = 0;

    spi_tx_buf[spi_tx_cnt++] = 0xFE;
    spi_tx_buf[spi_tx_cnt++] = 0xFC;
    spi_tx_buf[spi_tx_cnt++] = sel;
    spi_tx_buf[spi_tx_cnt++] = 0;

    // Защита доступа к spi_tx и mems данным

    switch (sel)
    {
        case 45:
            spi_tx_buf[spi_tx_cnt++] = spi_tx.en_motor*100+spi_tx.reset_q*10+spi_tx.reset_err; // Включение двигателей, установка нуля, сброс ошибки 

            spi_tx_buf[spi_tx_cnt++] =  mems.Acc_CALIBRATE*100+mems.Gyro_CALIBRATE*10+mems.Mag_CALIBRATE; // Калибровка

            spi_tx_buf[spi_tx_cnt++] =  spi_tx.beep_state;


            for (int id = 0; id < 10; id++)
            {
                setDataFloat_spi_int(spi_tx.q_set[id], CAN_POS_DIV);
                setDataFloat_spi_int(spi_tx.dq_set[id],CAN_DPOS_DIV);
                setDataFloat_spi_int(spi_tx.tau_ff[id],CAN_T_DIV);
                setDataFloat_spi_int(spi_tx.kp,CAN_GAIN_DIV_P);
                setDataFloat_spi_int(spi_tx.kd,CAN_GAIN_DIV_D);
            }
        break;

        // break;
        default:
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

    // printf("spi_tx_cnt=%d\n",spi_tx_cnt);
    if(spi_tx_cnt>SPI_SEND_MAX)
       printf("spi_tx_cnt=%d over flow!!!\n",spi_tx_cnt);
    spi_tx_cnt_show=spi_tx_cnt;
}

void transfer(int fd, int sel)//发送
{
    static uint8_t state, rx_cnt;
    static uint8_t _data_len2 = 0, _data_cnt2 = 0;
    static int parser_timeout = 0;
    int ret;
    uint8_t data = 0;

    can_board_send(sel);
    
    // for(int i=0;i<spi_tx_cnt;i++)
    //     printf("0x%X ",spi_tx_buf[i]);
    // printf("\n");

    // printf("spi_tx_cnt=%d\n",spi_tx_cnt);
    ret=SPIDataRW(0,spi_tx_buf,rx,SPI_SEND_MAX); //向总线中写入7个数据
    //printf("after1\n");
    //printf("ret=%d cnt=%d\n",ret,spi_tx_cnt);
    

    if (ret < 1){
       printf("SPI ERROR: Reopen! ret=%d\n", ret);
       SPISetup(0,speed);//printf("can't send spi message\n");
    }
    else
    {
        //printf("ret=%d\n",ret);
        for (int i = 0; i < SPI_SEND_MAX; i++)
        {
            data = rx[i];
            parser_timeout++;
            
            // Таймаут парсера - сбрасываем состояние если слишком долго парсим
            if (parser_timeout > 1000) {
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
                //printf("state 0 0x%X ",spi_rx_buf[0]);
                state = 2;
                spi_rx_buf[1] = data;
                parser_timeout = 0;
                //printf("state 1 0x%X ",data);
            }
            else if (state == 1 && data == 0xFF)
            {
                // Если получили еще один 0xFF, остаемся в состоянии 1
                // Это нормально, так как может быть много 0xFF подряд
                spi_rx_buf[0] = data;
                parser_timeout = 0;
            }
            else if (state == 2 && data > 0 && data < 0XF1)
            {
                state = 3;
                spi_rx_buf[2] = data;
                parser_timeout = 0;
                //printf("state 2 0x%X ",data);
            }
            else if (state == 3 && data < SPI_BUF_SIZE)
            {
                // Проверяем разумный размер пакета (должен быть ~111 байт)
                if (data < 50 || data > 150) {
                    state = 0;
                    parser_timeout = 0;
                    continue;
                }
                
                state = 4;
                spi_rx_buf[3] = data;
                _data_len2 = data;
                _data_cnt2 = 0;
                parser_timeout = 0;
                
                //printf("state 3 0x%X ",data);
            }
            else if (state == 4 && _data_len2 > 0)
            {
                _data_len2--;
                spi_rx_buf[4 + _data_cnt2++] = data;
                if (_data_len2 == 0) {
                    state = 5;
                    parser_timeout = 0;
                }
                //printf("state 4 0x%X ",data);
            }
            else if (state == 5)
            {
                state = 0;
                spi_rx_buf[4 + _data_cnt2] = data;
                parser_timeout = 0;
                
                slave_rx(spi_rx_buf, _data_cnt2 + 5);
                //printf("state 5 0x%X ",data);
            }
            else {
                
                // Если получили 0xFF, сразу переходим в состояние 1
                if (data == 0xFF) {
                    state = 1;
                    spi_rx_buf[0] = data;
                } else {
                    state = 0;
                }
            }
            // printf("%02x ",rx[i]); 
        }
        // printf("\n");
    }
    //printf("after2\n");
}




class Motor_control : public rclcpp::Node {
public:
  Motor_control()
  : rclcpp::Node("dual_io_node") {
    // Declare parameters with default values


    
    char buf_mem[MEM_SIZE]={1,2};
    
    RCLCPP_INFO(this->get_logger(), "Hardware::Thread_SPI started");
    Cycle_Time_Init();
    fd=SPISetup(0,speed); //初始化SPI通道0，并设置为最大速度500000hz
    if(fd==-1){
        RCLCPP_ERROR(this->get_logger(), "init spi failed!");
        return;
    }
    imu_pub_ = this->create_publisher<hardware_msg::msg::Imu>("imu/data", 10);
    motors_states_pub_ = this->create_publisher<hardware_msg::msg::MotorsStates>("motors/states", 10);
    motor_data_pub_ = this->create_publisher<hardware_msg::msg::MotorData>("motor/data", 10);
    joint_state_pub_ = this->create_publisher<sensor_msgs::msg::JointState>("/robot_joints", 10);

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
      "joint_r_ankle"
    };

    // Subscribers (make them members with empty callbacks)
    motors_cmd_sub_ = this->create_subscription<hardware_msg::msg::MotorsCommands>(
      "motors/commands", 10,
      std::bind(&Motor_control::on_motors_commands, this, std::placeholders::_1)
    );
    board_params_sub_ = this->create_subscription<hardware_msg::msg::BoardParameters>(
      "control_board/commands", 10,
      std::bind(&Motor_control::on_board_parameters, this, std::placeholders::_1)
    );
    imu_params_sub_ = this->create_subscription<hardware_msg::msg::ImuParameters>(
      "imu/commands", 10,
      std::bind(&Motor_control::on_imu_parameters, this, std::placeholders::_1)
    );
    motor_params_sub_ = this->create_subscription<hardware_msg::msg::MotorParameters>(
      "motor/params", 10,
      std::bind(&Motor_control::on_motor_parameters, this, std::placeholders::_1)
    );

    // Timer: publish default messages at 5 Hz
    using namespace std::chrono_literals;
    timer_ = this->create_wall_timer(1ms, std::bind(&Motor_control::on_timer, this));
  }

private:
  // Subscribers
  rclcpp::Subscription<hardware_msg::msg::MotorsCommands>::SharedPtr motors_cmd_sub_;
  rclcpp::Subscription<hardware_msg::msg::BoardParameters>::SharedPtr board_params_sub_;
  rclcpp::Subscription<hardware_msg::msg::ImuParameters>::SharedPtr imu_params_sub_;
  rclcpp::Subscription<hardware_msg::msg::MotorParameters>::SharedPtr motor_params_sub_;

  // Publishers
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr value_pub_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr flag_pub_;
  rclcpp::Publisher<hardware_msg::msg::Imu>::SharedPtr imu_pub_;
  rclcpp::Publisher<hardware_msg::msg::MotorsStates>::SharedPtr motors_states_pub_;
  rclcpp::Publisher<hardware_msg::msg::MotorData>::SharedPtr motor_data_pub_;
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_pub_;
  std::vector<std::string> joint_names_;

  // Empty subscriber callbacks
  void on_motors_commands(const hardware_msg::msg::MotorsCommands::SharedPtr msg) {
    spi_tx.q_set[MOTOR_ID] = msg->target_pos;
    spi_tx.dq_set[MOTOR_ID] = msg->target_vel;
    spi_tx.tau_ff[MOTOR_ID] = msg->target_trq;
    
    // Логирование полученных команд
    RCLCPP_INFO(this->get_logger(), 
        "Received motor commands - Motor ID: %d, Target Pos: %.3f, Target Vel: %.3f, Target Trq: %.3f",
        MOTOR_ID, 
        msg->target_pos, 
        msg->target_vel, 
        msg->target_trq);
    
    // Дополнительное отладочное логирование текущих значений в spi_tx
    RCLCPP_DEBUG(this->get_logger(),
        "SPI TX values - q_set[%d]: %.3f, dq_set[%d]: %.3f, tau_ff[%d]: %.3f",
        MOTOR_ID, spi_tx.q_set[MOTOR_ID],
        MOTOR_ID, spi_tx.dq_set[MOTOR_ID], 
        MOTOR_ID, spi_tx.tau_ff[MOTOR_ID]);
  }

  void on_board_parameters(const hardware_msg::msg::BoardParameters::SharedPtr msg) { 
    spi_tx.beep_state=msg->beep_state;

  }
  void on_imu_parameters(const hardware_msg::msg::ImuParameters::SharedPtr msg) {
    mems.Acc_CALIBRATE=msg->acc_calibrate;
    mems.Gyro_CALIBRATE=msg->gyro_calibrate;
    mems.Mag_CALIBRATE=msg->msg_calibrate;

   }
  void on_motor_parameters(const hardware_msg::msg::MotorParameters::SharedPtr msg) {
    spi_tx.kp= msg->kp;
    spi_tx.kd= msg->kd;
    spi_tx.en_motor= msg->enable;
    spi_tx.reset_q= msg->reset_zero;
    spi_tx.reset_err= msg->reset_error;
   }

   
  void on_timer() {

    static int counter = 0;
    static auto last_time = this->now();
    
    transfer(1, 45);
    
    counter++;
    if (counter % 1000 == 0) { // Каждую секунду
        auto now = this->now();
        auto dt = (now - last_time).seconds();
        RCLCPP_INFO(this->get_logger(), "SPI frequency: %.1f Hz", 1000.0 / dt);
        last_time = now;
        
        // Логируем команды
        RCLCPP_INFO(this->get_logger(), "Motor command: pos=%.3f, vel=%.3f, trq=%.3f", 
                   spi_tx.q_set[MOTOR_ID], spi_tx.dq_set[MOTOR_ID], spi_tx.tau_ff[MOTOR_ID]);
    }

    transfer(1, 45);
    hardware_msg::msg::Imu imu_msg;
      imu_msg.roll = spi_rx.att[0];
      imu_msg.pitch = spi_rx.att[1];
      imu_msg.yaw = spi_rx.att[2];
      imu_pub_->publish(imu_msg);

      hardware_msg::msg::MotorsStates motors_states_msg;
      motors_states_msg.current_pos = spi_rx.q[MOTOR_ID];
      motors_states_msg.current_vel = spi_rx.dq[MOTOR_ID];
      motors_states_msg.current_trq = spi_rx.tau[MOTOR_ID];
      motors_states_pub_->publish(motors_states_msg);
      
      hardware_msg::msg::MotorData motor_data_msg;
      motor_data_msg.id = MOTOR_ID;
      motor_data_msg.connect = spi_rx.connect_motor[MOTOR_ID];
      motor_data_msg.motor_connected = spi_rx.connect_motor[MOTOR_ID];
      motor_data_msg.ready = spi_rx.ready[MOTOR_ID];
      motor_data_pub_->publish(motor_data_msg);
      // Publish JointState for URDF visualization
      sensor_msgs::msg::JointState js;
      js.header.stamp = this->get_clock()->now();
      js.name = joint_names_;
      js.position.assign(joint_names_.size(), 0.0);
      if (!joint_names_.empty()) {
        // joint_l_yaw is first
        js.position[0] = spi_rx.q[MOTOR_ID];
      }
      joint_state_pub_->publish(js);
      
  }

  
  //   RCLCPP_INFO(this->get_logger(), "Hardware::on_timer");
  //   std_msgs::msg::Float32 out_value_msg;
  //     out_value_msg.data = 0.0F;
  //     value_pub_->publish(out_value_msg);

  //     std_msgs::msg::Bool out_flag_msg;
  //     out_flag_msg.data = false;
  //     flag_pub_->publish(out_flag_msg);

  // }
  // Params and timer
  rclcpp::TimerBase::SharedPtr timer_;
  int fd = 0;
};

int main(int argc, char ** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Motor_control>());
  rclcpp::shutdown();
  return 0;
}
