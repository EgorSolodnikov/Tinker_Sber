#include "../Inc/can.h"
#include "../Inc/filter.h"
#include "math.h"
#include "../Inc/time.h"
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )
char state_mit[4] = {0};

float P_MIN_CAN_MIT[10] = {-12.5f, -12.5f, -12.5f};
float P_MAX_CAN_MIT[10] = {12.5f, 12.5f, 12.5f};
float V_MIN_CAN_MIT[10] = {-38.2f, -38.2f, -38.2f};
float V_MAX_CAN_MIT[10] = {38.2f, 38.2f, 38.2f};
float KP_MIN_CAN_MIT[10] = {0.0f, 0.0f, 0.0f};
float KP_MAX_CAN_MIT[10] = {500.0f, 500.0f, 500.0f};
float KD_MIN_CAN_MIT[10] = {0.0f, 0.0f, 0.0f};
float KD_MAX_CAN_MIT[10] = {5.0f, 5.0f, 5.0f};
float T_MIN_CAN_MIT[10] = {-12.0f, -12.0f, -12.0f};
float T_MAX_CAN_MIT[10] = {12.0f, 12.0f, 12.0f};


float fmaxf_mit(float x, float y) {
    /// Returns maximum of x, y ///
    return (((x) > (y)) ? (x) : (y));
}

float fminf_mit(float x, float y) {
    /// Returns minimum of x, y ///
    return (((x) < (y)) ? (x) : (y));
}

int float_to_uint_mit(float x, float x_min, float x_max, int bits) {
    /// Converts a float to an unsigned int, given range and number of bits ///
    float span = x_max - x_min;
    float offset = x_min;
    x = LIMIT(x, x_min, x_max);
    return (int) ((x - offset) * ((float) ((1 << bits) - 1)) / span);
}

float uint_to_float_mit(int x_int, float x_min, float x_max, int bits) {
    /// converts unsigned int to float, given range and number of bits ///
    float span = x_max - x_min;
    float offset = x_min;
    return ((float) x_int) * span / ((float) ((1 << bits) - 1)) + offset;
}

int float_to_uint(float x_float, float x_min, float x_max, int bits) {
    /* Converts a float to an unsigned int, given range and number of bits */
    float span = x_max - x_min;
    float offset = x_min;
    return (int) ((x_float - offset) * ((float) ((1 << bits) - 1)) / span);
}

uint16_t float_to_uint_gim(float v, float v_min, float v_max, uint32_t width) {
    float temp;
    int32_t utemp;
    temp = ((v - v_min) / (v_max - v_min)) * ((float) width);
    utemp = (int32_t) temp;
    if (utemp < 0)utemp = 0;
    if (utemp > width)utemp = width;
    return utemp;
}

u8 mit_motor_mode_en(char id, char en) {
    //ʹ�ܵ��
    uint32_t mbox;
    uint16_t i = 0;
    uint8_t Data[8];
    CAN_TxHeaderTypeDef TxMessage;
    if (id < 5)
        TxMessage.StdId = 0x00 + id + 1; // ��׼��ʶ��Ϊ0
    else
        TxMessage.StdId = 0x00 + id + 1 - 5;

    TxMessage.ExtId = 0x00; //0x200;	 // ������չ��ʾ����29λ��
    TxMessage.IDE = 0; // ʹ����չ��ʶ��
    TxMessage.RTR = 0; // ��Ϣ����Ϊ����֡��һ֡8λ
    TxMessage.DLC = 8; // ������֡��Ϣ
    Data[0] = 0xFF; //300??
    Data[1] = 0xFF;
    Data[2] = 0xFF;
    Data[3] = 0xFF;
    Data[4] = 0xFF;
    Data[5] = 0xFF;
    Data[6] = 0xFF;
    if (en)
        Data[7] = 0xFC;
    else
        Data[7] = 0xFD;

    if (id < 5) {
        while (!HAL_CAN_GetTxMailboxesFreeLevel(&hcan1));
        HAL_CAN_AddTxMessage(&hcan1, &TxMessage, Data, &mbox);
        //TODO Надо тестить потому что раньше была блокирующая передача и стоит проверять возможность отправки
        //TODO Стоит добавить потом ограничение на кол-во попыток
    }
    while (!HAL_CAN_GetTxMailboxesFreeLevel(&hcan2));
    return HAL_CAN_AddTxMessage(&hcan2, &TxMessage, Data, &mbox); //�ȴ����ͽ���
}

u8 mit_set_pos_zero(char id) {
    //������λ
    u8 mbox;
    u8 Data[8];
    uint16_t i = 0;
    CAN_TxHeaderTypeDef TxMessage;
    if (id < 5)
        TxMessage.StdId = 0x00 + id + 1; // ��׼��ʶ��Ϊ0
    else
        TxMessage.StdId = 0x00 + id + 1 - 5;

    TxMessage.ExtId = 0x00; //0x200;	 // ������չ��ʾ����29λ��
    TxMessage.IDE = 0; // ʹ����չ��ʶ��
    TxMessage.RTR = 0; // ��Ϣ����Ϊ����֡��һ֡8λ
    TxMessage.DLC = 8; // ������֡��Ϣ
    Data[0] = 0xFF; //300??
    Data[1] = 0xFF;
    Data[2] = 0xFF;
    Data[3] = 0xFF;
    Data[4] = 0xFF;
    Data[5] = 0xFF;
    Data[6] = 0xFF;
    Data[7] = 0xFE;

    if (id < 5) {
        while (!HAL_CAN_GetTxMailboxesFreeLevel(&hcan1));
        HAL_CAN_AddTxMessage(&hcan1, &TxMessage, Data, &mbox);
        //TODO Надо тестить потому что раньше была блокирующая передача и стоит проверять возможность отправки
    }
    while (!HAL_CAN_GetTxMailboxesFreeLevel(&hcan2));
    return HAL_CAN_AddTxMessage(&hcan2, &TxMessage, Data, &mbox); //�ȴ����ͽ���
}

