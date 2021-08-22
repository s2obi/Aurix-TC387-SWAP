/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "00_APP/UserSW/inc/MCMCAN.h"
#include <stdio.h>
#include <string.h>

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
McmcanType                  g_mcmcan;                       /* Global MCMCAN configuration and control structure    */
char record_buf[19];                                        /* 수신받은 Hex 데이터의 한 레코드를 저장하는 버퍼 */
uint8 record_idx = 0;                                       /* 레코드 버퍼 index */
uint8 record_len = 0;                                       /* 레코드 길이 */

uint32 pfls_pageData[8];                                    /* PFlash 영역에 write할 32byte page */
uint8 pflsDataCount = 0;                                    /* PFlash page 데이터 개수 */
uint8 pflsDataIdx = 0;                                      /* PFlash page 데이터 index */

uint32 dfls_pageData[2];                                    /* DFlash 영역에 write할 8byte page */
uint8 dflsDataCount = 0;                                    /* DFlash page 데이터 개수 */
uint8 dflsDataIdx = 0;                                      /* DFlash page 데이터 index */

uint32 pageStartAddr = 0;                                       /* flash write 시작 주소 */
uint32 pageStartAddr_low = 0;
uint32 relativeAddr_prev = 0;
uint32 relativeAddr_now = 0;
uint32 pageStartAddr_high = 0;

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
 * Blink 50ms LED1 to indicate successful CAN message transmission.
 */
void canIsrTxHandler(void)
{
    IfxCan_Node_clearInterruptFlag(g_mcmcan.can00Node.node, IfxCan_Interrupt_transmissionCompleted);
    IfxPort_togglePin(LED1);
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
    IfxPort_togglePin(LED2);

    /* Clear the "New Data" flag; as long as the "New Data" flag is set, the respective Rx buffer is
     * locked against updates from received matching frames.
     */
    IfxCan_Node_clearRxBufferNewDataFlag(g_mcmcan.can00Node.node, g_mcmcan.canFilter.rxBufferOffset);

    /* Read the received CAN message */
    IfxCan_Can_readMessage(&g_mcmcan.can00Node, &g_mcmcan.rxMsg, g_mcmcan.rxData);

    if (g_mcmcan.rxMsg.messageId == 0x10) {                         /* 수신받은 CAN Message를 record_buf에 추가한다. */
        readRxDataUint32();
    } else if (g_mcmcan.rxMsg.messageId == 0x09) {                  /* record_buf 처리                                                     */
        if (record_buf[8] == '4') {                                 /* Record Type: Extended linear address */
            /* page에 데이터가 남아있는 경우 flash한다. */
            write_remain_page();

            pageStartAddr = 0;

            /* 32-bit address 상위 16bit 계산 */
            pageStartAddr_low = getDataFromAddrRecord();
        } else if (record_buf[8] == '0') {                          /* Record Type: Data */
            if (pageStartAddr_low < 0xAF000000) {                   /* PFlash 영역 처리 */
                /* 현재 레코드의 주솟값을 구한다. */
                pageStartAddr_high = getAddrFromDataRecord();

                /* 현재 레코드가 page의 첫 번째 데이터인 경우, pageStartAddr을 계산한다. */
                if (pflsDataCount == 0) {
                    pageStartAddr = pageStartAddr_low | pageStartAddr_high;
                }

                /* 현재 page가 비어있지 않은 경우 이전 주솟값을 업데이트한다. */
                if (pflsDataCount != 0) {
                    relativeAddr_prev = relativeAddr_now;
                }

                /* 현재 레코드의 주소와 이전 레코드의 주소를 비교하여 불연속적인 경우 현재 page를 write한다. */
                relativeAddr_now = pageStartAddr_high;
                if (relativeAddr_now - 4 != relativeAddr_prev) {
                    pfls_write(pageStartAddr, pfls_pageData, pflsDataCount);
                    pflsDataCount = 0;
                    pflsDataIdx = 0;
                    memset(pfls_pageData, 0, sizeof(pfls_pageData));
                    pageStartAddr = pageStartAddr_low | relativeAddr_now;
                }

                /* page에 데이터 저장 */
                pfls_pageData[pflsDataIdx] = getDataFromDataRecord();
                pflsDataCount++;
                pflsDataIdx++;

                /* page가 가득 찬 경우 pflash에 write한다. */
                if (pflsDataCount == 8) {
                    pfls_write(pageStartAddr, pfls_pageData, pflsDataCount);
                    pflsDataCount = 0;
                    pflsDataIdx = 0;
                    memset(pfls_pageData, 0, sizeof(pfls_pageData));
                }
            } else { /* DFlash 영역 처리 */
                /* 현재 레코드의 주솟값을 구한다. */
                pageStartAddr_high = getAddrFromDataRecord();

                /* 현재 레코드가 page의 첫 번째 데이터인 경우, pageStartAddr을 계산한다. */
                if (dflsDataCount == 0) {
                    pageStartAddr = pageStartAddr_low | pageStartAddr_high;
                }

                /* 현재 page가 비어있지 않은 경우 이전 주솟값을 업데이트한다. */
                if (dflsDataCount != 0) {
                    relativeAddr_prev = relativeAddr_now;
                }

                /* 현재 레코드의 주소와 이전 레코드의 주소를 비교하여 불연속적인 경우 현재 page를 write한다. */
                relativeAddr_now = pageStartAddr_high;
                if (relativeAddr_now - 4 != relativeAddr_prev) {
//                    ucb_write_buf(pageStartAddr, dfls_pageData, dflsDataCount);
                    dflsDataCount = 0;
                    dflsDataIdx = 0;
                    memset(dfls_pageData, 0, sizeof(dfls_pageData));
                    pageStartAddr = pageStartAddr_low | relativeAddr_now;
                }

                /* page에 데이터 저장 */
                dfls_pageData[dflsDataIdx] = getDataFromDataRecord();
                dflsDataCount++;
                dflsDataIdx++;

                /* page가 가득 찬 경우 dflash에 write한다. */
                if (dflsDataCount == 2) {
//                    ucb_write_buf(pageStartAddr, dfls_pageData, dflsDataCount);
                    dflsDataCount = 0;
                    dflsDataIdx = 0;
                    memset(dfls_pageData, 0, sizeof(dfls_pageData));
                }
            }
        }

        /* record_buf 초기화 */
        record_idx = 0;
        memset(record_buf, 0, sizeof(record_buf));

        IfxPort_togglePin(LED7);
    } else if (g_mcmcan.rxMsg.messageId == 0x11) { /* SWAP 활성화 */
        /* page에 데이터가 남아있는 경우 flash한다. */
        write_remain_page();
//        swap_enable();
    }
    IfxPort_setPinHigh(LED2);
}

