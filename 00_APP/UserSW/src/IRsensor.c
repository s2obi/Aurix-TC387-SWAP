#include "00_APP/UserSW/inc/IRsensor.h"
#include "00_APP/UserSW/inc/g_port.h"
#include "IfxPort.h"

void IR_init()
{
    IfxPort_setPinMode(IR_1, IfxPort_Mode_inputPullDown);
    IfxPort_setPinMode(IR_2, IfxPort_Mode_inputPullDown);
    IfxPort_setPinMode(IR_3, IfxPort_Mode_inputPullDown);
    IfxPort_setPinMode(IR_4, IfxPort_Mode_inputPullDown);
}

UINT_8 IR_data()
{
    UINT_8 status = 0;

    if (IfxPort_getPinState(IR_1)) {
        status |= 0x01;
    } else {
        status &= 0xFE;
    }

    if (IfxPort_getPinState(IR_2)) {
        status |= 0x02;
    } else {
         status &= 0xFD;
    }

    if (IfxPort_getPinState(IR_3)) {
        status |= 0x04;
    } else {
         status &= 0xFB;
    }

    if (IfxPort_getPinState(IR_4)) {
        status |= 0x08;
    } else {
        status &= 0xF7;
    }

    return status;
}