int qd_mid_f_mit = 3;
uint16_t int_temp;
float over_reg1[1000] = {0};
float over_reg2[1000] = {0};
float over_reg3[1000] = {0};
int over_cnt1 = 0;
int over_cnt2 = 0;
int over_cnt3 = 0;
int en_over_save1 = 0;
int en_over_save2 = 0;
int en_over_save3 = 0;
float t_check_over = 12;
float err_dead = 1.2;

void data_can_mit_anal(motor_measure_t *ptr, uint8_t buf_rx[8]) //�����������
{
    float dt = Get_Cycle_T(ptr->param.id + 50);

    int inv_q_flag = 1;
    if (!ptr->param.q_flag)
        inv_q_flag = -1;

    ptr->param.connect = 1;
    ptr->param.loss_cnt = 0;
    ptr->param.rx_dt = dt;

    uint16_t p_int = (buf_rx[1] << 8) | buf_rx[2];
    uint16_t v_int = (buf_rx[3] << 4) | (buf_rx[4] >> 4);
    uint16_t i_int = ((buf_rx[4] & 0xF) << 8) | buf_rx[5];

    ptr->param.total_angle_out = uint_to_float_mit(p_int, P_MIN_CAN_MIT[ptr->param.id], P_MAX_CAN_MIT[ptr->param.id],
                                                   16) * 57.3;
    ptr->t_now_flt = uint_to_float_mit(i_int, -T_MAX_CAN_MIT[ptr->param.id], T_MAX_CAN_MIT[ptr->param.id], 12) * ptr->
                     param.t_inv_flag_measure * inv_q_flag;

    ptr->param.cnt_rotate = (int) (ptr->param.total_angle_out) / 180;
    float total_angle_out_single = fmod(
        (float) (ptr->param.total_angle_out), 360);
    ptr->param.total_angle_out_single = total_angle_out_single;

    ptr->q_now = inv_q_flag * To_180_degrees(ptr->param.total_angle_out_single);
    ptr->q_now_flt = To_180_degrees(ptr->q_now + ptr->param.q_reset_angle);

    ptr->qd_now = To_180_degrees(ptr->q_now - ptr->param.q_now_reg) / dt; //���ٶ�΢��  ʹ��TD��
    ptr->qd_now_flt = Moving_Median(ptr->param.id, qd_mid_f_mit, ptr->qd_now);

    ptr->param.q_now_reg = ptr->q_now;
    ptr->param.qd_now_reg = ptr->qd_now;
}

float v_des_ff[10];
float t_des_ff[10];
float k_spd_all = 5;

