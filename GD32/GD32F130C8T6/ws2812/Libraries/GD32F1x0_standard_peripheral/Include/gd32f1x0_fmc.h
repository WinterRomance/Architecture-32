/*!
    \file    gd32f1x0_fmc.h
    \brief   definitions for the FMC

    \version 2025-01-01, V3.7.0, firmware update for GD32F1x0(x=3,5)
*/

/*
    Copyright (c) 2025, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#ifndef GD32F1X0_FMC_H
#define GD32F1X0_FMC_H

#include "gd32f1x0.h"

/* FMC and option byte definition */
#define FMC                     FMC_BASE                        /*!< FMC register base address */
#define OB                      OB_BASE                         /*!< option byte base address */

/* registers definitions */
#define FMC_WS                  REG32(FMC + 0x00000000U)        /*!< FMC wait state register */
#define FMC_KEY                 REG32(FMC + 0x00000004U)        /*!< FMC unlock key register */
#define FMC_OBKEY               REG32(FMC + 0x00000008U)        /*!< FMC option bytes unlock key register */
#define FMC_STAT                REG32(FMC + 0x0000000CU)        /*!< FMC status register */
#define FMC_CTL                 REG32(FMC + 0x00000010U)        /*!< FMC control register */
#define FMC_ADDR                REG32(FMC + 0x00000014U)        /*!< FMC address register */
#define FMC_OBSTAT              REG32(FMC + 0x0000001CU)        /*!< FMC option bytes status register */
#define FMC_WP                  REG32(FMC + 0x00000020U)        /*!< FMC write protection register */
#define FMC_WSEN                REG32(FMC + 0x000000FCU)        /*!< FMC wait state enable register */
#define FMC_PID                 REG32(FMC + 0x00000100U)        /*!< FMC product ID register */

#define OP_BYTE(x)              REG8(OB + ((uint32_t)((uint32_t)0x00000002U * (x))))     /*!< option byte value */
#define OB_SPC                  REG8(OB + 0x00000000U)                                   /*!< option byte security protection value */
#define OB_USER                 REG8(OB + 0x00000002U)                                   /*!< option byte user value */
#define OB_DATA0                REG8(OB + 0x00000004U)                                   /*!< option byte data0 value */
#define OB_DATA1                REG8(OB + 0x00000006U)                                   /*!< option byte data1 value */
#define OB_WP0                  REG8(OB + 0x00000008U)                                   /*!< option byte write protection 0 value */
#define OB_WP1                  REG8(OB + 0x0000000AU)                                   /*!< option byte write protection 1 value */

/* bits definitions */
/* FMC_WS */
#define FMC_WS_WSCNT            BITS(0,2)                   /*!< wait state counter */

/* FMC_KEY */
#define FMC_KEY_KEY             BITS(0,31)                  /*!< FMC main flash unlock key bits */

/* FMC_OBKEY */
#define FMC_OBKEY_OBKEY         BITS(0,31)                  /*!< option bytes unlock key bits */

/* FMC_STAT */
#define FMC_STAT_BUSY           BIT(0)                      /*!< flash busy flag bit */
#define FMC_STAT_PGERR          BIT(2)                      /*!< flash program error flag bit */
#define FMC_STAT_WPERR          BIT(4)                      /*!< flash write protection error flag bit */
#define FMC_STAT_ENDF           BIT(5)                      /*!< flash end of operation flag bit */

/* FMC_CTL */
#define FMC_CTL_PG              BIT(0)                      /*!< main flash program command bit */
#define FMC_CTL_PER             BIT(1)                      /*!< main flash page erase bit */
#define FMC_CTL_MER             BIT(2)                      /*!< main flash mass erase bit */
#define FMC_CTL_OBPG            BIT(4)                      /*!< option bytes program command bit */
#define FMC_CTL_OBER            BIT(5)                      /*!< option bytes erase command bit */
#define FMC_CTL_START           BIT(6)                      /*!< send erase command to FMC bit */
#define FMC_CTL_LK              BIT(7)                      /*!< flash lock bit */
#define FMC_CTL_OBWEN           BIT(9)                      /*!< option bytes erase/program enable bit */
#define FMC_CTL_ERRIE           BIT(10)                     /*!< error interrupt enable bit */
#define FMC_CTL_ENDIE           BIT(12)                     /*!< end of operation interrupt enable bit */
#define FMC_CTL_OBRLD           BIT(13)                     /*!< option bytes reload bit */

/* FMC_ADDR */
#define FMC_ADDR_ADDR           BITS(0,31)                  /*!< flash command address bits */

/* FMC_OBSTAT */
#define FMC_OBSTAT_OBERR        BIT(0)                      /*!< option bytes read error bit */
#define FMC_OBSTAT_PLVL         BITS(1,2)                   /*!< protection level bits */
#define FMC_OBSTAT_USER         BITS(8,15)                  /*!< option bytes user bits */
#define FMC_OBSTAT_DATA         BITS(16,31)                 /*!< option bytes data bits */

/* FMC_WSEN */
#define FMC_WSEN_WSEN           BIT(0)                      /*!< FMC wait state enable bit */

