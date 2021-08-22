/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "00_APP/UserSW/inc/g_port.h"

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* Initialize LEDs*/
void initLED(void)
{
    /* Initialization of the LED used in this example */
    IfxPort_setPinModeOutput(LED1, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(LED2, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(LED3, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(LED5, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
//    IfxPort_setPinMode(LED5, IfxPort_Mode_outputPushPullGeneral); // PWM
    IfxPort_setPinModeOutput(LED6, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(LED7, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1000));    /* Wait 500 milliseconds            */

    /* Switch OFF the LED (low-level active) */
    IfxPort_setPinHigh(LED1);
    IfxPort_setPinHigh(LED2);
    IfxPort_setPinHigh(LED3);
    IfxPort_setPinHigh(LED5);
    IfxPort_setPinHigh(LED6);
    IfxPort_setPinHigh(LED7);
}

/* Initialize S202 general purpose button */
void button_init(void)
{
    //    IfxPort_setPinModeInput(BUTTON, IfxPort_InputMode_pullUp);
    IfxPort_setPinMode(BUTTON, IfxPort_Mode_inputPullUp);
    IfxPort_setPinHigh(BUTTON);
}

/*
 * \brief return button states
 * \return @boolean
 *         True  - if button pushed
 *         False - if button not pushed
 */
boolean getButtonState(void)
{
    return IfxPort_getPinState(BUTTON) ? 0 : 1;
}