char data_can_mit_send(motor_measure_t *ptr) {
    //���Ϳ���ָ��
    u8 canbuft_mit1[20] = {0};
    int q_flag = 1;
    float set_q;

    if (ptr->param.q_flag)
        q_flag = 1;
    else
        q_flag = -1;
    if (ptr->cmd_mode == 2)
        ptr->set_q = LIMIT(ptr->set_q_test+ptr->set_q_test_bias, -180, 180);

#if EN_MIT_PID_INNER
    float temp = 0;
    if (ptr->param.q_reset_angle == 180) {
        if (ptr->set_q >= -180 && ptr->set_q <= -0) {
            if (ptr->param.q_flag)
                temp = 180 - fabs(ptr->set_q);
            else
                temp = -(180 - fabs(ptr->set_q));
        } else if (ptr->set_q <= 180 && ptr->set_q >= 0) {
            if (!ptr->param.q_flag)
                temp = 180 - fabs(ptr->set_q);
            else
                temp = -(180 - fabs(ptr->set_q));
        }
    } else {
        //-------------------------------------
        temp = q_flag * (ptr->set_q - ptr->param.q_reset_angle);
    }
    set_q = temp;
#endif

    ptr->param.set_q = set_q; //for record

    float set_dq = q_flag * ptr->set_qd / 57.3;
    float set_t = q_flag * ptr->set_t;

    float p_des = fminf_mit(fmaxf_mit(P_MIN_CAN_MIT[ptr->param.id], set_q / 57.3), P_MAX_CAN_MIT[ptr->param.id]);
    float v_des = fminf_mit(fmaxf_mit(V_MIN_CAN_MIT[ptr->param.id], set_dq), V_MAX_CAN_MIT[ptr->param.id]);
    float kp = fminf_mit(fmaxf_mit(KP_MIN_CAN_MIT[ptr->param.id], ptr->stiff * ptr->kp * EN_MIT_PID_INNER),
                         KP_MAX_CAN_MIT[ptr->param.id]);
    float kd = fminf_mit(fmaxf_mit(KD_MIN_CAN_MIT[ptr->param.id], ptr->stiff * ptr->kd * EN_MIT_PID_INNER),
                         KD_MAX_CAN_MIT[ptr->param.id]);
    float t_ff = fminf_mit(fmaxf_mit(T_MIN_CAN_MIT[ptr->param.id],LIMIT(set_t, -ptr->max_t, ptr->max_t)),
                           T_MAX_CAN_MIT[ptr->param.id]); //���շ��͵�����ǰ��
    t_des_ff[ptr->param.id] = t_ff;
    if (EN_MIT_PID_INNER == 0 || ptr->param.usb_cmd_mode == 2) //������ǰ��������ģʽ
        kp = kd = v_des = 0;

    if (ptr->param.control_mode == 1) {
        //ת��ģʽ7
        kp = 0;
        kd = LIMIT(kd, KD_MIN_CAN_MIT[ptr->param.id], KD_MAX_CAN_MIT[ptr->param.id]);
        v_des_ff[ptr->param.id] = v_des = LIMIT(set_dq*k_spd_all, V_MIN_CAN_MIT[ptr->param.id],
                                                V_MAX_CAN_MIT[ptr->param.id]); //butler
    }


    /// convert floats to unsigned ints ///
    uint16_t p_int = float_to_uint_mit(p_des, P_MIN_CAN_MIT[ptr->param.id], P_MAX_CAN_MIT[ptr->param.id], 16);
    uint16_t v_int = float_to_uint_mit(v_des, V_MIN_CAN_MIT[ptr->param.id], V_MAX_CAN_MIT[ptr->param.id], 12);
    uint16_t kp_int = float_to_uint_mit(kp, KP_MIN_CAN_MIT[ptr->param.id], KP_MAX_CAN_MIT[ptr->param.id], 12);
    uint16_t kd_int = float_to_uint_mit(kd, KD_MIN_CAN_MIT[ptr->param.id], KD_MAX_CAN_MIT[ptr->param.id], 12);
    uint16_t t_int = float_to_uint_mit(t_ff, T_MIN_CAN_MIT[ptr->param.id], T_MAX_CAN_MIT[ptr->param.id], 12);

    canbuft_mit1[0] = p_int >> 8;
    canbuft_mit1[1] = p_int & 0xFF;
    canbuft_mit1[2] = v_int >> 4;
    canbuft_mit1[3] = ((v_int & 0xF) << 4) | (kp_int >> 8);
    canbuft_mit1[4] = kp_int & 0xFF;
    canbuft_mit1[5] = kd_int >> 4;
    canbuft_mit1[6] = ((kd_int & 0xF) << 4) | (t_int >> 8);
    canbuft_mit1[7] = t_int & 0xff;

    u8 mbox;
    uint16_t i = 0;
    CAN_TxHeaderTypeDef TxMessage;
    if (ptr->param.id < 5)
        TxMessage.StdId = 0x00 + ptr->param.id + 1; // ��׼��ʶ��Ϊ0
    else
        TxMessage.StdId = 0x00 + ptr->param.id + 1 - 5;

    TxMessage.ExtId = 0x00; //0x200;	 // ������չ��ʾ����29λ��
    TxMessage.IDE = 0; // ʹ����չ��ʶ��
    TxMessage.RTR = 0; // ��Ϣ����Ϊ����֡��һ֡8λ
    TxMessage.DLC = 8; // ������֡��Ϣ


    if (ptr->param.id < 5) {
        while (!HAL_CAN_GetTxMailboxesFreeLevel(&hcan1));
        HAL_CAN_AddTxMessage(&hcan1, &TxMessage, canbuft_mit1, &mbox);
        //TODO Надо тестить потому что раньше была блокирующая передача и стоит проверять возможность отправки
        //TODO Стоит добавить потом ограничение на кол-во попыток
    }
    while (!HAL_CAN_GetTxMailboxesFreeLevel(&hcan2));
    return HAL_CAN_AddTxMessage(&hcan2, &TxMessage, canbuft_mit1, &mbox); //�ȴ����ͽ���
}

