//************************** Humidity System **********************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
// 
// File    : main.c
// Summary : System entry point and thread lifecycle management.
// 
//*****************************************************************************

//******************************* Include Files *******************************
#include <stdio.h>
#include <stdint.h>
#include "humiditySystem.h"



//***************************** Global Constants ******************************

//***************************** Local Constants *******************************

//***************************** Global Variables ******************************
mqd_t g_humidity_mq; 

//***************************** Type Definitions ******************************


//******************************.FUNCTION_HEADER.******************************
// Purpose  : Main entry point. Initializes system resources like message 
//            queues and launches the execution threads.
// Inputs   : None.
// Outputs  : None.
// Return   : int - Returns 0 on successful system initialization and 
//            execution, or 1 if an error occurs.
//*****************************************************************************
int main(void)
{
    int iRetVal = 1; 
    bool blStatus = FALSE;

    if (TRUE == MessageQueueCreate()) 
    {
        blStatus = CreateThreads();
    }

    if (TRUE == blStatus) 
    {
        iRetVal = 0;
    }
    else
    {
        printf("System Initialization Failed.\n");
        iRetVal = 1;
    }

    return iRetVal;
}

//******************************.FUNCTION_HEADER.******************************
// Purpose  : Spawns the required humidity reading, logic checking, and 
//            alarm threads and manages their lifecycle.
// Inputs   : None.
// Outputs  : None.
// Return   : bool - TRUE if all threads are created successfully, 
//            otherwise FALSE.
//*****************************************************************************
bool CreateThreads(void)
{
    pthread_t threads[3];
    bool blRet = TRUE;

    if (0 != pthread_create(&threads[0], NULL, HumidityReadThread, NULL)) { blRet = FALSE; }
    if (0 != pthread_create(&threads[1], NULL, HumidityCheckThread, NULL)) { blRet = FALSE; }
    if (0 != pthread_create(&threads[2], NULL, AlarmThread, NULL)) { blRet = FALSE; }

    if (TRUE == blRet)
    {
        for (int iIdx = 0; iIdx < 3; iIdx++)
        {
            pthread_join(threads[iIdx], NULL);
        }
    }

    return blRet;
}

bool MessageQueueCreate(void) 
{
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;          
    attr.mq_msgsize = sizeof(uint8_t); 
    attr.mq_curmsgs = 0;

    mq_unlink(QUEUE_NAME); 
    g_humidity_mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);

    if (g_humidity_mq == (mqd_t)-1) 
    {
        return false; 
    }

    return true; 
}

//******************************** End of File ********************************