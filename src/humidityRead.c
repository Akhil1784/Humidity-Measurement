//************************** Humidity System **********************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
// 
// File    : humidityRead.c
// Summary : Handles the acquisition of humidity data from the sensor.
// 
//*****************************************************************************

//******************************* Include Files *******************************
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include "humiditySystem.h"

//***************************** Global Constants ******************************

//***************************** Local Constants *******************************

//***************************** Global Variables ******************************
extern mqd_t g_humidity_mq;

//***************************** Type Definitions ******************************


//******************************.FUNCTION_HEADER.******************************
// Purpose  : Entry point for the humidity reading task. Periodically reads
//            sensor data and sends it to the message queue.
// Inputs   : pArg - Pointer to task arguments (unused). 
// Outputs  : None. 
// Return   : void* - Always NULL.
//*****************************************************************************
void* HumidityReadThread(void* pArg)
{
    uint8 ucHumidityValue = 0U; 

    while (TRUE)
    {
        if (TRUE == ReadHumidity(&ucHumidityValue)) 
        {
            (void)mq_send(g_humidity_mq, (const char*)&ucHumidityValue, MAX_MSG_SIZE, 0);
        }
        usleep(HUMIDITY_READ_FREQ_US); 
    }
    return NULL;
}

//******************************.FUNCTION_HEADER.******************************
// Purpose  : Validates the output pointer and attempts to read sensor data
//            with a retry mechanism.
// Inputs   : pucHumidityValue - Pointer to store the reading.
// Outputs  : Updates the value pointed to by pucHumidityValue.
// Return   : bool - TRUE if a valid reading was obtained.
//*****************************************************************************
bool ReadHumidity(uint8 *pucHumidityValue)
{
    uint8 ucRetry = 0U;
    bool  blRet   = FALSE;


    if (NULL != pucHumidityValue)
    {
        while ((RETRY_COUNT > ucRetry) && (FALSE == blRet))
        {
            blRet = SensorRead(pucHumidityValue);
            ucRetry++;
        }
    }

    return blRet;
}

//******************************.FUNCTION_HEADER.******************************
// Purpose  : Interfaces directly with hardware to get raw humidity data.
// Inputs   : pucHumidityValue - Pointer to output storage. 
// Outputs  : Updated humidity value. 
// Return   : bool - Always TRUE in this simulation. 
//*****************************************************************************
bool SensorRead(uint8 *pucHumidityValue) { 
    if (pucHumidityValue == NULL) return FALSE;
    *pucHumidityValue = 85U;
    return TRUE;
}

//******************************** End of File ********************************