char data_can_sample_only(motor_measure_t *ptr) {
    //���ݲɼ�
    u8 canbuft1[8];
    /// limit data to be within bounds ///
    int q_flag = 1;
    if (ptr->param.q_flag)
        q_flag = 1;
    else
        q_flag = -1;
    float set_q = q_flag * To_180_degrees(ptr->set_q - To_180_degrees(ptr->param.q_reset_angle));
    ptr->param.set_q = set_q;

    float p_des = fminf_mit(fmaxf_mit(P_MIN_CAN_MIT[ptr->param.id], set_q / 57.3), P_MAX_CAN_MIT[ptr->param.id]);
    float v_des = fminf_mit(fmaxf_mit(V_MIN_CAN_MIT[ptr->param.id], 0 / 57.3), V_MAX_CAN_MIT[ptr->param.id]);
    float kp = fminf_mit(fmaxf_mit(KP_MIN_CAN_MIT[ptr->param.id], 0), KP_MAX_CAN_MIT[ptr->param.id]);
    float kd = fminf_mit(fmaxf_mit(KD_MIN_CAN_MIT[ptr->param.id], 0), KD_MAX_CAN_MIT[ptr->param.id]);
    float t_ff = fminf_mit(fmaxf_mit(T_MIN_CAN_MIT[ptr->param.id], 0), T_MAX_CAN_MIT[ptr->param.id]);
    /// convert floats to unsigned ints ///
    uint16_t p_int = float_to_uint_mit(p_des, P_MIN_CAN_MIT[ptr->param.id], P_MAX_CAN_MIT[ptr->param.id], 16);
    uint16_t v_int = float_to_uint_mit(v_des, V_MIN_CAN_MIT[ptr->param.id], V_MAX_CAN_MIT[ptr->param.id], 12);
    uint16_t kp_int = float_to_uint_mit(kp, KP_MIN_CAN_MIT[ptr->param.id], KP_MAX_CAN_MIT[ptr->param.id], 12);
    uint16_t kd_int = float_to_uint_mit(kd, KD_MIN_CAN_MIT[ptr->param.id], KD_MAX_CAN_MIT[ptr->param.id], 12);
    uint16_t t_int = float_to_uint_mit(t_ff, T_MIN_CAN_MIT[ptr->param.id], T_MAX_CAN_MIT[ptr->param.id], 12);

    canbuft1[0] = p_int >> 8;
    canbuft1[1] = p_int & 0xFF;
    canbuft1[2] = v_int >> 4;
    canbuft1[3] = ((v_int & 0xF) << 4) | (kp_int >> 8);
    canbuft1[4] = kp_int & 0xFF;
    canbuft1[5] = kd_int >> 4;
    canbuft1[6] = ((kd_int & 0xF) << 4) | (t_int >> 8);
    canbuft1[7] = t_int & 0xff;

    /*if (ptr->param.id >= 0x2) {
        q_flag = 1;
        printf("Test!");
    }*/

    u8 mbox;
    uint16_t i = 0;
    CAN_TxHeaderTypeDef TxMessage;
    if (ptr->param.id < 5)
        TxMessage.StdId = 0x00 + ptr->param.id + 1; // ��׼��ʶ��Ϊ0
    else
        TxMessage.StdId = 0x00 + ptr->param.id + 1 - 5;

    TxMessage.ExtId = 0x00; //0x200;	 // ������չ��ʾ����29λ��
    TxMessage.IDE = 0; // ʹ����չ��ʶ��
    TxMessage.RTR = 0; // ��Ϣ����Ϊ����֡��һ֡8λ
    TxMessage.DLC = 8; // ������֡��Ϣ

    if (ptr->param.id < 5) {
        while (!HAL_CAN_GetTxMailboxesFreeLevel(&hcan1));
        HAL_CAN_AddTxMessage(&hcan1, &TxMessage, canbuft1, &mbox);
        //TODO Надо тестить потому что раньше была блокирующая передача и стоит проверять возможность отправки
        //TODO Стоит добавить потом ограничение на кол-во попыток
    }
    while (!HAL_CAN_GetTxMailboxesFreeLevel(&hcan2));
    return HAL_CAN_AddTxMessage(&hcan2, &TxMessage, canbuft1, &mbox); //�ȴ����ͽ���
}

char en_test = 0;
char en_mit_out = 0;
int mit_delay_d[2] = {100, 200};
int mit_delay = 200; //300
int mit_connect_cnt = 0;
float test_cmd[2] = {3.5, 25};

