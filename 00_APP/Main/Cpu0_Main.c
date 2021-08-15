#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxDmu_reg.h"

#include "00_APP/UserSW/inc/direction.h"
#include "00_APP/UserSW/inc/Flash.h"
#include "00_APP/UserSW/inc/IRsensor.h"
#include "00_APP/UserSW/inc/MCMCAN.h"
#include "00_APP/UserSW/inc/motordriver.h"
#include "00_APP/UserSW/inc/typedef.h"
#include "00_APP/UserSW/inc/ultrasonic.h"

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;

void core0_main(void)
{
    IfxCpu_enableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    /* YSKIM 테스트 코드 */
    // IfxPort_setPinMode(&MODULE_P33,4, IfxPort_Mode_outputPushPullGeneral);
    // IfxPort_setPinMode(&MODULE_P33,6, IfxPort_Mode_outputPushPullGeneral);
    // IfxPort_setPinMode(&MODULE_P20,11, IfxPort_Mode_outputPushPullGeneral);
    // IfxPort_setPinMode(&MODULE_P20,13, IfxPort_Mode_outputPushPullGeneral);

    // IfxPort_setPinState(&MODULE_P33,4, IfxPort_State_low);
    // IfxPort_setPinState(&MODULE_P33,6, IfxPort_State_low);
    // IfxPort_setPinState(&MODULE_P20,11, IfxPort_State_low);
    // IfxPort_setPinState(&MODULE_P20,13, IfxPort_State_low);

    // Line Tracer 테스트 코드
//    IR_init();
//    MT_init();
//    ultrasonic_init();
    //initLED();

    /* Reprogramming & SWAP Test */
//    swap_disable();
//    pfls_reprogram();
//    swap_enable();
//    swap_update();

    /* MCMCAN 테스트 코드 */
    //initCAN();

    initLED();
    while(1)
    {
        //line_tracer();

        //flash();
    }
}


//void flash()
//{
//    if(neederased)
//    {
//
//    }
//    else if (needCheck_Erased)
//    {
//
//    }
//    else if( flash_processing)
//    {
//
//    }
//}
