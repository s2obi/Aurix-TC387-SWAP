#ifndef USERSW_INC_MCMCAN_H_
#define USERSW_INC_MCMCAN_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "00_APP/UserSW/inc/g_port.h"
#include "Ifx_Types.h"
#include "IfxCan_Can.h"
#include "IfxCan.h"
#include "IfxCpu_Irq.h"
#include "IfxPort.h"                                        /* For GPIO Port Pin Control                            */

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define CAN_MESSAGE_ID              (uint32)0x777           /* Message ID that will be used in arbitration phase    */
#define INVALID_RX_DATA_VALUE       0xA5                    /* Used to invalidate RX message data content           */
#define INVALID_ID_VALUE            (uint32)0xFFFFFFFF      /* Used to invalidate RX message ID value               */
#define ISR_PRIORITY_CAN_TX         2                       /* Define the CAN TX interrupt priority                 */
#define ISR_PRIORITY_CAN_RX         1                       /* Define the CAN RX interrupt priority                 */
#define TX_DATA_LOW_WORD            (uint32)0xC0CAC01A      /* Define CAN data lower word to be transmitted         */
#define TX_DATA_HIGH_WORD           (uint32)0xBA5EBA11      /* Define CAN data higher word to be transmitted        */
#define MAXIMUM_CAN_DATA_PAYLOAD    2                       /* Define maximum classical CAN payload in 4-byte words */

#define MODULE_CAN0_RAM             0xF0200000
#define MODULE_CAN1_RAM             0xF0210000
#define NODE0_RAM_OFFSET            0x0

/*********************************************************************************************************************/
/*--------------------------------------------------Data Structures--------------------------------------------------*/
/*********************************************************************************************************************/
typedef struct
{
    IfxCan_Can_Config canConfig;                            /* CAN module configuration structure                   */
    IfxCan_Can canModule;                                   /* CAN module handle                                    */
    IfxCan_Can_Node can00Node;                              /* CAN source node handle data structure                */
    IfxCan_Can_NodeConfig canNodeConfig;                    /* CAN node configuration structure                     */
    IfxCan_Filter canFilter;                                /* CAN filter configuration structure                   */
    IfxCan_Message txMsg;                                   /* Transmitted CAN message structure                    */
    IfxCan_Message rxMsg;                                   /* Received CAN message structure                       */
    uint32 txData[MAXIMUM_CAN_DATA_PAYLOAD];                /* Transmitted CAN data array                           */
    uint32 rxData[MAXIMUM_CAN_DATA_PAYLOAD];                /* Received CAN data array                              */
} McmcanType;

/*********************************************************************************************************************/
/*-----------------------------------------------Function Prototypes-------------------------------------------------*/
/*********************************************************************************************************************/
void initCAN(void);
void can00_send(const uint32 id, const char *msg, const uint32 length);

#endif /* USERSW_INC_MCMCAN_H_ */