void mit_bldc_thread(char en_all, float dt) {
    char i = 0;
    static char state_reg[4] = {0};
    static float auto_off_t = 99;
    static float timer_sin = 0;
    static int reg_cmd_mode;
#if 1 //Tinker
    motor_chassis[0].motor.type = DM_6006;
    motor_chassis[0].param.q_flag = 0;
    motor_chassis[1].motor.type = DM_8006;
    motor_chassis[1].param.q_flag = 1;
    motor_chassis[2].motor.type = DM_8006;
    motor_chassis[2].param.q_flag = 1;
    motor_chassis[3].motor.type = DM_8006;
    motor_chassis[3].param.q_flag = 0;
    motor_chassis[4].motor.type = DM_6006;
    motor_chassis[4].param.q_flag = 1;

    motor_chassis[6].motor.type = DM_6006;
    motor_chassis[6].param.q_flag = 0;
    motor_chassis[7].motor.type = DM_8006;
    motor_chassis[7].param.q_flag = 1;
    motor_chassis[8].motor.type = DM_8006;
    motor_chassis[8].param.q_flag = 0;
    motor_chassis[9].motor.type = DM_8006;
    motor_chassis[9].param.q_flag = 1;
    motor_chassis[10].motor.type = DM_6006;
    motor_chassis[10].param.q_flag = 0;

    for (i = 0; i < 1; i++)
        motor_chassis[i].param.control_mode = 0; //POS

#endif
    for (i = 0; i < 10; i++) {
        motor_chassis[i].param.id = i;
        switch (motor_chassis[i].motor.type) {
            case M_3508:
                P_MIN_CAN_MIT[i] = -12.566f;
                P_MAX_CAN_MIT[i] = 12.566f;
                V_MIN_CAN_MIT[i] = -50.0f;
                V_MAX_CAN_MIT[i] = 50.0f;
                KP_MIN_CAN_MIT[i] = 0.0f;
                KP_MAX_CAN_MIT[i] = 500.0f;
                KD_MIN_CAN_MIT[i] = 0.0f;
                KD_MAX_CAN_MIT[i] = 5.0f;

                T_MIN_CAN_MIT[i] = -5.0f;
                T_MAX_CAN_MIT[i] = 5.0f;
                motor_chassis[i].motor.anal_type = M_MIT;
                break;
            case DM_J4310:
                P_MIN_CAN_MIT[i] = -12.5f;
                P_MAX_CAN_MIT[i] = 12.5f;
                V_MIN_CAN_MIT[i] = -30.0f;
                V_MAX_CAN_MIT[i] = 30.0f;
                KP_MIN_CAN_MIT[i] = 0.0f;
                KP_MAX_CAN_MIT[i] = 500.0f;
                KD_MIN_CAN_MIT[i] = 0.0f;
                KD_MAX_CAN_MIT[i] = 5.0f;

                T_MIN_CAN_MIT[i] = -10.0f;
                T_MAX_CAN_MIT[i] = 10.0f;
                motor_chassis[i].motor.anal_type = M_MIT;
                break;
            case DM_6006: //С�ͱ�ƽ���
                P_MIN_CAN_MIT[i] = -12.5f;
                P_MAX_CAN_MIT[i] = 12.5f;
                V_MIN_CAN_MIT[i] = -45.0f;
                V_MAX_CAN_MIT[i] = 45.0f;
                KP_MIN_CAN_MIT[i] = 0.0f;
                KP_MAX_CAN_MIT[i] = 500.0f;
                KD_MIN_CAN_MIT[i] = 0.0f;
                KD_MAX_CAN_MIT[i] = 5.0f;

                T_MIN_CAN_MIT[i] = -12.0f;
                T_MAX_CAN_MIT[i] = 12.0f;
                motor_chassis[i].motor.anal_type = M_MIT;
                break;
            case DM_8006: //���ٱ�6 ���
                P_MIN_CAN_MIT[i] = -12.5f;
                P_MAX_CAN_MIT[i] = 12.5f;
                V_MIN_CAN_MIT[i] = -45.0f;
                V_MAX_CAN_MIT[i] = 45.0f;
                KP_MIN_CAN_MIT[i] = 0.0f;
                KP_MAX_CAN_MIT[i] = 500.0f;
                KD_MIN_CAN_MIT[i] = 0.0f;
                KD_MAX_CAN_MIT[i] = 5.0f;

                T_MIN_CAN_MIT[i] = -20.0f;
                T_MAX_CAN_MIT[i] = 20.0f;
                motor_chassis[i].motor.anal_type = M_MIT;
                break;
            default:
                P_MIN_CAN_MIT[i] = -12.5f;
                P_MAX_CAN_MIT[i] = 12.5f;
                V_MIN_CAN_MIT[i] = -30.0f;
                V_MAX_CAN_MIT[i] = 30.0f;
                KP_MIN_CAN_MIT[i] = 0.0f;
                KP_MAX_CAN_MIT[i] = 500.0f;
                KD_MIN_CAN_MIT[i] = 0.0f;
                KD_MAX_CAN_MIT[i] = 5.0f;

                T_MIN_CAN_MIT[i] = -10.0f;
                T_MAX_CAN_MIT[i] = 10.0f;
                motor_chassis[i].motor.anal_type = M_MIT;
                break;
        }
    }
    //test
    timer_sin += dt * test_cmd[0];
    mit_connect_cnt = 0;
    for (i = 0; i < 10; i++) {
        if (motor_chassis[i].param.connect)
            mit_connect_cnt++;
        if (reg_cmd_mode != motor_chassis[0].cmd_mode || !en_all) {
            motor_chassis[i].set_q_test_bias = motor_chassis[i].q_now_flt;
            timer_sin = 0;
        }
        if (motor_chassis[i].cmd_mode == 2) {
            motor_chassis[i].set_q_test = sin(timer_sin) * test_cmd[1];
        }
    }
    reg_cmd_mode = motor_chassis[0].cmd_mode;
    //�궨
    for (i = 0; i < 10; i++) {
        if ((motor_chassis[i].reset_q == 1 || motor_chassis[i].cal_div == 1) && motor_chassis[i].reset_q_lock == 0) {
            mit_set_pos_zero(i);
            Delay_us(mit_delay);
            motor_chassis[i].reset_q_lock = 1;
            motor_chassis[i].reset_q_cnt = 0;
            motor_chassis[i].reset_q = 0;
        }
        if (motor_chassis[i].reset_q_lock == 1) {
            mit_set_pos_zero(i);
            Delay_us(mit_delay);
            motor_chassis[i].reset_q_cnt++;
            if (motor_chassis[i].reset_q_cnt > 3) {
                motor_chassis[i].reset_q_cnt = 0;
                motor_chassis[i].reset_q_lock = 2;
            }
        }
        if (motor_chassis[i].reset_q_lock == 2) {
            motor_chassis[i].reset_q_delay_timer += dt;
            if (motor_chassis[i].reset_q_delay_timer > 3.5) {
                motor_chassis[i].reset_q_delay_timer = 0;
                motor_chassis[i].reset_q_lock = 0;
                motor_chassis[i].reset_q = 0;
                motor_chassis[i].reset_q_cnt = 0;
            }
        }
    }
    //��������
    /*if (can_write_flash == 1) {
        //stop motor
        for (i = 0; i < 10; i++) {
            motor_chassis[i].en_cmd = 0;
            motor_chassis[i].param.given_current = 0;
            motor_chassis[i].given_current_cmd = 0;
            motor_chassis[i].set_t = 0;
            motor_chassis[i].motor.ready = 0;
        }
        can_write_flash = 0;
        en_all = 0;
        //   WRITE_PARM();
    }TODO Надо потом разобраться с отключением двигателей*/

    //���Ϳ���ָ��
    for (i = 0; i < 10; i++) {
        if (en_mit_out == 2) //ʹ�ܷ������� MIT����ģʽ
        {
            data_can_mit_send(&motor_chassis[i]);
            Delay_us(mit_delay);
        } else //����Ͳɼ�����  ���Ť�ؾ�Ϊ0
        {
            data_can_sample_only(&motor_chassis[i]);
            Delay_us(mit_delay);
        }
    }

    switch (en_mit_out) //----------------ʹ���źŵ�״̬��
    {
        case 0: //�ر�״̬
            auto_off_t += dt;
            if (auto_off_t > 0.5) //�Զ��ر����ڷ���
            {
                auto_off_t = 0;
                for (i = 0; i < 10; i++) {
                    mit_motor_mode_en(i, 0);
                    Delay_us(mit_delay);
                }
            } else if (en_test || en_all) {
                for (i = 0; i < 10; i++) {
                    mit_motor_mode_en(i, 1);
                    Delay_us(mit_delay);
                }
                en_mit_out++;
                auto_off_t = 0;
            }
            break;
        case 1:
            auto_off_t += dt;
            if (auto_off_t > 0.5 && 1) //
            {
                auto_off_t = 0;
                en_mit_out++;
            }
            for (i = 0; i < 10; i++) {
                mit_motor_mode_en(i, 1);
                Delay_us(mit_delay);
            }
            break;
        case 2: //ʹ�ܺ�
            if (!en_test && !en_all) //����ʽ�ر�
            {
                for (i = 0; i < 10; i++) {
                    mit_motor_mode_en(i, 0);
                    Delay_us(mit_delay);
                }
                en_mit_out = 0;
            }
            break;
    }

    for (i = 0; i < 4; i++)
        state_reg[i] = state_mit[i];
}


