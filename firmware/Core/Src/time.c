//
// Created by Степан on 24.09.2025.
//

#include "../Inc/time.h"
volatile float Cycle_T[(100)][4];

enum
{
    NOW = 0,
    OLD,
    NEW,
    DT_LAST
};

#define TICK_PER_SECOND 1000 //2000
#define TICK_US	(1000000/TICK_PER_SECOND)

volatile uint32_t sysTickUptime = 0;
uint32_t GetSysTime_us(void)
{
    register uint32_t ms;
    uint32_t value;
    ms = sysTickUptime;
    value = ms * TICK_US + (SysTick->LOAD - SysTick->VAL) * TICK_US / SysTick->LOAD;
    return value;
}

float Get_Cycle_T(uint8_t item)
{
    Cycle_T[item][OLD] = Cycle_T[item][NOW];	//????��????
    Cycle_T[item][NOW] = (float)GetSysTime_us()/1000000.0f; //GetSysTime_us()/1000000.0f; //???��????
    if(Cycle_T[item][NOW]>Cycle_T[item][OLD]){
        Cycle_T[item][NEW] = ( ( Cycle_T[item][NOW] - Cycle_T[item][OLD] ) );//?????????????
        Cycle_T[item][DT_LAST] = Cycle_T[item][NEW];
    }
    else
        Cycle_T[item][NEW] = Cycle_T[item][DT_LAST];

    if(Cycle_T[item][NEW]>0.5)
        return 0.5;
    else
        return Cycle_T[item][NEW];
}

void Delay_us(uint32_t us)
{
    uint32_t now = GetSysTime_us();
    while (GetSysTime_us() - now < us);
}