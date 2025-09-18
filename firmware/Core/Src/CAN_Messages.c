//
// Created by Степан on 18.09.2025.
//

#include "../Inc/CAN_Messages.h"

//

//TODO Надо затестить
CAN_MESSAGE_Receive CAN_Message_Parse(uint8_t* buffer) {
    CAN_MESSAGE_Receive message;
    message.id = buffer[0]>>4;
    message.error = buffer[0] & 0x0F;
    message.position = ((uint16_t)buffer[1]<<8)|buffer[2];
    message.velocity = ((uint16_t)buffer[3]<<8)|(buffer[4]&0xF0);
    message.torque = ((uint16_t)(buffer[4]&0x0F)<<8)|buffer[5];
    message.temperature_motor = buffer[7];
    message.temperature_mosfet = buffer[6];
    return message;
}


//TODO Надо затестить
uint8_t * CAN_Message_Create(CAN_MESSAGE_Send *message) {
    static uint8_t buffer[9];
    buffer[0] = message->id;
    buffer[1] = message->position;
    buffer[2] = (message->position >> 8) & 0xFF;
    buffer[3] = (message->velocity>>4) & 0xFF;
    buffer[4] = (message->velocity&0xF) |  ((message->kp >> 8) & 0xF);
    buffer[5] = message->kp & 0xFF;
    buffer[6] = (message->kd>>4) & 0xFF;
    buffer[7] = (message->kd & 0x0F) | ((message->torque >> 8) & 0x0F);
    buffer[8] = message->torque & 0xFF;
    return buffer;
}


