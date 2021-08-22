/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "00_APP/UserSW/inc/motordriver.h"

/*********************************************************************************************************************/
/*--------------------------------------------------Data Structures--------------------------------------------------*/
/*********************************************************************************************************************/
typedef enum count_num {
    ALL_MOTER = 0,
    LEFT_MOTER,
    RIGHR_MOTER,
    STOP_MOTER
} COUNT;

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
volatile COUNT count;

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* Initialize Motor */
void MT_init()
{
//    IfxPort_setPinModeOutput(MOTOR_1_E, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
//    IfxPort_setPinModeOutput(MOTOR_2_E, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
//    IfxPort_setPinModeOutput(MOTOR_3_E, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
//    IfxPort_setPinModeOutput(MOTOR_4_E, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(MOTOR_1_F, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(MOTOR_2_F, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(MOTOR_3_F, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(MOTOR_4_F, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

//    IfxPort_setPinLow(MOTOR_1_E);
//    IfxPort_setPinLow(MOTOR_2_E);
//    IfxPort_setPinLow(MOTOR_3_E);
//    IfxPort_setPinLow(MOTOR_4_E);
    initGtmTomPwm(38);

    IfxPort_setPinLow(MOTOR_1_F);
    IfxPort_setPinLow(MOTOR_2_F);
    IfxPort_setPinLow(MOTOR_3_F);
    IfxPort_setPinLow(MOTOR_4_F);
}

void MT_forward()
{
//    IfxPort_setPinHigh(MOTOR_1_E);
//    IfxPort_setPinHigh(MOTOR_2_E);
//    IfxPort_setPinHigh(MOTOR_3_E);
//    IfxPort_setPinHigh(MOTOR_4_E);
    startGtmTomPwm();

    IfxPort_setPinLow(MOTOR_1_F);
    IfxPort_setPinLow(MOTOR_2_F);
    IfxPort_setPinLow(MOTOR_3_F);
    IfxPort_setPinLow(MOTOR_4_F);
}

void MT_hard_left()
{
    MT_stop();
//    IfxPort_setPinHigh(MOTOR_1_E);
//    IfxPort_setPinHigh(MOTOR_2_E);
//    IfxPort_setPinHigh(MOTOR_3_E);
//    IfxPort_setPinHigh(MOTOR_4_E);
    startGtmTomPwm();

    IfxPort_setPinLow(MOTOR_1_F);
    IfxPort_setPinLow(MOTOR_2_F);
    IfxPort_setPinHigh(MOTOR_3_F);
    IfxPort_setPinHigh(MOTOR_4_F);
}

//void MT_soft_left()
//{
//    MT_stop();
//    IfxPort_setPinHigh(MOTOR_1_E);
//    IfxPort_setPinHigh(MOTOR_2_E);
//    IfxPort_setPinLow(MOTOR_3_E);
//    IfxPort_setPinLow(MOTOR_4_E);
//
//    IfxPort_setPinLow(MOTOR_1_F);
//    IfxPort_setPinLow(MOTOR_2_F);
//    IfxPort_setPinHigh(MOTOR_3_F);
//    IfxPort_setPinHigh(MOTOR_4_F);
//}

void MT_hard_right()
{
    MT_stop();
//    IfxPort_setPinHigh(MOTOR_1_E);
//    IfxPort_setPinHigh(MOTOR_2_E);
//    IfxPort_setPinHigh(MOTOR_3_E);
//    IfxPort_setPinHigh(MOTOR_4_E);
    startGtmTomPwm();

    IfxPort_setPinHigh(MOTOR_1_F);
    IfxPort_setPinHigh(MOTOR_2_F);
    IfxPort_setPinLow(MOTOR_3_F);
    IfxPort_setPinLow(MOTOR_4_F);
}

//void MT_soft_right()
//{
//    MT_stop();
//    IfxPort_setPinLow(MOTOR_1_E);
//    IfxPort_setPinLow(MOTOR_2_E);
//    IfxPort_setPinHigh(MOTOR_3_E);
//    IfxPort_setPinHigh(MOTOR_4_E);
//
//    IfxPort_setPinHigh(MOTOR_1_F);
//    IfxPort_setPinHigh(MOTOR_2_F);
//    IfxPort_setPinLow(MOTOR_3_F);
//    IfxPort_setPinLow(MOTOR_4_F);
//}

void MT_backward()
{
    MT_stop();
//    IfxPort_setPinHigh(MOTOR_1_E);
//    IfxPort_setPinHigh(MOTOR_2_E);
//    IfxPort_setPinHigh(MOTOR_3_E);
//    IfxPort_setPinHigh(MOTOR_4_E);
    startGtmTomPwm();

    IfxPort_setPinHigh(MOTOR_1_F);
    IfxPort_setPinHigh(MOTOR_2_F);
    IfxPort_setPinHigh(MOTOR_3_F);
    IfxPort_setPinHigh(MOTOR_4_F);
}

void MT_stop()
{
//    IfxPort_setPinLow(MOTOR_1_E);
//    IfxPort_setPinLow(MOTOR_2_E);
//    IfxPort_setPinLow(MOTOR_3_E);
//    IfxPort_setPinLow(MOTOR_4_E);
    stopGtmTomPwm();

    IfxPort_setPinLow(MOTOR_1_F);
    IfxPort_setPinLow(MOTOR_2_F);
    IfxPort_setPinLow(MOTOR_3_F);
    IfxPort_setPinLow(MOTOR_4_F);
}
