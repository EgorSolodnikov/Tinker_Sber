#include "../Inc/can.h"

#include <math.h>
#include  "filter.h"
#include "time.h"

_LEG_MOTOR leg_motor;
motor_measure_t motor_chassis[10];
uint32_t can1_rx_id;
int can_rx_over[5], can_rx_cnt[5];
u8 canbuft1[8], canbufr1[8];
#define u32 uint32_t
#define USE_ID_CHECK1 0
#if CAN_NART_SEL== DISABLE || CAN_FB_SYNC //unuse
int CAN_SAFE_DELAY = 166; //us  ��֤���ڵ���ճ�ʱС��11
#else
int CAN_SAFE_DELAY = 130; //us  ��֤���ڵ���ճ�ʱС��11
#endif
float k_t_i[10] = {1};

u32 slave_id1 = 99;
float cnt_rst1 = 0;
int can1_rx_cnt;
int can_rx_cnt_all[6] = {0};

float To_180_degrees(float x) {
    return (x > 180 ? (x - 360) : (x < -180 ? (x + 360) : x));
}


union RV_TypeConvert {
    float to_float;
    int to_int;
    unsigned int to_uint;
    uint8_t buf[4];
} rv_type_convert;

float uint_to_float_rv(int x_int, float x_min, float x_max, int bits) {
    /// converts unsigned int to float, given range and number of bits ///
    float span = x_max - x_min;
    float offset = x_min;
    return ((float) x_int) * span / ((float) ((1 << bits) - 1)) + offset;
}


void data_can_rv_anal(motor_measure_t *ptr, float q_rx, float v_rx, float t_rx) {
    char i;
    char sum = 0;
    float dt = Get_Cycle_T(ptr->param.id);
    float t_temp = 0;
    uint16_t _cnt = 0, cnt_reg;
    int16_t _temp;
    int inv_q_flag = 1;
    if (!ptr->param.q_flag)
        inv_q_flag = -1;
    //id=buf_rx[0];
    ptr->param.connect = 1;
    ptr->param.loss_cnt = 0;
    ptr->param.rx_dt = dt;

    ptr->param.total_angle_out = q_rx * 57.3;
    ptr->t_now_flt = ptr->param.real_current = t_rx * ptr->param.t_inv_flag_measure * inv_q_flag;
    ptr->param.cnt_rotate = (int) (ptr->param.total_angle_out) / 180;
    float total_angle_out_single = fmod(
        (float) (ptr->param.total_angle_out), 360);
    ptr->param.total_angle_out_single = total_angle_out_single;

    ptr->q_now = inv_q_flag * To_180_degrees(ptr->param.total_angle_out_single);
    ptr->q_now_flt = To_180_degrees(ptr->q_now + ptr->param.q_reset_angle);

    ptr->qd_now = To_180_degrees(ptr->q_now - ptr->param.q_now_reg) / dt;
    ptr->qd_now_flt = Moving_Median(ptr->param.id, 3, ptr->qd_now);

    ptr->param.q_now_reg = ptr->q_now;
    ptr->param.qd_now_reg = ptr->qd_now;
}


MotorCommFbd motor_comm_fbd;
OD_Motor_Msg rv_motor_msg[14];
uint16_t motor_id_check = 0;


