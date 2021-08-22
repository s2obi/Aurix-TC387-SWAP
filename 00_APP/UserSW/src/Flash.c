/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "00_APP/UserSW/inc/Flash.h"
#include <string.h>
#include <stdio.h>

/* AF40 0000 */
/* UCB00-11 */
uint32 buf_9[] = {
        0xB359003E, 0xA0000000, 0xD86CBDAB, 0x27934254,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x43211234, 0x00000000, 0x00000000, 0x00000000,
        0xB359003E, 0xA0000000, 0xD86CBDAB, 0x27934254,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x43211234, 0x00000000, 0x00000000, 0x00000000,
        0xB359003E, 0xA0000000, 0xD86CBDAB, 0x27934254,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x43211234, 0x00000000, 0x00000000, 0x00000000,
        0xB359003E, 0xA0000000, 0xD86CBDAB, 0x27934254,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x43211234, 0x00000000, 0x00000000, 0x00000000,
        0xB359003E, 0xA0000000, 0xD86CBDAB, 0x27934254,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x43211234, 0x00000000, 0x00000000, 0x00000000,
        0xB359003E, 0xA0000000, 0xD86CBDAB, 0x27934254,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x43211234, 0x00000000, 0x00000000, 0x00000000,
        0xB359003E, 0xA0000000, 0xD86CBDAB, 0x27934254,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x43211234, 0x00000000, 0x00000000, 0x00000000,
        0xB359003E, 0xA0000000, 0xD86CBDAB, 0x27934254,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x43211234, 0x00000000, 0x00000000, 0x00000000
};


/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/**
 * \brief Erase one sector
 * \@param sector address
 */
void pfls_erase(uint32 pfls_addr)
{
    /* Get the current password of the Safety WatchDog module */
    uint16 endInitSafetyPassword = IfxScuWdt_getSafetyWatchdogPasswordInline();

    /* Erase the sector */
    IfxScuWdt_clearSafetyEndinitInline(endInitSafetyPassword);      /* Disable EndInit protection                   */
    IfxFlash_eraseSector(pfls_addr);                                /* Erase the given sector */

    IfxScuWdt_setSafetyEndinitInline(endInitSafetyPassword);        /* Enable EndInit protection                    */

    /* Wait until the sector is erased */
    IfxFlash_waitUnbusyAll();
}

/**
 * \brief Erase all inactive PFLASH sectors
 * \return None
 */
void pfls_MassErase(void)
{
    for (uint32 pfls_sector_start = 0xA0600000; pfls_sector_start < 0xA0C00000; pfls_sector_start += PFLASH_LOGICAL_SECTOR_SIZE) {
        pfls_erase(pfls_sector_start);
    }
}

/**
 * \brief Write page into pflash memory
 * \param @pfls_addr pflash address
 * \param @buf data
 * \param @len length of data
 * \return None
 */
void pfls_write(uint32 pfls_addr, uint32 *buf, int len)
{
   uint32 page;                                                /* Variable to cycle over all the pages             */
   uint32 offset;                                              /* Variable to cycle over all the words in a page   */

   /* Get the current password of the Safety WatchDog module */
   uint16 endInitSafetyPassword = IfxScuWdt_getSafetyWatchdogPasswordInline();

   /* Write all the pages */
   int total_page = len / 8, buf_idx = 0;
   if (len % 8 != 0) {
       total_page++;
   }
   for(page = 0; page < total_page; page++)              /* Loop over all the pages                  */
   {
       uint32 pageAddr = pfls_addr + (page * PFLASH_PAGE_LENGTH);   /* Get the address of the page              */

       /* Enter in page mode */
       IfxFlash_enterPageMode(pageAddr);

       /* Wait until page mode is entered */
       IfxFlash_waitUnbusyAll();

       /* Write 32 bytes (8 double words) into the assembly buffer */
       for(offset = 0; offset < PFLASH_PAGE_LENGTH; offset += 0x8)     /* Loop over the page length                */
       {
           IfxFlash_loadPage2X32(pageAddr, buf[buf_idx], buf[buf_idx + 1]); /* Load 2 words of 32 bits each */
           buf_idx += 2;
           if (buf_idx >= len) {
               IfxFlash_loadPage2X32(pageAddr, 0x00000000, 0x00000000); /* Load 2 words of 32 bits each */
               break;
           }
       }

       /* Write the page */
       IfxScuWdt_clearSafetyEndinitInline(endInitSafetyPassword);      /* Disable EndInit protection               */
       IfxFlash_writePage(pageAddr);                                   /* Write the page */
       IfxScuWdt_setSafetyEndinitInline(endInitSafetyPassword);        /* Enable EndInit protection                */

       /* Wait until the page is written in the Program Flash memory */
       IfxFlash_waitUnbusyAll();
   }
}

