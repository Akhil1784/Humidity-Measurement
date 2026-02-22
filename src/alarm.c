//************************** Humidity System **********************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
// 
// File    : alarm.c
// Summary : Manages the alarm notification task.
// 
//*****************************************************************************

//******************************* Include Files *******************************
#include <stdio.h>
#include <unistd.h>
#include "humiditySystem.h"

//***************************** Global Constants ******************************

//***************************** Local Constants *******************************

//***************************** Global Variables ******************************
extern sem_t g_lAlarmFlag;

//***************************** Type Definitions ******************************

//******************************.FUNCTION_HEADER.******************************
// Purpose  : Blocks on a semaphore and prints alarm status when triggered.
// Inputs   : pArg - Pointer to task arguments.
// Outputs  : None. 
// Return   : void* - Always NULL.
//*****************************************************************************
void* AlarmThread(void* pArg)
{
    while (TRUE)
    {
        if (0 == sem_wait(&g_lAlarmFlag))
        {
            printf("\n>>> HUMIDITY ALARM TRIGGERED! <<<\n");
            sleep(ALARM_DURATION_SEC); 
        }
    }
    return NULL;
}

//******************************** End of File ********************************