/* 주소 레코드에서 상위 16bit 기준주솟값을 반환한다. */
uint32 getDataFromAddrRecord(void)
{
    uint32 addr_low;

    addr_low = ((record_buf[9] <= '9' ? (record_buf[9] - '0') : (record_buf[9] - 'A' + 10)) << 28 & 0xF0000000);
    addr_low |= ((record_buf[10] <= '9' ? (record_buf[10] - '0') : (record_buf[10] - 'A' + 10)) << 24 & 0xFF000000);
    addr_low |= ((record_buf[11] <= '9' ? (record_buf[11] - '0') : (record_buf[11] - 'A' + 10)) << 20 & 0xFFF00000);
    addr_low |= ((record_buf[12] <= '9' ? (record_buf[12] - '0') : (record_buf[12] - 'A' + 10)) << 16 & 0xFFFF0000);

    return addr_low;
}

/* 데이터 레코드에서 상대주솟값을 반환한다. */
uint32 getAddrFromDataRecord(void)
{
    uint32 addr_high;

    addr_high = ((record_buf[3] <= '9' ? (record_buf[3] - '0') : (record_buf[3] - 'A' + 10)) << 12 & 0x0000F000);
    addr_high |= ((record_buf[4] <= '9' ? (record_buf[4] - '0') : (record_buf[4] - 'A' + 10)) << 8 & 0x0000FF00);
    addr_high |= ((record_buf[5] <= '9' ? (record_buf[5] - '0') : (record_buf[5] - 'A' + 10)) << 4 & 0x0000FFF0);
    addr_high |= ((record_buf[6] <= '9' ? (record_buf[6] - '0') : (record_buf[6] - 'A' + 10)) & 0x0000FFFF);

    return addr_high;
}

/* 데이터 레코드에서 데이터값을 반환한다. */
uint32 getDataFromDataRecord(void)
{
    uint32 data;

    data = ((record_buf[9] <= '9' ? (record_buf[9] - '0') : (record_buf[9] - 'A' + 10)) << 28 & 0xF0000000);
    data |= ((record_buf[10] <= '9' ? (record_buf[10] - '0') : (record_buf[10] - 'A' + 10)) << 24 & 0xFF000000);
    data |= ((record_buf[11] <= '9' ? (record_buf[11] - '0') : (record_buf[11] - 'A' + 10)) << 20 & 0xFFF00000);
    data |= ((record_buf[12] <= '9' ? (record_buf[12] - '0') : (record_buf[12] - 'A' + 10)) << 16 & 0xFFFF0000);
    data |= ((record_buf[13] <= '9' ? (record_buf[13] - '0') : (record_buf[13] - 'A' + 10)) << 12 & 0x0000F000);
    data |= ((record_buf[14] <= '9' ? (record_buf[14] - '0') : (record_buf[14] - 'A' + 10)) << 8 & 0x0000FF00);
    data |= ((record_buf[15] <= '9' ? (record_buf[15] - '0') : (record_buf[15] - 'A' + 10)) << 4 & 0x0000FFF0);
    data |= ((record_buf[16] <= '9' ? (record_buf[16] - '0') : (record_buf[16] - 'A' + 10)) & 0x0000FFFF);

    return data;
}

