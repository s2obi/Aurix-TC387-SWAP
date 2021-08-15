/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "00_APP/UserSW/inc/MCMCAN.h"

#include <IfxCan.h>
#include <IfxCan_Can.h>
#include "IfxPort.h"
#include "Bsp.h"
/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
McmcanType                  g_mcmcan;                       /* Global MCMCAN configuration and control structure    */
IfxPort_Pin_Config          g_led1;                         /* Global LED1 configuration and control structure      */
IfxPort_Pin_Config          g_led2;                         /* Global LED2 configuration and control structure      */

IFX_CONST IfxCan_Can_Pins Can00_pins = {
        &IfxCan_TXD00_P20_8_OUT, IfxPort_OutputMode_pushPull,
        &IfxCan_RXD00B_P20_7_IN, IfxPort_InputMode_pullUp,
        IfxPort_PadDriver_cmosAutomotiveSpeed4
};

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* Macro to define Interrupt Service Routine.
 * This macro:
 * - defines linker section as .intvec_tc<vector number>_<interrupt priority>.
 * - defines compiler specific attribute for the interrupt functions.
 * - defines the Interrupt service routine as ISR function.
 *
 * IFX_INTERRUPT(isr, vectabNum, priority)
 *  - isr: Name of the ISR function.
 *  - vectabNum: Vector table number.
 *  - priority: Interrupt priority. Refer Usage of Interrupt Macro for more details.
 */
IFX_INTERRUPT(canIsrTxHandler, 0, ISR_PRIORITY_CAN_TX);
IFX_INTERRUPT(canIsrRxHandler, 0, ISR_PRIORITY_CAN_RX);

/* Interrupt Service Routine (ISR) called once the TX interrupt has been generated.
 * Turns on the LED1 to indicate successful CAN message transmission.
 */
void canIsrTxHandler(void)
{
    IfxCan_Node_clearInterruptFlag(g_mcmcan.can00Node.node, IfxCan_Interrupt_transmissionCompleted);

    IfxPort_setPinLow(LED1);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 100));
    IfxPort_setPinHigh(LED1);
}

/* Interrupt Service Routine (ISR) called once the RX interrupt has been generated.
 * Compares the content of the received CAN message with the content of the transmitted CAN message
 * and in case of success, turns on the LED2 to indicate successful CAN message reception.
 */
void canIsrRxHandler(void)
{
    /* Clear the "Message stored to Dedicated RX Buffer" interrupt flag */
    IfxCan_Node_clearInterruptFlag(g_mcmcan.can00Node.node, IfxCan_Interrupt_messageStoredToDedicatedRxBuffer);

    /* Clear the "New Data" flag; as long as the "New Data" flag is set, the respective Rx buffer is
     * locked against updates from received matching frames.
     */
    IfxCan_Node_clearRxBufferNewDataFlag(g_mcmcan.can00Node.node, g_mcmcan.canFilter.rxBufferOffset);

    /* Read the received CAN message */
    IfxCan_Can_readMessage(&g_mcmcan.can00Node, &g_mcmcan.rxMsg, g_mcmcan.rxData);

    /* Check if the received data matches with the transmitted one */
//    IfxPort_setPinLow(LED2);
//    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 100));
//    IfxPort_setPinHigh(LED2);
    IfxPort_togglePin(LED2);
//    if ((g_mcmcan.rxData[0] == 0x48656c6c) && (g_mcmcan.rxData[1] == 0x6f212121) && (g_mcmcan.rxMsg.messageId == g_mcmcan.txMsg.messageId)) {
//        IfxPort_setPinLow(g_led2.port, g_led2.pinIndex);
//    }
//    if( ( g_mcmcan.rxData[0] == g_mcmcan.txData[0] ) &&
//        ( g_mcmcan.rxData[1] == g_mcmcan.txData[1] ) &&
//        ( g_mcmcan.rxMsg.messageId == g_mcmcan.txMsg.messageId ) )
//    {
//        /* Turn on the LED2 to indicate correctness of the received message */
//        IfxPort_setPinLow(g_led2.port, g_led2.pinIndex);
//    }
}

