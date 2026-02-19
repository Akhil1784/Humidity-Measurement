//************************** Health Monitor ***********************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
// 
// File    : main.c
// Summary : Health monitor simulation . 
// 
//*****************************************************************************

//******************************* Include Files *******************************
#include <stdio.h>
#include "platformTypes.h"
//******************************* Include Files *******************************

//***************************** Global Constants ******************************

//***************************** Local Constants *******************************
#define BUFFER_SIZE          (5U) 
#define SENSOR_VAL_INITIAL   (100U)
#define SENSOR_VAL_SECONDARY (200U)
#define SENSOR_VAL_REPEATED  (50U)
#define AVG_SAMPLE_COUNT     (2U)
#define LOOP_LIMIT_EXTENDED  (5U)

//***************************** Local Variables *******************************
static int16 s_anSensorReading[BUFFER_SIZE] = {0}; 
static uint8 s_ucHistoryIndex = 0U;

//***************************** Global Variables ******************************

//***************************** Type Definitions ******************************

//******************************.FUNCTION_HEADER.******************************
// Purpose  : Adds a new sensor reading to the internal history buffer while 
//            preventing buffer overflow. 
// Inputs   : ulValue - The 32-bit unsigned sensor reading to be stored.
// Outputs  : Updates the s_anSensorReading array with the new value and 
//            increments the s_ucHistoryIndex.
// Return   : bool - TRUE if the reading was successfully added to the buffer; 
//            FALSE if the buffer is full. 
//*****************************************************************************
bool AddReading(uint32 ulValue)
{
    bool blStatus = FALSE;

    if (s_ucHistoryIndex < BUFFER_SIZE)
    {
        s_anSensorReading[s_ucHistoryIndex] = (int16)ulValue;
        s_ucHistoryIndex++;
        blStatus = TRUE;
    }
    else
    {
        printf("Error: Buffer overflow attempt detected.\n");
    }

    return blStatus;
}

//******************************.FUNCTION_HEADER.******************************
// Purpose  : Calculates the mathematical average of a specified number of 
//            previous sensor readings from the history buffer.
// Inputs   : ucCount - The number of historical samples to include. 
// Outputs  : None. 
// Return   : float - The calculated average of the requested samples. Returns 
//            0.0f if the count is invalid.
//*****************************************************************************
float GetAverage(uint8 ucCount)
{
    float fSum   = 0.0f;
    uint8 ucIIdx = 0U;

    if ((0U < ucCount) && (ucCount <= s_ucHistoryIndex))
    {
        for (ucIIdx = 0U; ucIIdx < ucCount; ucIIdx++)
        {
            fSum += (float)s_anSensorReading[ucIIdx];
        }
        fSum = fSum / (float)ucCount;
    }

    return fSum;
}

//******************************.FUNCTION_HEADER.******************************
// Purpose  : Main entry point. Executes the health monitor simulation logic.
// Inputs   : None. 
// Outputs  : None. 
// Return   : int - 0 on success. 
//*****************************************************************************
int main(void)
{
    int32 lInitialVal = 0; 
    const int32 *plSafePtr = &lInitialVal; 

    printf("--- Health Monitor Simulation ---\n\n");  
    (void)AddReading(SENSOR_VAL_INITIAL);
    (void)AddReading(SENSOR_VAL_SECONDARY);   
    float fAvg = GetAverage(AVG_SAMPLE_COUNT);
    printf("Calculated Avg: %.2f\n", (double)fAvg);

    for (uint8 ucJIdx = 0U; ucJIdx < LOOP_LIMIT_EXTENDED; ucJIdx++)
    {
        (void)AddReading(SENSOR_VAL_REPEATED); 
    }

    printf("\nPointer Access (Safe): %ld\n", *plSafePtr);

    return 0;
}

//******************************** End of File ********************************