void RV_can_data_repack(CAN_RxHeaderTypeDef *RxMessage, uint8_t comm_mode, uint8_t sel, uint8_t *Data) {
    uint8_t motor_id_t = 0;
    uint8_t ack_status = 0;
    int pos_int = 0;
    int spd_int = 0;
    int cur_int = 0;
    if (RxMessage->StdId == 0x7FF) {
        if (Data[2] != 0x01) //determine whether it is a motor feedback instruction
            return; //it is not a motor feedback instruction
        if ((Data[0] == 0xff) && (Data[1] == 0xFF)) {
            motor_comm_fbd.motor_id = Data[3] << 8 | Data[4];
            motor_comm_fbd.motor_fbd = 0x01;
        } else if ((Data[0] == 0x80) && (Data[1] == 0x80)) //inquire failed
        {
            motor_comm_fbd.motor_id = 0;
            motor_comm_fbd.motor_fbd = 0x80;
        } else if ((Data[0] == 0x7F) && (Data[1] == 0x7F)) //reset ID succeed
        {
            motor_comm_fbd.motor_id = 1;
            motor_comm_fbd.motor_fbd = 0x05;
        } else {
            motor_comm_fbd.motor_id = Data[0] << 8 | Data[1];
            motor_comm_fbd.motor_fbd = Data[3];
        }
    } else if (comm_mode == 0x00) //Response mode
    {
        ack_status = Data[0] >> 5;
        motor_id_t = RxMessage->StdId - 1;
        motor_id_check = RxMessage->StdId;
        rv_motor_msg[motor_id_t].motor_id = motor_id_t;
        rv_motor_msg[motor_id_t].error = Data[0] & 0x1F;
        if (ack_status == 1) //response frame 1 ----->rx here
        {
            pos_int = Data[1] << 8 | Data[2];
            spd_int = Data[3] << 4 | (Data[4] & 0xF0) >> 4;
            cur_int = (Data[4] & 0x0F) << 8 | Data[5];

            rv_motor_msg[motor_id_t].angle_actual_rad = uint_to_float_rv(pos_int,POS_MIN,POS_MAX, 16);
            rv_motor_msg[motor_id_t].speed_actual_rad = uint_to_float_rv(spd_int,SPD_MIN,SPD_MAX, 12);
            rv_motor_msg[motor_id_t].current_actual_float = uint_to_float_rv(cur_int,I_MIN,I_MAX, 12);
            rv_motor_msg[motor_id_t].temperature = (Data[6] - 50) / 2;

            int id = rv_motor_msg[motor_id_t].motor_id; //<----------------------------
            //			float i_2_t=0.67;//0.62-----------------???????? ??????????????T?????
            if (id >= 0 && id < 14) {
                if (sel == 0) {
                    data_can_rv_anal(&motor_chassis[id],
                                     rv_motor_msg[id].angle_actual_rad, //?????
                                     rv_motor_msg[id].speed_actual_rad,
                                     rv_motor_msg[id].current_actual_float * k_t_i[id]);
                } else {
                    data_can_rv_anal(&motor_chassis[id + 7],
                                     rv_motor_msg[id].angle_actual_rad, //?????
                                     rv_motor_msg[id].speed_actual_rad,
                                     rv_motor_msg[id].current_actual_float * k_t_i[id + 7]);
                }
            }
        } else if (ack_status == 2) //response frame 2
        {
            rv_type_convert.buf[0] = Data[4];
            rv_type_convert.buf[1] = Data[3];
            rv_type_convert.buf[2] = Data[2];
            rv_type_convert.buf[3] = Data[1];
            rv_motor_msg[motor_id_t].angle_actual_float = rv_type_convert.to_float;
            rv_motor_msg[motor_id_t].current_actual_int = Data[5] << 8 | Data[6];
            rv_motor_msg[motor_id_t].temperature = (Data[7] - 50) / 2;
            rv_motor_msg[motor_id_t].current_actual_float = rv_motor_msg[motor_id_t].current_actual_int / 100.0f;
        } else if (ack_status == 3) //response frame 3
        {
            rv_type_convert.buf[0] = Data[4];
            rv_type_convert.buf[1] = Data[3];
            rv_type_convert.buf[2] = Data[2];
            rv_type_convert.buf[3] = Data[1];
            rv_motor_msg[motor_id_t].speed_actual_float = rv_type_convert.to_float;
            rv_motor_msg[motor_id_t].current_actual_int = Data[5] << 8 | Data[6];
            rv_motor_msg[motor_id_t].temperature = (Data[7] - 50) / 2;
            rv_motor_msg[motor_id_t].current_actual_float = rv_motor_msg[motor_id_t].current_actual_int / 100.0f;
        } else if (ack_status == 4) //response frame 4
        {
            if (RxMessage->DLC != 3) return;
            motor_comm_fbd.INS_code = Data[1];
            motor_comm_fbd.motor_fbd = Data[2];
        } else if (ack_status == 5) //response frame 5
        {
            motor_comm_fbd.INS_code = Data[1];
            if (motor_comm_fbd.INS_code == 1 & RxMessage->DLC == 6) //get position
            {
                rv_type_convert.buf[0] = Data[5];
                rv_type_convert.buf[1] = Data[4];
                rv_type_convert.buf[2] = Data[3];
                rv_type_convert.buf[3] = Data[2];
                rv_motor_msg[motor_id_t].angle_actual_float = rv_type_convert.to_float;
            } else if (motor_comm_fbd.INS_code == 2 & RxMessage->DLC == 6) //get speed
            {
                rv_type_convert.buf[0] = Data[5];
                rv_type_convert.buf[1] = Data[4];
                rv_type_convert.buf[2] = Data[3];
                rv_type_convert.buf[3] = Data[2];
                rv_motor_msg[motor_id_t].speed_actual_float = rv_type_convert.to_float;
            } else if (motor_comm_fbd.INS_code == 3 & RxMessage->DLC == 6) //get current
            {
                rv_type_convert.buf[0] = Data[5];
                rv_type_convert.buf[1] = Data[4];
                rv_type_convert.buf[2] = Data[3];
                rv_type_convert.buf[3] = Data[2];
                rv_motor_msg[motor_id_t].current_actual_float = rv_type_convert.to_float;
            } else if (motor_comm_fbd.INS_code == 4 & RxMessage->DLC == 6) //get power
            {
                rv_type_convert.buf[0] = Data[5];
                rv_type_convert.buf[1] = Data[4];
                rv_type_convert.buf[2] = Data[3];
                rv_type_convert.buf[3] = Data[2];
                rv_motor_msg[motor_id_t].power = rv_type_convert.to_float;
            } else if (motor_comm_fbd.INS_code == 5 & RxMessage->DLC == 4) //get acceleration
            {
                rv_motor_msg[motor_id_t].acceleration = Data[2] << 8 | Data[3];
            } else if (motor_comm_fbd.INS_code == 6 & RxMessage->DLC == 4) //get linkage_KP
            {
                rv_motor_msg[motor_id_t].linkage_KP = Data[2] << 8 | Data[3];
            } else if (motor_comm_fbd.INS_code == 7 & RxMessage->DLC == 4) //get speed_KI
            {
                rv_motor_msg[motor_id_t].speed_KI = Data[2] << 8 | Data[3];
            } else if (motor_comm_fbd.INS_code == 8 & RxMessage->DLC == 4) //get feedback_KP
            {
                rv_motor_msg[motor_id_t].feedback_KP = Data[2] << 8 | Data[3];
            } else if (motor_comm_fbd.INS_code == 9 & RxMessage->DLC == 4) //get feedback_KD
            {
                rv_motor_msg[motor_id_t].feedback_KD = Data[2] << 8 | Data[3];
            }
        }
    } else if (comm_mode == 0x01) //automatic feedback mode
    {
        motor_id_t = RxMessage->StdId - 0x205;
        rv_motor_msg[motor_id_t].angle_actual_int = (uint16_t) (Data[0] << 8 | Data[1]);
        rv_motor_msg[motor_id_t].speed_actual_int = (int16_t) (Data[2] << 8 | Data[3]);
        rv_motor_msg[motor_id_t].current_actual_int = (Data[4] << 8 | Data[5]);
        rv_motor_msg[motor_id_t].temperature = Data[6];
        rv_motor_msg[motor_id_t].error = Data[7];
    }
}