void pfls_reprogram(void)
{
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
//    uint32 ucb_sector_start;
//    for (ucb_sector_start = UCB_BMHD0_ORIG; ucb_sector_start < UCB_BMHD3_ORIG; ucb_sector_start += UCB_LOGICAL_SECTOR_SIZE) {
//        ucb_erase(ucb_sector_start);
//    }
//    for (ucb_sector_start = UCB_BMHD0_COPY; ucb_sector_start < UCB_BMHD3_COPY; ucb_sector_start += UCB_LOGICAL_SECTOR_SIZE) {
//        ucb_erase(ucb_sector_start);
//    }

    // UCB 00-11 Write
    //0xB359003E, 0xA0000000, 0xD86CBDAB, 0x27934254
//    ucb_write(UCB_BMHD0_COPY, (uint32)0xB359003E, (uint32)0xA0000000);
//    ucb_write(UCB_BMHD0_COPY + 0x8, (uint32)0xD86CBDAB, 0x27934254);
//    ucb_write(UCB_BMHD0_COPY + 0x1F0, (uint32)0x43211234, 0x00000000);
//    ucb_write(UCB_BMHD1_COPY, (uint32)0xB359003E, (uint32)0xA0000000);
//    ucb_write(UCB_BMHD1_COPY + 0x8, (uint32)0xD86CBDAB, 0x27934254);
//    ucb_write(UCB_BMHD1_COPY + 0x1F0, (uint32)0x43211234, 0x00000000);
//    ucb_write(UCB_BMHD2_COPY, (uint32)0xB359003E, (uint32)0xA0000000);
//    ucb_write(UCB_BMHD2_COPY + 0x8, (uint32)0xD86CBDAB, 0x27934254);
//    ucb_write(UCB_BMHD2_COPY + 0x1F0, (uint32)0x43211234, 0x00000000);
//    ucb_write(UCB_BMHD3_COPY, (uint32)0xB359003E, (uint32)0xA0000000);
//    ucb_write(UCB_BMHD3_COPY + 0x8, (uint32)0xD86CBDAB, 0x27934254);
//    ucb_write(UCB_BMHD3_COPY + 0x1F0, (uint32)0x43211234, 0x00000000);
//
//    ucb_write(UCB_BMHD0_ORIG, (uint32)0xB359003E, (uint32)0xA0000000);
//    ucb_write(UCB_BMHD0_ORIG + 0x8, (uint32)0xD86CBDAB, 0x27934254);
//    ucb_write(UCB_BMHD0_ORIG + 0x1F0, (uint32)0x43211234, 0x00000000);
//    ucb_write(UCB_BMHD1_ORIG, (uint32)0xB359003E, (uint32)0xA0000000);
//    ucb_write(UCB_BMHD1_ORIG + 0x8, (uint32)0xD86CBDAB, 0x27934254);
//    ucb_write(UCB_BMHD1_ORIG + 0x1F0, (uint32)0x43211234, 0x00000000);
//    ucb_write(UCB_BMHD2_ORIG, (uint32)0xB359003E, (uint32)0xA0000000);
//    ucb_write(UCB_BMHD2_ORIG + 0x8, (uint32)0xD86CBDAB, 0x27934254);
//    ucb_write(UCB_BMHD2_ORIG + 0x1F0, (uint32)0x43211234, 0x00000000);
//    ucb_write(UCB_BMHD3_ORIG, (uint32)0xB359003E, (uint32)0xA0000000);
//    ucb_write(UCB_BMHD3_ORIG + 0x8, (uint32)0xD86CBDAB, 0x27934254);
//    ucb_write(UCB_BMHD3_ORIG + 0x1F0, (uint32)0x43211234, 0x00000000);

    //addr = 0xAF400000;
    //int buf9_len = sizeof(buf_9) / sizeof(uint32);
    //ucb_write_buf(addr, buf_9, buf9_len);

    // 락방지용 - 테스트시 메모리뷰 확인하면서 진행할것
//    ucb_write(0xAF4001F0, 0x43211234, 0x00000000);
//    ucb_write(0xAF4003F0, 0x43211234, 0x00000000);
//    ucb_write(0xAF4005F0, 0x43211234, 0x00000000);
//    ucb_write(0xAF4007F0, 0x43211234, 0x00000000);
//    ucb_write(0xAF4011F0, 0x43211234, 0x00000000);
//    ucb_write(0xAF4013F0, 0x43211234, 0x00000000);
//    ucb_write(0xAF4015F0, 0x43211234, 0x00000000);
//    ucb_write(0xAF4017F0, 0x43211234, 0x00000000);
}

