//
// Created by Степан on 18.09.2025.
//

#ifndef FIRMWARE_CAN_MESSAGES_H
#define FIRMWARE_CAN_MESSAGES_H
#include "main.h"
#endif //FIRMWARE_CAN_MESSAGES_H




//0:[4bitFor ID << 4bit for error] 1:[positon 15:8] 2:[position 7:0] 3:[velocity 11:4]
//4:[Velocity 3:0 Torque 11:8] 5:[7:0 Torque] 6:[Temperature_MOS] 7:[Temperature]
typedef struct {
    uint8_t id;
    uint8_t error;
    int16_t position;
    int16_t velocity;
    uint16_t torque;
    int8_t temperature_motor;
    int8_t temperature_mosfet;
} CAN_MESSAGE_Receive;


//ID 0:[position_dest] 1:[positon_dest] 2:[v_des 11:4] 3:[v_des 3:0 | Kp 11:8]
// 4:[kp] 5:[Kd 11:4] 6:[Kd 3:0 | t_ff[11:8]] 7:[t_ff]
//t_ff- Задаваемый момент
typedef struct {
    uint8_t id;
    int16_t position;
    int16_t velocity;
    uint16_t kp;
    uint16_t kd;
    uint16_t torque;
}   CAN_MESSAGE_Send;

//Парсит значения полученые с CAN шины в структуру
CAN_MESSAGE_Receive CAN_Message_Parse(uint8_t* buffer);

// Возвращает буфер для CAN шины из структуры
// Возвращает массив из 9 байт, где первый байт это ID
uint8_t* CAN_Message_Create(CAN_MESSAGE_Send* message);