/* FMC_PID */
#define FMC_PID_PID             BITS(0,31)                  /*!< product ID bits */

/* constants definitions */
/* fmc state */
typedef enum
{
    FMC_READY,                                              /*!< the operation has been completed */
    FMC_BUSY,                                               /*!< the operation is in progress */
    FMC_PGERR,                                              /*!< program error */
    FMC_WPERR,                                              /*!< erase/program protection error */
    FMC_TOERR,                                              /*!< timeout error */
    FMC_OB_HSPC                                             /*!< option byte security protection code high */
}fmc_state_enum;

/* unlock key */
#define UNLOCK_KEY0                ((uint32_t)0x45670123U)  /*!< unlock key 0 */
#define UNLOCK_KEY1                ((uint32_t)0xCDEF89ABU)  /*!< unlock key 1 */

/* wait state counter value */
#define WS_WSCNT_0                 ((uint8_t)0x00U)         /*!< 0 wait state added */
#define WS_WSCNT_1                 ((uint8_t)0x01U)         /*!< 1 wait state added */
#define WS_WSCNT_2                 ((uint8_t)0x02U)         /*!< 2 wait state added */

/* read protect configure */
#define FMC_NSPC                   ((uint8_t)0xA5U)         /*!< no security protection */
#define FMC_LSPC                   ((uint8_t)0xBBU)         /*!< low level security protection, any value except 0xA5 or 0xCC */
#define FMC_HSPC                   ((uint8_t)0xCCU)         /*!< high level security protection */

/* option byte write protection mask */
#define OB_LWP                     ((uint16_t)0x00FFU)      /*!< write protection low bits */
#define OB_HWP                     ((uint16_t)0xFF00U)      /*!< write protection high bits */

/* option byte software/hardware free watchdog timer */  
#define OB_FWDGT_HW                ((uint8_t)(~BIT(0)))     /*!< hardware free watchdog timer */
#define OB_FWDGT_SW                ((uint8_t)BIT(0))        /*!< software free watchdog timer */

/* option byte reset or not entering deep sleep mode */
#define OB_DEEPSLEEP_RST           ((uint8_t)(~BIT(1)))     /*!< generate a reset instead of entering deepsleep mode */
#define OB_DEEPSLEEP_NRST          ((uint8_t)BIT(1))        /*!< no reset when entering deepsleep mode */

/* option byte reset or not entering standby mode */
#define OB_STDBY_RST               ((uint8_t)(~BIT(2)))     /*!< generate a reset instead of entering standby mode */
#define OB_STDBY_NRST              ((uint8_t)BIT(2))        /*!< no reset when entering standby mode */

/* option byte OB_BOOT1_n set */
#define OB_BOOT1_SET_1             ((uint8_t)(~BIT(4)))     /*!< BOOT1 bit is 1 */
#define OB_BOOT1_SET_0             ((uint8_t)BIT(4))        /*!< BOOT1 bit is 0 */

/* option byte VDDA monitor enable/disable */
#define OB_VDDA_DISABLE            ((uint8_t)(~BIT(5)))     /*!< disable VDDA monitor */
#define OB_VDDA_ENABLE             ((uint8_t)BIT(5))        /*!< enable VDDA monitor */

/* option byte SRAM parity enable/disable */
#define OB_SRAM_PARITY_ENABLE      ((uint8_t)(~BIT(6)))     /*!< enable SRAM parity check */
#define OB_SRAM_PARITY_DISABLE     ((uint8_t)BIT(6))        /*!< disable SRAM parity check */

/* option byte reset value */
#define OB_USER_RSET               ((uint8_t)0xFFU)         /*!< reset option byte user byte */

/* option byte security protection level in FMC_OBSTAT register */
#define OB_OBSTAT_PLEVEL_NO        ((uint32_t)0x00000000U)  /*!< no security protection */
#define OB_OBSTAT_PLEVEL_LOW       ((uint32_t)0x00000002U)  /*!< low security protection */
#define OB_OBSTAT_PLEVEL_HIGH      ((uint32_t)0x00000006U)  /*!< high security protection */

/* option byte user mask */
#define OB_USER_MASK               ((uint8_t)0x88U)         /*!< OB_USER reserved bit mask */

/* option byte data mask */
#define OB_LDATA                   ((uint16_t)0x00FFU)      /*!< option byte data0 bit mask */
#define OB_HDATA                   ((uint16_t)0xFF00U)      /*!< option byte data1 bit mask */

/* FMC flags */
#define FMC_FLAG_BUSY              FMC_STAT_BUSY            /*!< FMC busy flag */
#define FMC_FLAG_PGERR             FMC_STAT_PGERR           /*!< FMC programming error flag */
#define FMC_FLAG_WPERR             FMC_STAT_WPERR           /*!< FMC write protection error flag */
#define FMC_FLAG_END               FMC_STAT_ENDF            /*!< FMC end of programming flag */

/* FMC interrupt enable */
#define FMC_INT_END                FMC_CTL_ENDIE            /*!< enable FMC end of operation interrupt */
#define FMC_INT_ERR                FMC_CTL_ERRIE            /*!< enable FMC error interrupt */

