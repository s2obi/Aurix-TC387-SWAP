#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxDmu_reg.h"

#include "00_APP/UserSW/inc/direction.h"
#include "00_APP/UserSW/inc/Flash.h"
#include "00_APP/UserSW/inc/g_port.h"
#include "00_APP/UserSW/inc/IRsensor.h"
#include "00_APP/UserSW/inc/MCMCAN.h"
#include "00_APP/UserSW/inc/motordriver.h"
#include "00_APP/UserSW/inc/typedef.h"
#include "00_APP/UserSW/inc/ultrasonic.h"
#include "00_APP/UserSW/inc/GPT12_Timer_Interrupt.h"

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;

void core0_main(void)
{
    IfxCpu_enableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    initLED();              /* LED Initialization */
    initCAN();              /* Initialization CAN Module */
    IR_init();              /* IR Sensor Initialization */
    MT_init();              /* Motor Driver Initialization */
    ultrasonic_init();      /* Ultrasonic Sensor Initialization */
    button_init();          /* OTA Update Request pin Initialization */
    initGpt12Timer();       /* Initialize and start GPT12 timer */

    /* Reprogramming & SWAP Test */
//    swap_disable();
//    pfls_reprogram();
//    swap_enable();
//    swap_update();

    volatile boolean isBtnPushed = 0;
    while(1)
    {
        waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1000));
        isBtnPushed = getButtonState();

        if (isBtnPushed) {
            IfxPort_setPinLow(LED5);
            pfls_MassErase();
            /**
             * Erase UCBs
             *
             * UCB00(UCB_BMHD0_ORIG)
             * UCB01(UCB_BMHD1_ORIG)
             * UCB02(UCB_BMHD2_ORIG)
             * UCB03(UCB_BMHD3_ORIG)
             * UCB08(UCB_BMHD0_COPY)
             * UCB09(UCB_BMHD1_COPY)
             * UCB10(UCB_BMHD2_COPY)
             * UCB11(UCB_BMHD3_COPY)
             */
//            for (uint32 ucbSectorAddr = UCB_BMHD0_ORIG; ucbSectorAddr < UCB_BMHD3_ORIG; ucbSectorAddr += UCB_LOGICAL_SECTOR_SIZE) {
//                ucb_erase(ucbSectorAddr);
//            }
//            for (uint32 ucbSectorAddr = UCB_BMHD0_COPY; ucbSectorAddr < UCB_BMHD3_COPY; ucbSectorAddr += UCB_LOGICAL_SECTOR_SIZE) {
//                ucb_erase(ucbSectorAddr);
//            }
            waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 100));
            can00_send(0x100, "REQ_OTA", 7); /* Request Reprogramming */

            /* 락방지용 코드 */
//            for (uint32 ucbSectorAddr = UCB_BMHD0_ORIG; ucbSectorAddr < UCB_BMHD3_ORIG; ucbSectorAddr += UCB_LOGICAL_SECTOR_SIZE) {
//                ucb_erase(ucbSectorAddr);
//            }
//            for (uint32 ucbSectorAddr = UCB_BMHD0_COPY; ucbSectorAddr < UCB_BMHD3_COPY; ucbSectorAddr += UCB_LOGICAL_SECTOR_SIZE) {
//                ucb_erase(ucbSectorAddr);
//            }
//            ucb_write(0xAF4001F0, 0x43211234, 0x00000000);
//            ucb_write(0xAF4003F0, 0x43211234, 0x00000000);
//            ucb_write(0xAF4005F0, 0x43211234, 0x00000000);
//            ucb_write(0xAF4007F0, 0x43211234, 0x00000000);
//            ucb_write(0xAF4011F0, 0x43211234, 0x00000000);
//            ucb_write(0xAF4013F0, 0x43211234, 0x00000000);
//            ucb_write(0xAF4015F0, 0x43211234, 0x00000000);
//            ucb_write(0xAF4017F0, 0x43211234, 0x00000000);
            IfxPort_setPinHigh(LED5);
        }
    }
}