void CAN_motor_init(void) {
    char i;

    for (i = 0; i < 10; i++) {
        leg_motor.connect = 0;
        leg_motor.motor_en = 0;
        leg_motor.motor_mode = MOTOR_MODE_T; //  Ŀǰ��������ģʽ

        reset_current_cmd(i);

        motor_chassis[i].max_t = leg_motor.max_t[i] = 120; //Nm �������

        motor_chassis[i].stiff = 1.0;
        motor_chassis[i].kp = 0.5;
        motor_chassis[i].kd = 0.1;
    }
}


char can_rx_t1[10];

void CAN1_Handler(void) {
    int i;
    uint8_t Data[8];
    CAN_RxHeaderTypeDef pRxHeader; //declare header for message reception
    HAL_CAN_GetRxMessage(CAN1, CAN_RX_FIFO0, &pRxHeader, Data);
    can_rx_t1[0] = pRxHeader.StdId;
    can_rx_t1[1] = Data[0];
    can_rx_t1[2] = Data[1];
    can_rx_t1[3] = Data[2];
    can_rx_t1[4] = Data[3];
    can_rx_t1[5] = Data[4];
    can_rx_t1[6] = Data[5];
    can_rx_t1[7] = Data[6];
    can_rx_t1[8] = Data[7];

    // Frame DMG
    // CMD    | nodeID
    // 7 bits | 4 bits
    uint32_t frameID = pRxHeader.StdId;
    uint32_t cmd = (frameID >> 4);
    uint32_t nodeID = (frameID & 0xF) - 1;

    //----------------------------MIT  ���CAN1 ID��1��ʼ  ˫�㣺CAN1��Ӧ����  �����Ӧ����ǰ ��ǰ
    if ((motor_chassis[0].motor.type < EC_1) &&
        (pRxHeader.IDE == CAN_ID_STD) //��׼֡��
        && (pRxHeader.IDE == 0x00000000U) //TODO Тут хардкод смотри зависимость платформы
        && ((pRxHeader.DLC == 6 || pRxHeader.DLC == 8))) /* ���ݳ���Ϊ8 */
    {
        if (Data[0] == 0 + 1 || Data[0] == 0 + 1 + 0x10) {
            data_can_mit_anal(&motor_chassis[0], Data);
            leg_motor.q_now[0] = motor_chassis[0].q_now_flt;
            leg_motor.qd_now[0] = motor_chassis[0].qd_now_flt;
            leg_motor.t_now[0] = motor_chassis[0].t_now_flt;
        } else if (Data[0] == 1 + 1 || Data[0] == 1 + 1 + 0x10) {
            data_can_mit_anal(&motor_chassis[1], Data);
            leg_motor.q_now[1] = motor_chassis[1].q_now_flt;
            leg_motor.qd_now[1] = motor_chassis[1].qd_now_flt;
            leg_motor.t_now[1] = motor_chassis[1].t_now_flt;
        } else if (Data[0] == 2 + 1 || Data[0] == 2 + 1 + 0x10) {
            data_can_mit_anal(&motor_chassis[2], Data);
            leg_motor.q_now[2] = motor_chassis[2].q_now_flt;
            leg_motor.qd_now[2] = motor_chassis[2].qd_now_flt;
            leg_motor.t_now[2] = motor_chassis[2].t_now_flt;
        } else if (Data[0] == 3 + 1 || Data[0] == 3 + 1 + 0x10) {
            data_can_mit_anal(&motor_chassis[3], Data);
            leg_motor.q_now[3] = motor_chassis[3].q_now_flt;
            leg_motor.qd_now[3] = motor_chassis[3].qd_now_flt;
            leg_motor.t_now[3] = motor_chassis[3].t_now_flt;
        } else if (Data[0] == 4 + 1 || Data[0] == 4 + 1 + 0x10) {
            data_can_mit_anal(&motor_chassis[4], Data);
            leg_motor.q_now[4] = motor_chassis[4].q_now_flt;
            leg_motor.qd_now[4] = motor_chassis[4].qd_now_flt;
            leg_motor.t_now[4] = motor_chassis[4].t_now_flt;
        } else if (Data[0] == 5 + 1 || Data[0] == 5 + 1 + 0x10) {
            data_can_mit_anal(&motor_chassis[5], Data);
            leg_motor.q_now[5] = motor_chassis[5].q_now_flt;
            leg_motor.qd_now[5] = motor_chassis[5].qd_now_flt;
            leg_motor.t_now[5] = motor_chassis[5].t_now_flt;
        } else if (Data[0] == 6 + 1 || Data[0] == 6 + 1 + 0x10) {
            data_can_mit_anal(&motor_chassis[6], Data);
            leg_motor.q_now[6] = motor_chassis[6].q_now_flt;
            leg_motor.qd_now[6] = motor_chassis[6].qd_now_flt;
            leg_motor.t_now[6] = motor_chassis[6].t_now_flt;
        }
    }

    //----------------------------RVϵ�� VESC����
    if (
        (pRxHeader.IDE == CAN_ID_STD) //��׼֡��
        && (pRxHeader.IDE == 0x00000000U) //TODO Тут хардкод смотри зависимость платформы
        && ((pRxHeader.DLC >= 6)) &&
        motor_chassis[0].motor.type >= EC_1) /* ���ݳ���Ϊ8 */
    {
        RV_can_data_repack(&pRxHeader, 0, 0, Data);
        for (i = 0; i < 10; i++) {
            leg_motor.q_now[i] = motor_chassis[i].q_now_flt;
            leg_motor.qd_now[i] = motor_chassis[i].qd_now_flt;
            leg_motor.t_now[i] = motor_chassis[i].t_now_flt;
        }
    }

    can1_rx_cnt++;
}