int float_to_uint_rv(float x, float x_min, float x_max, int bits){
	/// Converts a float to an unsigned int, given range and number of bits ///
	float span = x_max - x_min;
	float offset = x_min;
	return (int) ((x-offset)*((float)((1<<bits)-1))/span);
}



// This function use in ask communication mode.
/*
motor_id:1~0x7FE
kp:0~500
kd:0~50
pos:-12.5rad~12.5rad
spd:-18rad/s~18rad/s
tor:-30Nm~30Nm
*/
HAL_StatusTypeDef send_motor_ctrl_cmd(uint16_t motor_id, float kp, float kd, float pos, float spd, float tor)
{
	u8 mbox;
  uint16_t i=0;
	int kp_int;
	int kd_int;
	int pos_int;
	int spd_int;
	int tor_int;

	CAN_TxHeaderTypeDef TxMessage;
	TxMessage.IDE = CAN_ID_STD;
	if(motor_id<7)
		TxMessage.StdId=0x00+motor_id+1;	 // ?????????0
	else
		TxMessage.StdId=0x00+motor_id+1-7;

	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;
	TxMessage.ExtId=0x00;//0x200;	 // ??????????????29???
  TxMessage.IDE=0;		  // '??????????
  TxMessage.RTR=0;		  // ???????????????h?8?
	if(kp>KP_MAX) kp=KP_MAX;
		else if(kp<KP_MIN) kp=KP_MIN;
	if(kd>KD_MAX ) kd=KD_MAX;
		else if(kd<KD_MIN) kd=KD_MIN;
	if(pos>POS_MAX)	pos=POS_MAX;
		else if(pos<POS_MIN) pos=POS_MIN;
	if(spd>SPD_MAX)	spd=SPD_MAX;
		else if(spd<SPD_MIN) spd=SPD_MIN;
	if(tor>T_MAX)	tor=T_MAX;
		else if(tor<T_MIN) tor=T_MIN;

  kp_int = float_to_uint_rv(kp, KP_MIN, KP_MAX, 12);
  kd_int = float_to_uint_rv(kd, KD_MIN, KD_MAX, 9);
	pos_int = float_to_uint_rv(pos, POS_MIN, POS_MAX, 16);
  spd_int = float_to_uint_rv(spd, SPD_MIN, SPD_MAX, 12);
  tor_int = float_to_uint_rv(tor, T_MIN, T_MAX, 12);
	uint8_t Data[8]={};
	Data[0]=0x00|(kp_int>>7);//kp5
	Data[1]=((kp_int&0x7F)<<1)|((kd_int&0x100)>>8);//kp7+kd1
	Data[2]=kd_int&0xFF;
	Data[3]=pos_int>>8;
	Data[4]=pos_int&0xFF;
	Data[5]=spd_int>>4;
	Data[6]=(spd_int&0x0F)<<4|(tor_int>>8);
	Data[7]=tor_int&0xff;

	if(motor_id<7) // 0-6
	{
		while (!HAL_CAN_GetTxMailboxesFreeLevel(&hcan1));
		return HAL_CAN_AddTxMessage(&hcan1, &TxMessage, Data, &mbox); //�ȴ����ͽ���
	}
	else // motor_id ?? 7   7-13
	{
		while (!HAL_CAN_GetTxMailboxesFreeLevel(&hcan2));
		return HAL_CAN_AddTxMessage(&hcan2, &TxMessage, Data, &mbox); //TODO Вечный цикл должно быть услвие выхода
	}

//	//for test,data unpack;
//	kp_int=kd_int=pos_int=spd_int=cur_int=0;
//
//	kp_int=(TxMessage.Data[0]&0x1F)<<7|(TxMessage.Data[1]&0xFE)>>1;
//	kd_int=(TxMessage.Data[1]&0x01)<<8|TxMessage.Data[2];
//	pos_int=TxMessage.Data[3]<<8|TxMessage.Data[4];
//	spd_int=TxMessage.Data[5]<<4|(TxMessage.Data[6]&0xF0)>>4;
//	cur_int=(TxMessage.Data[6]&0x0F)<<8|TxMessage.Data[7];
//
//	kp 	= uint_to_float(kp_int, KP_MIN, KP_MAX, 12);
//  kd	= uint_to_float(kd_int, KD_MIN, KD_MAX, 9);
//	pos = uint_to_float(pos_int, POS_MIN, POS_MAX, 16);
//  spd = uint_to_float(spd_int, SPD_MIN, SPD_MAX, 12);
//  cur = uint_to_float(cur_int, I_MIN, I_MAX, 12);
}



