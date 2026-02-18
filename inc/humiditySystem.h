//************************** Humidity System **********************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
// 
// Summary : Constants, types, and prototypes for the humidity monitor.
// Note    : Adheres to Trenser Coding Standard V1.0.
// 
//*****************************************************************************

#ifndef HUMIDITY_SYSTEM_H
#define HUMIDITY_SYSTEM_H

//******************************* Include Files *******************************
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <mqueue.h>
#include "platformTypes.h" 

//***************************** Global Constants ******************************

//***************************** Local Constants *******************************
#define HUMIDITY_READ_FREQ_US  (1000000UL) 
#define ALARM_DURATION_SEC (2U)
#define HUMIDITY_THRESHOLD_MIN  (20U)
#define HUMIDITY_THRESHOLD_MAX  (60U)
#define MAX_BREACH_LIMIT   (3U)
#define RETRY_COUNT        (3U)
#define QUEUE_NAME         "/humidity_queue"
#define MAX_MSG_SIZE       sizeof(uint8)

//***************************** Global Variables ******************************

//***************************** Type Definitions ******************************
bool  CreateThreads(void);
bool  MessageQueueCreate(void);
void* HumidityReadThread(void* pArg);
bool  ReadHumidity(uint8 *pucHumidityValue); 
bool  SensorRead(uint8 *pucHumidityValue);
void* HumidityCheckThread(void* pArg);
bool  HumidityCheckForThresholds(uint8 ucHumidityValue);
void* AlarmThread(void* pArg);

//**************************** Forward Declarations ***************************

#endif /* HUMIDITY_SYSTEM_H */

//******************************** End of File ********************************