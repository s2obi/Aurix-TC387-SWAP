/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "00_APP/UserSW/inc/pwm.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define ISR_PRIORITY_TOM    20                                      /* Interrupt priority number                    */
#define MOTOR               IfxGtm_TOM2_11_TOUT71_P15_0_OUT         /* MOTOR */
#define PWM_PERIOD          50000                                   /* PWM period for the TOM                       */

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
IfxGtm_Tom_Pwm_Config moter_tomConfig;                                  /* Timer configuration structure                */
IfxGtm_Tom_Pwm_Driver moter_tomDriver;                                  /* Timer Driver structure                       */

/*********************************************************************************************************************/
/*-----------------------------------------------Function Prototypes-------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*--------------------------------------------Function Implementations-----------------------------------------------*/
/*********************************************************************************************************************/
/* This function initializes the TOM */
void initGtmTomPwm(uint32 dutyCycle)
{
    IfxGtm_enable(&MODULE_GTM);                                     /* Enable GTM                                   */

    IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_FXCLK);   /* Enable the FXU clock                         */

    /* Initialize the configuration structure with default parameters */
    IfxGtm_Tom_Pwm_initConfig(&moter_tomConfig, &MODULE_GTM);

    moter_tomConfig.tom = MOTOR.tom;                                      /* Select the TOM depending on the LED          */
    moter_tomConfig.tomChannel = MOTOR.channel;                           /* Select the channel depending on the LED      */
    moter_tomConfig.period = PWM_PERIOD;                                /* Set the timer period                         */
    moter_tomConfig.pin.outputPin = &MOTOR;                               /* Set the LED port pin as output               */
    moter_tomConfig.dutyCycle = 500 * dutyCycle;
    moter_tomConfig.synchronousUpdateEnabled = TRUE;                    /* Enable synchronous update                    */

    IfxGtm_Tom_Pwm_init(&moter_tomDriver, &moter_tomConfig);                /* Initialize the GTM TOM                       */
}

void startGtmTomPwm() {
    IfxGtm_Tom_Pwm_start(&moter_tomDriver, TRUE);                       /* Start the PWM                                */
}

void stopGtmTomPwm(void) {
    IfxGtm_Tom_Pwm_stop(&moter_tomDriver, TRUE);
}