/* CAN 메시지 ASCII 값을 저장한다.*/
void readRxDataUint32(void)
{
    for (int i = 0; i < g_mcmcan.rxMsg.dataLengthCode; i++) {
        if (i >= 4) {
            record_buf[record_idx++] = (char)(g_mcmcan.rxData[1] >> ((i - 4) *8));
        } else {
            record_buf[record_idx++] = (char)(g_mcmcan.rxData[0] >> (i * 8));
        }
    }
}

/* page에 남아있는 데이터를 flash에 write한다. */
void write_remain_page(void)
{
    if (pflsDataCount > 0) {
        pfls_write(pageStartAddr, pfls_pageData, pflsDataCount);
        pflsDataCount = 0;
        pflsDataIdx = 0;
        memset(pfls_pageData, 0, sizeof(pfls_pageData));
    }
    if (dflsDataCount > 0) {
        //dfls_write();
        dflsDataCount = 0;
        dflsDataIdx = 0;
        memset(dfls_pageData, 0, sizeof(dfls_pageData));
    }
}

/* CAN0 모듈 초기화 */
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

    /* One Record Receive Complete */
    g_mcmcan.canFilter.number = 0;
    g_mcmcan.canFilter.elementConfiguration = IfxCan_FilterElementConfiguration_storeInRxBuffer;
    g_mcmcan.canFilter.id1 = 0x09;
    g_mcmcan.canFilter.rxBufferOffset = IfxCan_RxBufferId_0;
    IfxCan_Can_setStandardFilter(&g_mcmcan.can00Node, &g_mcmcan.canFilter);

    /* Hex Data Receive */
    g_mcmcan.canFilter.number = 1;
    g_mcmcan.canFilter.elementConfiguration = IfxCan_FilterElementConfiguration_storeInRxBuffer;
    g_mcmcan.canFilter.id1 = 0x10;
    g_mcmcan.canFilter.rxBufferOffset = IfxCan_RxBufferId_0;
    IfxCan_Can_setStandardFilter(&g_mcmcan.can00Node, &g_mcmcan.canFilter);

    /* Hex Transfer Complete */
    g_mcmcan.canFilter.number = 2;
    g_mcmcan.canFilter.elementConfiguration = IfxCan_FilterElementConfiguration_storeInRxBuffer;
    g_mcmcan.canFilter.id1 = 0x11;
    g_mcmcan.canFilter.rxBufferOffset = IfxCan_RxBufferId_0;
    IfxCan_Can_setStandardFilter(&g_mcmcan.can00Node, &g_mcmcan.canFilter);

    /* Hex Transfer Failed */
    g_mcmcan.canFilter.number = 3;
    g_mcmcan.canFilter.elementConfiguration = IfxCan_FilterElementConfiguration_storeInRxBuffer;
    g_mcmcan.canFilter.id1 = 0x12;
    g_mcmcan.canFilter.rxBufferOffset = IfxCan_RxBufferId_0;
    IfxCan_Can_setStandardFilter(&g_mcmcan.can00Node, &g_mcmcan.canFilter);

    /* Hex Download Failed */
    g_mcmcan.canFilter.number = 4;
    g_mcmcan.canFilter.elementConfiguration = IfxCan_FilterElementConfiguration_storeInRxBuffer;
    g_mcmcan.canFilter.id1 = 0x04;
    g_mcmcan.canFilter.rxBufferOffset = IfxCan_RxBufferId_0;
    IfxCan_Can_setStandardFilter(&g_mcmcan.can00Node, &g_mcmcan.canFilter);
}

/* CAN0 메시지 전송 */
void can00_send(const uint32 id, const char *msg, const uint32 length)
{
    IfxCan_Can_initMessage(&g_mcmcan.txMsg); // 전송 메시지 버퍼 초기화

    g_mcmcan.txMsg.dataLengthCode = length; // DLC 설정
    g_mcmcan.txMsg.frameMode = IfxCan_FrameMode_standard;       // Classic CAN

    uint32 *data_low = (uint32 *)&msg[0];
    uint32 *data_high;
    if (length > 4) {
        data_high = (uint32 *)&msg[4];
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