uint32_t can2_rx_id;
u8 canbuft2[8];
u8 canbufr2[8];
#define USE_ID_CHECK2 0
u32 slave_id2 = 99;
float cnt_rst2;
int can2_rx_cnt;
#if CAN2_RX0_INT_ENABLE
void CAN2_Handler(void) {
    int ge, shi, bai;
    static int cnt_rx, led_flag, id = 0;
    int i = 0;
    uint8_t Data[8];
    CAN_RxHeaderTypeDef pRxHeader; //declare header for message reception
    HAL_CAN_GetRxMessage(CAN1, CAN_RX_FIFO0, &pRxHeader, Data);
    cnt_rst2 = 0;
    if ((motor_chassis[0].motor.type < EC_1) &&
        (pRxHeader.IDE == CAN_ID_STD) //��׼֡��
        && (pRxHeader.IDE == 0x00000000U) //����֡��
        && ((pRxHeader.DLC == 6 || pRxHeader.DLC == 8))) /* ���ݳ���Ϊ8 */
    {
        if (Data[0] == 0 + 1 || Data[0] == 0 + 1 + 0x10) {
            data_can_mit_anal(&motor_chassis[5 + 0], Data);
            leg_motor.q_now[5 + 0] = motor_chassis[5 + 0].q_now_flt;
            leg_motor.qd_now[5 + 0] = motor_chassis[5 + 0].qd_now_flt;
            leg_motor.t_now[5 + 0] = motor_chassis[5 + 0].t_now_flt;
        } else if (Data[0] == 1 + 1 || Data[0] == 1 + 1 + 0x10) {
            data_can_mit_anal(&motor_chassis[5 + 1], Data);
            leg_motor.q_now[5 + 1] = motor_chassis[5 + 1].q_now_flt;
            leg_motor.qd_now[5 + 1] = motor_chassis[5 + 1].qd_now_flt;
            leg_motor.t_now[5 + 1] = motor_chassis[5 + 1].t_now_flt;
        } else if (Data[0] == 2 + 1 || Data[0] == 2 + 1 + 0x10) {
            data_can_mit_anal(&motor_chassis[5 + 2], Data);
            leg_motor.q_now[5 + 2] = motor_chassis[5 + 2].q_now_flt;
            leg_motor.qd_now[5 + 2] = motor_chassis[5 + 2].qd_now_flt;
            leg_motor.t_now[5 + 2] = motor_chassis[5 + 2].t_now_flt;
        } else if (Data[0] == 3 + 1 || Data[0] == 3 + 1 + 0x10) {
            data_can_mit_anal(&motor_chassis[5 + 3], Data);
            leg_motor.q_now[5 + 3] = motor_chassis[5 + 3].q_now_flt;
            leg_motor.qd_now[5 + 3] = motor_chassis[5 + 3].qd_now_flt;
            leg_motor.t_now[5 + 3] = motor_chassis[5 + 3].t_now_flt;
        } else if (Data[0] == 4 + 1 || Data[0] == 4 + 1 + 0x10) {
            data_can_mit_anal(&motor_chassis[5 + 4], Data);
            leg_motor.q_now[5 + 4] = motor_chassis[5 + 4].q_now_flt;
            leg_motor.qd_now[5 + 4] = motor_chassis[5 + 4].qd_now_flt;
            leg_motor.t_now[5 + 4] = motor_chassis[5 + 4].t_now_flt;
        } else if (Data[0] == 5 + 1 || Data[0] == 5 + 1 + 0x10) {
            data_can_mit_anal(&motor_chassis[5 + 5], Data);
            leg_motor.q_now[5 + 5] = motor_chassis[5 + 5].q_now_flt;
            leg_motor.qd_now[5 + 5] = motor_chassis[5 + 5].qd_now_flt;
            leg_motor.t_now[5 + 5] = motor_chassis[5 + 5].t_now_flt;
        } else if (Data[0] == 6 + 1 || Data[0] == 6 + 1 + 0x10) {
            data_can_mit_anal(&motor_chassis[5 + 6], Data);
            leg_motor.q_now[5 + 6] = motor_chassis[5 + 6].q_now_flt;
            leg_motor.qd_now[5 + 6] = motor_chassis[5 + 6].qd_now_flt;
            leg_motor.t_now[5 + 6] = motor_chassis[5 + 6].t_now_flt;
        }
    }

    //----------------------------RVϵ�� VESC����
    if (
        (pRxHeader.IDE == CAN_ID_STD) //��׼֡��
        && (pRxHeader.IDE == 0x00000000U) //����֡��
        && ((pRxHeader.DLC >= 6)) &&
        motor_chassis[0].motor.type >= EC_1) /* ���ݳ���Ϊ8 */
    {
        RV_can_data_repack(&pRxHeader, 0, 1, Data); //can2
        for (i = 0; i < 10; i++) {
            leg_motor.q_now[i] = motor_chassis[i].q_now_flt;
            leg_motor.qd_now[i] = motor_chassis[i].qd_now_flt;
            leg_motor.t_now[i] = motor_chassis[i].t_now_flt;
        }
    }

    can2_rx_cnt++;
}
#endif