/* FMC interrupt flags */
#define FMC_INT_FLAG_PGERR         FMC_STAT_PGERR           /*!< FMC programming error interrupt flag */
#define FMC_INT_FLAG_WPERR         FMC_STAT_WPERR           /*!< FMC write protection error interrupt flag */
#define FMC_INT_FLAG_END           FMC_STAT_ENDF            /*!< FMC end of programming interrupt flag */

/* option bytes write protection */
#define OB_WP_NONE                 ((uint16_t)0x0000U)      /*!< disable all erase/program protection */
#define OB_WP_0                    ((uint16_t)0x0001U)      /*!< erase/program protection of sector 0 */
#define OB_WP_1                    ((uint16_t)0x0002U)      /*!< erase/program protection of sector 1 */
#define OB_WP_2                    ((uint16_t)0x0004U)      /*!< erase/program protection of sector 2 */
#define OB_WP_3                    ((uint16_t)0x0008U)      /*!< erase/program protection of sector 3 */
#define OB_WP_4                    ((uint16_t)0x0010U)      /*!< erase/program protection of sector 4 */
#define OB_WP_5                    ((uint16_t)0x0020U)      /*!< erase/program protection of sector 5 */
#define OB_WP_6                    ((uint16_t)0x0040U)      /*!< erase/program protection of sector 6 */
#define OB_WP_7                    ((uint16_t)0x0080U)      /*!< erase/program protection of sector 7 */
#define OB_WP_8                    ((uint16_t)0x0100U)      /*!< erase/program protection of sector 8 */
#define OB_WP_9                    ((uint16_t)0x0200U)      /*!< erase/program protection of sector 9 */
#define OB_WP_10                   ((uint16_t)0x0400U)      /*!< erase/program protection of sector 10 */
#define OB_WP_11                   ((uint16_t)0x0800U)      /*!< erase/program protection of sector 11 */
#define OB_WP_12                   ((uint16_t)0x1000U)      /*!< erase/program protection of sector 12 */
#define OB_WP_13                   ((uint16_t)0x2000U)      /*!< erase/program protection of sector 13 */
#define OB_WP_14                   ((uint16_t)0x4000U)      /*!< erase/program protection of sector 14 */
#define OB_WP_15                   ((uint16_t)0x8000U)      /*!< erase/program protection of sector 15 */
#define OB_WP_ALL                  ((uint16_t)0xFFFFU)      /*!< erase/program protection of all sectors */

/* FMC time out */
#define FMC_TIMEOUT_COUNT          ((uint32_t)0x000F0000U)  /*!< count to judge of FMC timeout */

/* function declarations */
/* FMC main memory programming functions */
/* unlock the main FMC operation */
void fmc_unlock(void);
/* lock the main FMC operation */
void fmc_lock(void);
/* set the wait state counter value */
void fmc_wscnt_set(uint8_t wscnt);
/* fmc wait state enable */
void fmc_wait_state_enable(void);
/* fmc wait state disable */
void fmc_wait_state_disable(void);
/* FMC erase page */
fmc_state_enum fmc_page_erase(uint32_t page_address);
/* FMC erase whole chip */
fmc_state_enum fmc_mass_erase(void);
/* FMC program a word at the corresponding address */
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data);
/* FMC program a half word at the corresponding address */
fmc_state_enum fmc_halfword_program(uint32_t address, uint16_t data);

/* FMC option bytes programming functions */
/* unlock the option byte operation */
void ob_unlock(void);
/* lock the option byte operation */
void ob_lock(void);
/* reload the option byte and generate a system reset */
void ob_reset(void);
/* erase option byte */
fmc_state_enum ob_erase(void);
/* enable option byte write protection (OB_WP) */
fmc_state_enum ob_write_protection_enable(uint16_t ob_wp);
/* configure read out protect */
fmc_state_enum ob_security_protection_config(uint8_t ob_spc);
/* write the FMC option byte user */
fmc_state_enum ob_user_write(uint8_t ob_user);
/* write the FMC option byte data */
fmc_state_enum ob_data_program(uint16_t ob_data);
/* get the FMC option byte OB_USER */
uint8_t ob_user_get(void);
/* get the FMC option byte OB_DATA */
uint16_t ob_data_get(void);
/* get the FMC option byte write protection (OB_WP) in register FMC_WP */
uint16_t ob_write_protection_get(void);
/* get the value of FMC option byte security protection level (PLEVEL) in FMC_OBSTAT register */
uint32_t ob_obstat_plevel_get(void);

/* FMC interrupts and flags management functions */
/* get FMC flag state */
FlagStatus fmc_flag_get(uint32_t flag);
/* clear the FMC pending flag */
void fmc_flag_clear(uint32_t flag);
/* enable FMC interrupt */
void fmc_interrupt_enable(uint32_t interrupt);
/* disable FMC interrupt */
void fmc_interrupt_disable(uint32_t interrupt);
/* get FMC interrupt flag state */
FlagStatus fmc_interrupt_flag_get(uint32_t flag);
/* clear the FMC pending interrupt flag */
void fmc_interrupt_flag_clear(uint32_t flag);

#endif /* GD32F1X0_FMC_H */
