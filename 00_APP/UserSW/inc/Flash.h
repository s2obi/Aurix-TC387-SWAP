#ifndef USERSW_INC_FLASH_H_
#define USERSW_INC_FLASH_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "00_APP/UserSW/inc/g_port.h"
#include "Ifx_Types.h"
#include "IfxFlash.h"
#include "IfxCpu.h"
#include "Bsp.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define PFLASH_PAGE_LENGTH          IFXFLASH_PFLASH_PAGE_LENGTH /* 0x20 = 32 Bytes (smallest unit that can be
                                                                 * programmed in the Program Flash memory (PFLASH)) */
#define DFLASH_PAGE_LENGTH          IFXFLASH_DFLASH_PAGE_LENGTH /* 0x8 = 8 Bytes (smallest unit that can be
                                                                 * programmed in the Data Flash memory (DFLASH))    */
#define FLASH_MODULE                0                           /* Macro to select the flash (PMU) module           */
#define PROGRAM_FLASH_0             IfxFlash_FlashType_P0       /* Define the Program Flash Bank to be used         */
#define PROGRAM_FLASH_1             IfxFlash_FlashType_P1
#define PROGRAM_FLASH_2             IfxFlash_FlashType_P2
#define PROGRAM_FLASH_3             IfxFlash_FlashType_P3
#define DATA_FLASH_0                IfxFlash_FlashType_D0       /* Define the Data Flash Bank to be used            */

#define PFLASH_NUM_PAGE_TO_FLASH    2                           /* Number of pages to flash in the PFLASH           */
#define PFLASH_NUM_SECTORS          1                           /* Number of PFLASH sectors to be erased            */
#define DFLASH_NUM_PAGE_TO_FLASH    8                           /* Number of pages to flash in the DFLASH           */
#define DFLASH_NUM_SECTORS          1                           /* Number of DFLASH sectors to be erased            */

#define UCB_BMHD0_ORIG              0xAF400000                 /* UCB00 */
#define UCB_BMHD1_ORIG              0xAF400200                 /* UCB01 */
#define UCB_BMHD2_ORIG              0xAF400400                 /* UCB02 */
#define UCB_BMHD3_ORIG              0xAF400600                 /* UCB03 */
#define UCB_BMHD0_COPY              0xAF401000                 /* UCB08 */
#define UCB_BMHD1_COPY              0xAF401200                 /* UCB09 */
#define UCB_BMHD2_COPY              0xAF401400                 /* UCB10 */
#define UCB_BMHD3_COPY              0xAF401600                 /* UCB11 */
#define UCB_SWAP_ORIG               0xAF402E00                 /* UCB23 */
#define UCB_SWAP_COPY               0xAF403E00                 /* UCB31 */
#define UCB_OTP0_ORIG               0xAF404000                 /* UCB32 */
#define UCB_OTP0_COPY               0xAF405000                 /* UCB40 */

#define PFLASH_LOGICAL_SECTOR_SIZE  0x4000
#define UCB_LOGICAL_SECTOR_SIZE     0x200


/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void pfls_erase(uint32 pfls_addr);
void pfls_MassErase(void);
void pfls_write(uint32 pfls_addr, uint32* buf, int len);
void pfls_reprogram(void);
void ucb_erase(uint32 ucb_addr);
void ucb_write_buf(uint32 ucb_addr, uint32* buf, int len);
void ucb_write(uint32 ucb_addr, uint32 data_h, uint32 data_l);
void swap_enable(void);
void swap_update(void);
void swap_disable(void);

#endif /* USERSW_INC_FLASH_H_ */