/**
 * \brief UCB 영역을 erase한다.
 * \param ucb_addr UCBxx의 시작 주소
 * \return None
 */
void ucb_erase(uint32 ucb_addr)
{
    /* --------------- ERASE PROCESS --------------- */
    /* Get the current password of the Safety WatchDog module */
    uint16 endInitSafetyPassword = IfxScuWdt_getSafetyWatchdogPassword();

    /* Erase the sector */
    IfxScuWdt_clearSafetyEndinit(endInitSafetyPassword);        /* Disable EndInit protection                       */
    IfxFlash_eraseMultipleSectors(ucb_addr, DFLASH_NUM_SECTORS); /* Erase the given sector           */
    IfxScuWdt_setSafetyEndinit(endInitSafetyPassword);          /* Enable EndInit protection                        */

    /* Wait until the sector is erased */
    IfxFlash_waitUnbusyAll();
    IfxFlash_waitUnbusy(FLASH_MODULE, DATA_FLASH_0);
}

/**
 * \brief UCB 영역에 buf data를 write한다.
 * \param ucb_addr UCB 시작 주소
 * \param buf buffer data
 * \param len 페이지 수
 * \return None
 */
void ucb_write_buf(uint32 ucb_addr, uint32* buf, int len)
{
    uint32 page;                                                /* Variable to cycle over all the pages             */

    /* --------------- ERASE PROCESS --------------- */
    /* Get the current password of the Safety WatchDog module */
    uint16 endInitSafetyPassword = IfxScuWdt_getSafetyWatchdogPassword();

    /* Erase the sector */
    IfxScuWdt_clearSafetyEndinit(endInitSafetyPassword);        /* Disable EndInit protection                       */
    IfxFlash_eraseMultipleSectors(ucb_addr, DFLASH_NUM_SECTORS); /* Erase the given sector           */
    IfxScuWdt_setSafetyEndinit(endInitSafetyPassword);          /* Enable EndInit protection                        */

    /* Wait until the sector is erased */
    IfxFlash_waitUnbusy(FLASH_MODULE, DATA_FLASH_0);


    int total_page = len / 2, buf_idx = 0;
//    if (len % 2 != 0) {
//        total_page++;
//    }
    /* --------------- WRITE PROCESS --------------- */
    for(page = 0; page < total_page; page++)      /* Loop over all the pages                          */
    {
        uint32 pageAddr = ucb_addr + (page * DFLASH_PAGE_LENGTH); /* Get the address of the page     */

        /* Enter in page mode */
        IfxFlash_enterPageMode(pageAddr);

        /* Wait until page mode is entered */
        IfxFlash_waitUnbusy(FLASH_MODULE, DATA_FLASH_0);

        /* Load data to be written in the page */
        IfxFlash_loadPage2X32(pageAddr, buf[buf_idx], buf[buf_idx + 1]); /* Load two words of 32 bits each            */
        buf_idx += 2;
//        if (buf_idx >= len) {
//            IfxFlash_loadPage2X32(pageAddr, 0x00000000, 0x00000000); /* Load two words of 32 bits each            */
//            break;
//        }

        /* Write the loaded page */
        IfxScuWdt_clearSafetyEndinit(endInitSafetyPassword);    /* Disable EndInit protection                       */
        IfxFlash_writePage(pageAddr);                           /* Write the page                                   */
        IfxScuWdt_setSafetyEndinit(endInitSafetyPassword);      /* Enable EndInit protection                        */

        /* Wait until the data is written in the Data Flash memory */
        IfxFlash_waitUnbusy(FLASH_MODULE, DATA_FLASH_0);
    }
}

