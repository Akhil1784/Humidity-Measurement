//************************** Humidity System **********************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
// 
// File    : humidityCheck.c
// Summary : Evaluates readings against thresholds and signals the alarm.
// 
//*****************************************************************************

//******************************* Include Files *******************************
#include <stdio.h>
#include "humiditySystem.h"

//***************************** Global Constants ******************************

//***************************** Local Constants *******************************

//***************************** Global Variables ******************************
sem_t g_lAlarmFlag; 
extern mqd_t g_humidity_mq;

//***************************** Type Definitions ******************************


//******************************.FUNCTION_HEADER.******************************
// Purpose  : Task to monitor humidity levels and count consecutive breaches.
// Inputs   : pArg - Pointer to task arguments.
// Outputs  : None. 
// Return   : void* - Always NULL. 
//*****************************************************************************
void* HumidityCheckThread(void* pArg)
{
    uint8 ucReceivedHum = 0U;
    uint8 ucBreachCount = 0U;

    (void)sem_init(&g_lAlarmFlag, 0, 0);

    while (TRUE)
    {
        if (-1 != mq_receive(g_humidity_mq, (char*)&ucReceivedHum, MAX_MSG_SIZE, NULL))
        {
            if (FALSE == HumidityCheckForThresholds(ucReceivedHum))
            {
                ucBreachCount++;
                
                if (MAX_BREACH_LIMIT <= ucBreachCount)
                {
                    (void)sem_post(&g_lAlarmFlag);
                    ucBreachCount = 0U;
                }
            }
            else
            {
                ucBreachCount = 0U; 
            }
        }
    }
    return NULL;
}

//******************************.FUNCTION_HEADER.******************************
// Purpose  : Performs logical comparison of value against range limits.
// Inputs   : ucHumidityValue - The value to check. 
// Outputs  : None. 
// Return   : bool - TRUE if within safety thresholds. 
//*****************************************************************************
bool HumidityCheckForThresholds(uint8 ucHumidityValue)
{
    bool blIsSafe = FALSE;

    if ((ucHumidityValue >= HUMIDITY_THRESHOLD_MIN) && 
        (ucHumidityValue <= HUMIDITY_THRESHOLD_MAX))
    {
        blIsSafe = TRUE;
    }

    return blIsSafe;
}

//******************************** End of File ********************************