extern CAN_HandleTypeDef hcan1;
extern 		CAN_HandleTypeDef hcan2;
u8 mit_rv_pos_zero( char id)
{
	u8 mbox;
	uint8_t Data[8]={};
	CAN_TxHeaderTypeDef TxMessage;
	TxMessage.StdId=0x7ff;	 // ?????????0
	TxMessage.ExtId=0x00;//0x200;	 // ??????????????29???
	TxMessage.IDE=0;		  // '??????????
	TxMessage.RTR=0;		  // ???????????????h?8?
	TxMessage.DLC=4;							 // ??????????
	Data[0] = 0x00;//300??
	if(id<7)
		Data[1] = 0x00+id+1;	 // ?????????0
	else
		Data[1] = 0x00+id+1-7;
	//Data[1] = id;
	Data[2] = 0x00;
	Data[3] = 0x03;

	if(id<7) {

		HAL_CAN_AddTxMessage(&hcan1,&TxMessage,Data,&mbox);
	} else
		HAL_CAN_AddTxMessage(&hcan2,&TxMessage,Data,&mbox);
	return 0;		
}	



u8 rv_motor_mode_en( char id,char en)
{
	float kp=0;
	float kd=0;
	float pos=0;
	float spd=0;
	float tor=0;
	if(en)
		send_motor_ctrl_cmd(id, kp, kd, pos, spd, 0.1);
	else
		send_motor_ctrl_cmd(id, kp, kd, pos, spd, 0.0);
	return 0;
}

char data_can_sample_only_rv(motor_measure_t *ptr)//?????????
{
	u8 canbuft1[8];
	/// limit data to be within bounds ///
	int q_flag=1;
	if(ptr->param.q_flag)
		q_flag=1;
	else
		q_flag=-1;
	float set_q=q_flag*To_180_degrees(ptr->set_q-To_180_degrees(ptr->param.q_reset_angle));
	ptr->param.set_q=set_q;
	send_motor_ctrl_cmd(ptr->param.id, 0, 0, 0, 0, 0);
	return 0;
}


char data_can_rv_send(motor_measure_t *ptr)
{
	u8 canbuft1[8]={0};
/// limit data to be within bounds ///
	int q_flag=1;
	if(ptr->param.q_flag)
		q_flag = 1;
	else
		q_flag = -1;
	float set_q;//q_flag*To_180_degrees(ptr->set_q-To_180_degrees(ptr->param.q_reset_angle));
	#if EN_MIT_PID_INNER
	float temp=0;
	//ptr->set_q=test_set_q;
	if(ptr->cmd_mode==2)
		ptr->set_q=LIMIT(ptr->set_q_test+ptr->set_q_test_bias,-180,180);

	if(ptr->param.q_reset_angle==180)
	{
		if(ptr->set_q>=-180&&ptr->set_q<=-0)
		{
			if(ptr->param.q_flag)
				temp= 180-fabs(ptr->set_q);
			else
				temp= -(180-fabs(ptr->set_q));
		}
		else if(ptr->set_q<=180&&ptr->set_q>=0)
		{
			if(!ptr->param.q_flag)
				temp= 180-fabs(ptr->set_q);
			else
				temp= -(180-fabs(ptr->set_q));
		}
	}
	else
	{
		if(ptr->set_q>=-180&&ptr->set_q<=-0){
			if(!ptr->param.q_flag)
				temp= fabs(ptr->set_q);
			else
				temp= -(fabs(ptr->set_q));
		}else if(ptr->set_q<=180&&ptr->set_q>=0){
			if(ptr->param.q_flag)
				temp= fabs(ptr->set_q);
			else
				temp= -(fabs(ptr->set_q));
		}
	}

	set_q=temp;
	#endif
	ptr->param.set_q=set_q;//for record

	float set_dq=q_flag*ptr->set_qd;
	float set_t=q_flag*ptr->set_t;

	float p_des = set_q/57.3;
	float v_des =  set_dq/57.3;
	float kp = ptr->stiff*ptr->kp*EN_MIT_PID_INNER;
	float kd = ptr->stiff*ptr->kd*EN_MIT_PID_INNER;
	float t_ff = LIMIT(set_t,-ptr->max_t,ptr->max_t); //????????????j??

	if(EN_MIT_PID_INNER==0||ptr->param.usb_cmd_mode==2)//??????j????????g?
	   kp=kd=v_des=0;

	if(ptr->param.control_mode==1)//???g?
	{
		kp=0;
	}
  //send_motor_ctrl_cmd(uint16_t motor_id,float kp,float kd,float pos,float spd,float tor)
	send_motor_ctrl_cmd(ptr->param.id, kp, kd, p_des, v_des, t_ff*10);

  return 0;
}