/*
 * Write 하기 전 ucb_erase()로 해당 block erase할 것
 */
/**
 * \brief UCB 영역에 데이터 write
 * \param ucb_addr ucbxx 시작 주소
 * \param data_h high data
 * \param data_l low data
 * \return None
 */
void ucb_write(uint32 ucb_addr, uint32 data_h, uint32 data_l)
{
    /* Get the current password of the Safety WatchDog module */
    uint16 endInitSafetyPassword = IfxScuWdt_getSafetyWatchdogPassword();

    // Write UCB Data
    IfxFlash_enterPageMode(ucb_addr);
    IfxFlash_waitUnbusy(FLASH_MODULE, DATA_FLASH_0);
    IfxFlash_loadPage2X32(ucb_addr, data_h, data_l);
    /* Write the loaded page */
    IfxScuWdt_clearSafetyEndinit(endInitSafetyPassword);    /* Disable EndInit protection                       */
    IfxFlash_writePage(ucb_addr);                           /* Write the page                                   */
    IfxScuWdt_setSafetyEndinit(endInitSafetyPassword);      /* Enable EndInit protection                        */
    IfxFlash_waitUnbusy(FLASH_MODULE, DATA_FLASH_0);
}

/* Memory A/B SWAP 활성화 */
void swap_enable(void)
{
    // UCB_SWAP_COPY 설정
    ucb_erase(UCB_SWAP_COPY);
    ucb_write(UCB_SWAP_COPY, 0x000000AA, UCB_SWAP_COPY);
    ucb_write(UCB_SWAP_COPY + 8, 0x57B5327F, UCB_SWAP_COPY + 8);
    ucb_write(UCB_SWAP_COPY + 0x1F0, 0x43211234, 0x00000000);
    // UCB_SWAP_ORIG 설정
    ucb_erase(UCB_SWAP_ORIG);
    ucb_write(UCB_SWAP_ORIG, 0x000000AA, UCB_SWAP_ORIG);
    ucb_write(UCB_SWAP_ORIG + 8, 0x57B5327F, UCB_SWAP_ORIG + 8);
    ucb_write(UCB_SWAP_ORIG + 0x1F0, 0x43211234, 0x00000000);

    // Enable SWAP
    ucb_write(UCB_OTP0_COPY + 0x1E8, 0x00030000, 0x00000000);
    ucb_write(UCB_OTP0_ORIG + 0x1E8, 0x00030000, 0x00000000);
}

