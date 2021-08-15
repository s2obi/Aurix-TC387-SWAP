#include "00_APP/UserSW/inc/motordriver.h"
#include "00_APP/UserSW/inc/g_port.h"
#include "00_APP/UserSW/inc/typedef.h"
#include "IfxPort.h"

//implement
void MT_init()
{
    IfxPort_setPinModeOutput(MOTOR_1_E, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(MOTOR_2_E, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(MOTOR_3_E, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(MOTOR_4_E, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(MOTOR_1_F, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(MOTOR_2_F, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(MOTOR_3_F, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(MOTOR_4_F, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

    IfxPort_setPinLow(MOTOR_1_E);
    IfxPort_setPinLow(MOTOR_2_E);
    IfxPort_setPinLow(MOTOR_3_E);
    IfxPort_setPinLow(MOTOR_4_E);

    IfxPort_setPinLow(MOTOR_1_F);
    IfxPort_setPinLow(MOTOR_2_F);
    IfxPort_setPinLow(MOTOR_3_F);
    IfxPort_setPinLow(MOTOR_4_F);
}

void MT_forward()
{
    MT_stop();
    IfxPort_setPinHigh(MOTOR_1_E);
    IfxPort_setPinHigh(MOTOR_2_E);
    IfxPort_setPinHigh(MOTOR_3_E);
    IfxPort_setPinHigh(MOTOR_4_E);

    IfxPort_setPinLow(MOTOR_1_F);
    IfxPort_setPinLow(MOTOR_2_F);
    IfxPort_setPinLow(MOTOR_3_F);
    IfxPort_setPinLow(MOTOR_4_F);
}

void MT_hard_left()
{
    MT_stop();
    IfxPort_setPinHigh(MOTOR_1_E);
    IfxPort_setPinHigh(MOTOR_2_E);
    IfxPort_setPinHigh(MOTOR_3_E);
    IfxPort_setPinHigh(MOTOR_4_E);

    IfxPort_setPinLow(MOTOR_1_F);
    IfxPort_setPinLow(MOTOR_2_F);
    IfxPort_setPinHigh(MOTOR_3_F);
    IfxPort_setPinHigh(MOTOR_4_F);
}

void MT_soft_left()
{
    MT_stop();
    IfxPort_setPinHigh(MOTOR_1_E);
    IfxPort_setPinHigh(MOTOR_2_E);
    IfxPort_setPinLow(MOTOR_3_E);
    IfxPort_setPinLow(MOTOR_4_E);

    IfxPort_setPinLow(MOTOR_1_F);
    IfxPort_setPinLow(MOTOR_2_F);
    IfxPort_setPinHigh(MOTOR_3_F);
    IfxPort_setPinHigh(MOTOR_4_F);
}

void MT_hard_right()
{
    MT_stop();
    IfxPort_setPinHigh(MOTOR_1_E);
    IfxPort_setPinHigh(MOTOR_2_E);
    IfxPort_setPinHigh(MOTOR_3_E);
    IfxPort_setPinHigh(MOTOR_4_E);

    IfxPort_setPinHigh(MOTOR_1_F);
    IfxPort_setPinHigh(MOTOR_2_F);
    IfxPort_setPinLow(MOTOR_3_F);
    IfxPort_setPinLow(MOTOR_4_F);
}

void MT_soft_right()
{
    MT_stop();
    IfxPort_setPinLow(MOTOR_1_E);
    IfxPort_setPinLow(MOTOR_2_E);
    IfxPort_setPinHigh(MOTOR_3_E);
    IfxPort_setPinHigh(MOTOR_4_E);

    IfxPort_setPinHigh(MOTOR_1_F);
    IfxPort_setPinHigh(MOTOR_2_F);
    IfxPort_setPinLow(MOTOR_3_F);
    IfxPort_setPinLow(MOTOR_4_F);
}

void MT_backward()
{
    MT_stop();
    IfxPort_setPinHigh(MOTOR_1_E);
    IfxPort_setPinHigh(MOTOR_2_E);
    IfxPort_setPinHigh(MOTOR_3_E);
    IfxPort_setPinHigh(MOTOR_4_E);

    IfxPort_setPinHigh(MOTOR_1_F);
    IfxPort_setPinHigh(MOTOR_2_F);
    IfxPort_setPinHigh(MOTOR_3_F);
    IfxPort_setPinHigh(MOTOR_4_F);
}

void MT_stop()
{
    IfxPort_setPinLow(MOTOR_1_E);
    IfxPort_setPinLow(MOTOR_2_E);
    IfxPort_setPinLow(MOTOR_3_E);
    IfxPort_setPinLow(MOTOR_4_E);

    IfxPort_setPinLow(MOTOR_1_F);
    IfxPort_setPinLow(MOTOR_2_F);
    IfxPort_setPinLow(MOTOR_3_F);
    IfxPort_setPinLow(MOTOR_4_F);
}