extern float k_t_i[10];
char en_test_rv=0;
char en_rv_out=0;
int rv_delay=150;//doghome
float test_cmd_rv[2]={0.4,90};
int rv_connect_cnt=0;
float auto_off_t_rv=99;
float dt_rt=0;
void mit_bldc_thread_rv(char en_all,float dt)
{
	char i=0;
	static char state_reg[4]={0};
	static float timer_sin=0;
	static int reg_cmd_mode;

	for(i=0;i<14;i++)
	{
		motor_chassis[i].param.id=i;
	  //?????????�???
		switch(motor_chassis[i].motor.type)
		{
			case EC_1 ://?????6 ???
				k_t_i[i]=0.68;
			break;
			case EC_2 ://?????6 ???
				k_t_i[i]=0.68;
			break;
			case EC_3 ://?????6 ???
				k_t_i[i]=0.68;
			break;
		}
	}
	#if 1
	for(i=0;i<14;i++)
	{
		if(en_rv_out==2)//'????????? MIT????g?
		{
			data_can_rv_send(&motor_chassis[i]);
			Delay_us(rv_delay);// 300us = 0.3ms
		}
		else//???????????  ???T????0
		{
			data_can_sample_only_rv(&motor_chassis[i]);
			Delay_us(rv_delay);
		}
	}
	#endif
	//test
	timer_sin+=dt*test_cmd_rv[0];
	rv_connect_cnt=0;
	for(i=0;i<14;i++)
	{
		if(motor_chassis[i].param.connect)
			rv_connect_cnt++;
		if(reg_cmd_mode!=motor_chassis[0].cmd_mode||!en_all)
		{
			motor_chassis[i].set_q_test_bias=motor_chassis[i].q_now_flt;
			timer_sin=0;
		}
		if(motor_chassis[i].cmd_mode==2)
		{
			motor_chassis[i].set_q_test=sin(timer_sin)*test_cmd_rv[1];
		}
	}
	reg_cmd_mode=motor_chassis[0].cmd_mode;
	//??
	for(i=0;i<14;i++)
	{
		if((motor_chassis[i].reset_q==1||motor_chassis[i].cal_div==1)&&motor_chassis[i].reset_q_lock==0)
		{
			mit_rv_pos_zero(i);
			Delay_us(rv_delay);
			motor_chassis[i].reset_q_lock=1;
			motor_chassis[i].reset_q_cnt=0;
			motor_chassis[i].reset_q=0;
		}
		if(motor_chassis[i].reset_q_lock==1)
		{
				mit_rv_pos_zero(i);
				Delay_us(rv_delay);
        motor_chassis[i].reset_q_cnt++;
				if(motor_chassis[i].reset_q_cnt>3)
				{
					motor_chassis[i].reset_q_cnt=0;
					motor_chassis[i].reset_q_lock=2;
				}
		}
		if(motor_chassis[i].reset_q_lock==2)
		{
			 motor_chassis[i].reset_q_delay_timer+=dt;
			 if(motor_chassis[i].reset_q_delay_timer>3.5)
			 {
				 motor_chassis[i].reset_q_delay_timer=0;
				 motor_chassis[i].reset_q_lock=0;
				 motor_chassis[i].reset_q=0;
				 motor_chassis[i].reset_q_cnt=0;
			 }
		}
	}

	//????????
	/*if(can_write_flash==1)
	{
		//stop motor
		for(i=0;i<14;i++)
		{
			motor_chassis[i].en_cmd=0;
			motor_chassis[i].param.given_current=0;
			motor_chassis[i].given_current_cmd=0;
			motor_chassis[i].set_t=0;
			motor_chassis[i].motor.ready=0;
		}
		can_write_flash=0;
		en_all=0;
	}*/
	dt_rt=dt;
	switch(en_rv_out)//----------------'???zw?????
	{
		case 0://?????
			auto_off_t_rv+=dt;
			if(auto_off_t_rv>0.5&&1)//?????????????
			{
				auto_off_t_rv=0;
				for(i=0;i<14;i++)
				{
					rv_motor_mode_en(i,0);
					Delay_us(rv_delay);
				}
			}
			else if(en_test_rv||en_all)
			{
				for(i=0;i<14;i++)
				{
					rv_motor_mode_en(i,1);
					Delay_us(rv_delay);
				}
				en_rv_out++;
				auto_off_t_rv=0;
			}
		break;
		case 1://???????0.1s
			auto_off_t_rv+=dt;
			if(auto_off_t_rv>0.5&&1)//
			{
				auto_off_t_rv=0;
				en_rv_out++;
			}
			for(i=0;i<14;i++){
				rv_motor_mode_en(i,1);// ????can?????
				Delay_us(rv_delay);   // �?????0.3ms
			}
		break;
		case 2://'???
			if(!en_test_rv&&!en_all)//????????
			{
				for(i=0;i<14;i++){
					rv_motor_mode_en(i,0);
					Delay_us(rv_delay);
				}
				en_rv_out=0;
			}
		break;
		default:
			auto_off_t_rv=0;
		break;
	}
}