/* Memory A/B SWAP Configuration 설정 업데이트 */
void swap_update(void)
{
    // 현재 사용중인 swap configuration entry 체크
    uint32 scu_stmem1 = SCU_STMEM1.U;
    uint32 swapctrl = SCU_SWAPCTRL.U;
    int entry_num = ((scu_stmem1 & 0x00F80000) >> 19) / 2;  /* 현재 활성화된 Configuration Entry 번호 */
    uint32 addr_cfg = (swapctrl & 0x00000003);              /* 01b - A active, 10b - B active */

    // UCB_SWAP_COPY configuration 업데이트
    ucb_erase(UCB_SWAP_COPY);
    for (int i = 0; i <= entry_num; i++) {
        if (i % 2 == 0) {
            ucb_write(UCB_SWAP_COPY + (i * 0x10), 0x000000AA, UCB_SWAP_COPY + (i * 0x10));
        } else {
            ucb_write(UCB_SWAP_COPY + (i * 0x10), 0x00000055, UCB_SWAP_COPY + (i * 0x10));
        }
        ucb_write(UCB_SWAP_COPY + (i * 0x10) + 8, 0xFFFFFFFF, 0xFFFFFFFF);
    }
    if ((entry_num + 1) % 2 == 0) {
        ucb_write(UCB_SWAP_COPY + (entry_num * 0x10), 0x000000AA, UCB_SWAP_COPY + (entry_num * 0x10));
    } else {
        ucb_write(UCB_SWAP_COPY + (entry_num * 0x10), 0x00000055, UCB_SWAP_COPY + (entry_num * 0x10));
    }
    ucb_write(UCB_SWAP_COPY + 0x1F0, 0x43211234, 0x00000000); // confirmation code 업데이트
    // UCB_SWAP_ORIG configuration 업데이트
    ucb_erase(UCB_SWAP_ORIG);
    for (int i = 0; i <= entry_num; i++) {
        if (i % 2 == 0) {
            ucb_write(UCB_SWAP_ORIG + (i * 0x10), 0x000000AA, UCB_SWAP_ORIG + (i * 0x10));
        } else {
            ucb_write(UCB_SWAP_ORIG + (i * 0x10), 0x00000055, UCB_SWAP_ORIG + (i * 0x10));
        }
        ucb_write(UCB_SWAP_ORIG + (i * 0x10) + 8, 0xFFFFFFFF, 0xFFFFFFFF);
    }
    if ((entry_num + 1) % 2 == 0) {
        ucb_write(UCB_SWAP_ORIG + (entry_num * 0x10), 0x000000AA, UCB_SWAP_ORIG + (entry_num * 0x10));
    } else {
        ucb_write(UCB_SWAP_ORIG + (entry_num * 0x10), 0x00000055, UCB_SWAP_ORIG + (entry_num * 0x10));
    }
    ucb_write(UCB_SWAP_ORIG + 0x1F0, 0x43211234, 0x00000000); // confirmation code 업데이트
}

/* SWAP 비활성화 */
void swap_disable(void)
{
    // Erase UCB31(UCB_SWAP_COPY)
    ucb_erase(UCB_SWAP_COPY);
    // Write Confirmation Code into UCB31
    ucb_write(UCB_SWAP_COPY + 0x1F0, (uint32)0x43211234, (uint32)0x00000000);

    // Delete UCB23(UCB_SWAP_ORIG)
    ucb_erase(UCB_SWAP_ORIG);
    // Write Confirmation Code into UCB23
    ucb_write(UCB_SWAP_ORIG + 0x1F0, (uint32)0x43211234, (uint32)0x00000000);

    // Erase UCB40(UCB_OTP0_COPY)
    ucb_erase(UCB_OTP0_COPY);
    // Write Confirmation Code into UCB40
    ucb_write(UCB_OTP0_COPY + 0x1F0, (uint32)0x43211234, (uint32)0x00000000);

    // Erase UCB32(UCB_OTP0_ORIG)
    ucb_erase(UCB_OTP0_ORIG);
    // Write Confirmation Code into UCB32
    ucb_write(UCB_OTP0_ORIG + 0x1F0, (uint32)0x43211234, (uint32)0x00000000);
}
