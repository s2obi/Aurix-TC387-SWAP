/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "00_APP/UserSW/inc/ultrasonic.h"
#include <time.h>

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* Initialize Ultrasonic Sensor */
void ultrasonic_init(void)
{
    IfxPort_setPinModeOutput(TRIGPIN, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinMode(ECHOPIN, IfxPort_Mode_inputPullDown);
}

/* Get data from Ultrasonic Sensor */
float ultrasonic_data(void)
{
    int start = 0, end = 0, time = 0;
    float distance = 0;

    IfxPort_setPinState(TRIGPIN, IfxPort_State_low);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 20));
    IfxPort_setPinState(TRIGPIN, IfxPort_State_high);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 100));
    IfxPort_setPinState(TRIGPIN, IfxPort_State_low);

    while (IfxPort_getPinState(ECHOPIN) == 0) {};
    start = (int)now();
    while(IfxPort_getPinState(ECHOPIN) == 1) {};
    end = (int)now();
    time = end - start;

    distance = ((float)340 * time / 2 / 10000);

    return distance;
}