//----------------------------------------------------------------------------------------------------------------------
void reset_current_cmd(char id) //�������
{
    leg_motor.set_t[id] = 0;
    leg_motor.set_i[id] = 0;
}
#import "mit_link.h"
void CAN_motor_sm(float dt) {
    char i = 0;
    char id_cnt = 0;

    if (motor_chassis[0].motor.type >= EC_1) //----------ECOS��� motor.type �Ƕ�ȡ����λ������
    {
        /*if (!can_cmd_usb_disable /*|| ocu_connect == 0#1#) //usbû����
        {
            for (i = 0; i < 10; i++)
                motor_chassis[i].en_cmd = leg_motor.motor_en;
            mit_bldc_thread_rv(leg_motor.motor_en, dt);
        } else {*/
            for (i = 0; i < 10; i++) {
                motor_chassis[i].en_cmd = motor_chassis[i].en_cmd_ocu;
                mit_bldc_thread_rv(motor_chassis[0].en_cmd_ocu, dt);
            }
      //  }
    } else //---------------------------------------------DM���
    {
        /*if (!can_cmd_usb_disable /*|| ocu_connect == 0#1#) //usbû����
        {
            for (i = 0; i < 10; i++)
                motor_chassis[i].en_cmd = leg_motor.motor_en;

            mit_bldc_thread(leg_motor.motor_en, dt);
        } else {*/
            for (i = 0; i < 10; i++)
                motor_chassis[i].en_cmd = motor_chassis[i].en_cmd_ocu;

            mit_bldc_thread(motor_chassis[0].en_cmd_ocu, dt);
        //}
    }
}