void initCAN(void)
{
    /* CAN module configuration and initialization */
    IfxCan_Can_initModuleConfig(&g_mcmcan.canConfig, &MODULE_CAN0);
    IfxCan_Can_initModule(&g_mcmcan.canModule, &g_mcmcan.canConfig);
    IfxCan_Can_initNodeConfig(&g_mcmcan.canNodeConfig, &g_mcmcan.canModule);

    // node
    g_mcmcan.canNodeConfig.nodeId = IfxCan_NodeId_0;    // CAN00
    g_mcmcan.canNodeConfig.clockSource = IfxCan_ClockSource_both;
    g_mcmcan.canNodeConfig.frame.type = IfxCan_FrameType_transmitAndReceive;
    g_mcmcan.canNodeConfig.frame.mode = IfxCan_FrameMode_standard; // Classic CAN
    g_mcmcan.canNodeConfig.txConfig.txMode = IfxCan_TxMode_dedicatedBuffers;
    g_mcmcan.canNodeConfig.txConfig.dedicatedTxBuffersNumber = 16;
    g_mcmcan.canNodeConfig.txConfig.txBufferDataFieldSize = IfxCan_DataFieldSize_8;
    g_mcmcan.canNodeConfig.rxConfig.rxMode = IfxCan_RxMode_dedicatedBuffers;
    g_mcmcan.canNodeConfig.rxConfig.rxBufferDataFieldSize = IfxCan_DataFieldSize_8;
    g_mcmcan.canNodeConfig.filterConfig.extendedListSize = 16; // Extended Frame
    g_mcmcan.canNodeConfig.filterConfig.standardListSize = 16; // Standard Frame
    g_mcmcan.canNodeConfig.filterConfig.messageIdLength = IfxCan_MessageIdLength_both;
    g_mcmcan.canNodeConfig.messageRAM.extendedFilterListStartAddress = 0x100;   // Extended Frame
    g_mcmcan.canNodeConfig.messageRAM.standardFilterListStartAddress = 0x100;   // Standard Frame
    g_mcmcan.canNodeConfig.messageRAM.rxBuffersStartAddress = 0x200;
    g_mcmcan.canNodeConfig.messageRAM.txBuffersStartAddress = 0x400;
    g_mcmcan.canNodeConfig.messageRAM.baseAddress = MODULE_CAN0_RAM + NODE0_RAM_OFFSET;
    // transmit interrupt
    g_mcmcan.canNodeConfig.interruptConfig.transmissionCompletedEnabled = TRUE;
    g_mcmcan.canNodeConfig.interruptConfig.traco.priority = ISR_PRIORITY_CAN_TX;
    g_mcmcan.canNodeConfig.interruptConfig.traco.interruptLine = IfxCan_InterruptLine_0;
    g_mcmcan.canNodeConfig.interruptConfig.traco.typeOfService = IfxSrc_Tos_cpu0;
    // receive interrupt
    g_mcmcan.canNodeConfig.interruptConfig.messageStoredToDedicatedRxBufferEnabled = TRUE;
    g_mcmcan.canNodeConfig.interruptConfig.reint.priority = ISR_PRIORITY_CAN_RX;
    g_mcmcan.canNodeConfig.interruptConfig.reint.interruptLine = IfxCan_InterruptLine_1;
    g_mcmcan.canNodeConfig.interruptConfig.reint.typeOfService = IfxSrc_Tos_cpu0;
    g_mcmcan.canNodeConfig.baudRate.baudrate = 1000000; // 1M Baud
    g_mcmcan.canNodeConfig.pins = &Can00_pins;
    IfxCan_Can_initNode(&g_mcmcan.can00Node, &g_mcmcan.canNodeConfig);

    g_mcmcan.canFilter.number = 0;
    g_mcmcan.canFilter.elementConfiguration = IfxCan_FilterElementConfiguration_storeInRxBuffer;
    g_mcmcan.canFilter.id1 = 0x0;
    g_mcmcan.canFilter.rxBufferOffset = IfxCan_RxBufferId_0;
    IfxCan_Can_setStandardFilter(&g_mcmcan.can00Node, &g_mcmcan.canFilter);

    g_mcmcan.canFilter.number = 1;
    g_mcmcan.canFilter.elementConfiguration = IfxCan_FilterElementConfiguration_storeInRxBuffer;
    g_mcmcan.canFilter.id1 = 0x1;
    g_mcmcan.canFilter.rxBufferOffset = IfxCan_RxBufferId_1;
    IfxCan_Can_setStandardFilter(&g_mcmcan.can00Node, &g_mcmcan.canFilter);

    g_mcmcan.canFilter.number = 2;
    g_mcmcan.canFilter.elementConfiguration = IfxCan_FilterElementConfiguration_storeInRxBuffer;
    g_mcmcan.canFilter.id1 = 0x2;
    g_mcmcan.canFilter.rxBufferOffset = IfxCan_RxBufferId_1;
    IfxCan_Can_setStandardFilter(&g_mcmcan.can00Node, &g_mcmcan.canFilter);

}

void can00_send(const uint32 id, const char *msg, const uint32 length)
{
    IfxCan_Can_initMessage(&g_mcmcan.txMsg);

    g_mcmcan.txMsg.dataLengthCode = length;
//    g_mcmcan.txMsg.dataLengthCode = IfxCan_DataLengthCode_8;    // 8 bytes
    g_mcmcan.txMsg.frameMode = IfxCan_FrameMode_standard;       // Classic CAN

    uint32 *data_low = &msg[0];
    uint32 *data_high;
    if (length > 4) {
        data_high = &msg[4];
    }
    g_mcmcan.txMsg.bufferNumber = 0;
    g_mcmcan.txMsg.messageId = id;
    g_mcmcan.txData[0] = *data_low;
    if (length > 4) {
        g_mcmcan.txData[1] = *data_high;
    }
    g_mcmcan.txMsg.messageIdLength = IfxCan_MessageIdLength_standard;   // Standard Frame
    while( IfxCan_Status_notSentBusy ==
           IfxCan_Can_sendMessage(&g_mcmcan.can00Node, &g_mcmcan.txMsg, &g_mcmcan.txData[0]) )
    {
    }
}
