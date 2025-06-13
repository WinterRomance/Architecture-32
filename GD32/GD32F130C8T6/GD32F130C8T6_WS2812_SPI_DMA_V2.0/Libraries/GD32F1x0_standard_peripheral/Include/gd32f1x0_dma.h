/*!
    \file    gd32f1x0_dma.h
    \brief   definitions for the DMA

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

#ifndef GD32F1X0_DMA_H
#define GD32F1X0_DMA_H

#include "gd32f1x0.h"

/* DMA definitions */
#define DMA                               DMA_BASE                     /*!< DMA base address */

/* registers definitions */
#define DMA_INTF                          REG32(DMA + 0x00000000U)     /*!< DMA interrupt flag register */
#define DMA_INTC                          REG32(DMA + 0x00000004U)     /*!< DMA interrupt flag clear register */

#define DMA_CH0CTL                        REG32(DMA + 0x00000008U)     /*!< DMA channel 0 control register */
#define DMA_CH0CNT                        REG32(DMA + 0x0000000CU)     /*!< DMA channel 0 counter register */
#define DMA_CH0PADDR                      REG32(DMA + 0x00000010U)     /*!< DMA channel 0 peripheral base address register */
#define DMA_CH0MADDR                      REG32(DMA + 0x00000014U)     /*!< DMA channel 0 memory base address register */

#define DMA_CH1CTL                        REG32(DMA + 0x0000001CU)     /*!< DMA channel 1 control register */
#define DMA_CH1CNT                        REG32(DMA + 0x00000020U)     /*!< DMA channel 1 counter register */
#define DMA_CH1PADDR                      REG32(DMA + 0x00000024U)     /*!< DMA channel 1 peripheral base address register */
#define DMA_CH1MADDR                      REG32(DMA + 0x00000028U)     /*!< DMA channel 1 memory base address register */

#define DMA_CH2CTL                        REG32(DMA + 0x00000030U)     /*!< DMA channel 2 control register */
#define DMA_CH2CNT                        REG32(DMA + 0x00000034U)     /*!< DMA channel 2 counter register */
#define DMA_CH2PADDR                      REG32(DMA + 0x00000038U)     /*!< DMA channel 2 peripheral base address register */
#define DMA_CH2MADDR                      REG32(DMA + 0x0000003CU)     /*!< DMA channel 2 memory base address register */

#define DMA_CH3CTL                        REG32(DMA + 0x00000044U)     /*!< DMA channel 3 control register */
#define DMA_CH3CNT                        REG32(DMA + 0x00000048U)     /*!< DMA channel 3 counter register */
#define DMA_CH3PADDR                      REG32(DMA + 0x0000004CU)     /*!< DMA channel 3 peripheral base address register */
#define DMA_CH3MADDR                      REG32(DMA + 0x00000050U)     /*!< DMA channel 3 memory base address register */

#define DMA_CH4CTL                        REG32(DMA + 0x00000058U)     /*!< DMA channel 4 control register */
#define DMA_CH4CNT                        REG32(DMA + 0x0000005CU)     /*!< DMA channel 4 counter register */
#define DMA_CH4PADDR                      REG32(DMA + 0x00000060U)     /*!< DMA channel 4 peripheral base address register */
#define DMA_CH4MADDR                      REG32(DMA + 0x00000064U)     /*!< DMA channel 4 memory base address register */

#define DMA_CH5CTL                        REG32(DMA + 0x0000006CU)     /*!< DMA channel 5 control register */
#define DMA_CH5CNT                        REG32(DMA + 0x00000070U)     /*!< DMA channel 5 counter register */
#define DMA_CH5PADDR                      REG32(DMA + 0x00000074U)     /*!< DMA channel 5 peripheral base address register */
#define DMA_CH5MADDR                      REG32(DMA + 0x00000078U)     /*!< DMA channel 5 memory base address register */

#define DMA_CH6CTL                        REG32(DMA + 0x00000080U)     /*!< DMA channel 6 control register */
#define DMA_CH6CNT                        REG32(DMA + 0x00000084U)     /*!< DMA channel 6 counter register */
#define DMA_CH6PADDR                      REG32(DMA + 0x00000088U)     /*!< DMA channel 6 peripheral base address register */
#define DMA_CH6MADDR                      REG32(DMA + 0x0000008CU)     /*!< DMA channel 6 memory base address register */

/* bits definitions */
/* DMA_INTF */
#define DMA_INTF_GIF                      BIT(0)                 /*!< global interrupt flag of channel */
#define DMA_INTF_FTFIF                    BIT(1)                 /*!< transfer complete flag of channel */
#define DMA_INTF_HTFIF                    BIT(2)                 /*!< half transfer complete flag of channel */
#define DMA_INTF_ERRIF                    BIT(3)                 /*!< error flag of channel */

/* DMA_INTC */
#define DMA_INTFC_GIFC                    BIT(0)                 /*!< clear global interrupt flag of channel */
#define DMA_INTFC_FTFIFC                  BIT(1)                 /*!< clear transfer complete flag of channel */
#define DMA_INTFC_HTFIFC                  BIT(2)                 /*!< clear half transfer complete flag of channel */
#define DMA_INTFC_ERRIFC                  BIT(3)                 /*!< clear error flag of channel */

/* DMA_CHxCTL,x=0..6 */
#define DMA_CHXCTL_CHEN                   BIT(0)                 /*!< channel x enable */
#define DMA_CHXCTL_FTFIE                  BIT(1)                 /*!< enable bit for channel x transfer complete interrupt */
#define DMA_CHXCTL_HTFIE                  BIT(2)                 /*!< enable bit for channel x transfer half complete interrupt */
#define DMA_CHXCTL_ERRIE                  BIT(3)                 /*!< enable bit for channel x error interrupt */
#define DMA_CHXCTL_DIR                    BIT(4)                 /*!< transfer direction */
#define DMA_CHXCTL_CMEN                   BIT(5)                 /*!< circulation mode */
#define DMA_CHXCTL_PNAGA                  BIT(6)                 /*!< next address generation algorithm of peripheral */
#define DMA_CHXCTL_MNAGA                  BIT(7)                 /*!< next address generation algorithm of memory */
#define DMA_CHXCTL_PWIDTH                 BITS(8,9)              /*!< transfer data size of peripheral */
#define DMA_CHXCTL_MWIDTH                 BITS(10,11)            /*!< transfer data size of memory */
#define DMA_CHXCTL_PRIO                   BITS(12,13)            /*!< priority level of channelx */
#define DMA_CHXCTL_M2M                    BIT(14)                /*!< memory to memory mode */

/* DMA_CHxCNT, x=0..6 */
#define DMA_CHXCNT_CNT                    BITS(0,15)             /*!< transfer counter */

/* DMA_CHxPADDR, x=0..6 */
#define DMA_CHXPADDR_PADDR                BITS(0,31)             /*!< peripheral base address */

/* DMA_CHxMADDR, x=0..6 */
#define DMA_CHXMADDR_MADDR                BITS(0,31)             /*!< memory base address */

/* constants definitions */
/* DMA channel select */
typedef enum 
{
    DMA_CH0 = 0,            /*!< DMA Channel0 */
    DMA_CH1,                /*!< DMA Channel1 */ 
    DMA_CH2,                /*!< DMA Channel2 */ 
    DMA_CH3,                /*!< DMA Channel3 */ 
    DMA_CH4,                /*!< DMA Channel4 */ 
    DMA_CH5,                /*!< DMA Channel5 */ 
    DMA_CH6                 /*!< DMA Channel6 */
} dma_channel_enum;

/* DMA initialize struct */
typedef struct
{
    uint32_t periph_addr;   /*!< peripheral base address */
    uint32_t periph_width;  /*!< transfer data size of peripheral */
    uint8_t periph_inc;    /*!< peripheral increasing mode */
    uint32_t memory_addr;   /*!< memory base address */
    uint32_t memory_width;  /*!< transfer data size of memory */
    uint8_t memory_inc;    /*!< memory increasing mode */
    uint8_t direction;     /*!< channel data transfer direction */
    uint32_t number;        /*!< channel transfer number */
    uint32_t priority;      /*!< channel priority level */
} dma_parameter_struct;

/* DMA reset value */
#define DMA_CHCTL_RESET_VALUE             ((uint32_t)0x00000000U)                          /*!< the reset value of DMA channel CHXCTL register  */
#define DMA_CHCNT_RESET_VALUE             ((uint32_t)0x00000000U)                          /*!< the reset value of DMA channel CHXCNT register  */
#define DMA_CHPADDR_RESET_VALUE           ((uint32_t)0x00000000U)                          /*!< the reset value of DMA channel CHXPADDR register  */
#define DMA_CHMADDR_RESET_VALUE           ((uint32_t)0x00000000U)                          /*!< the reset value of DMA channel CHXMADDR register  */
#define DMA_CHINTF_RESET_VALUE            (DMA_INTF_GIF | DMA_INTF_FTFIF | \
                                           DMA_INTF_HTFIF | DMA_INTF_ERRIF)                /*!< clear DMA channel CHXINTFS register  */

#define DMA_FLAG_ADD(flag,shift)          ((uint32_t)(flag) << ((uint32_t)(shift) * 4U))   /*!< DMA channel flag shift */

/* DMA_CHCTL base address */
#define DMA_CHXCTL_BASE                   (DMA + 0x00000008U)                              /*!< the base address of DMA channel CHXCTL register */
#define DMA_CHXCNT_BASE                   (DMA + 0x0000000CU)                              /*!< the base address of DMA channel CHXCNT register */
#define DMA_CHXPADDR_BASE                 (DMA + 0x00000010U)                              /*!< the base address of DMA channel CHXPADDR register */
#define DMA_CHXMADDR_BASE                 (DMA + 0x00000014U)                              /*!< the base address of DMA channel CHXMADDR register */

/* DMA channel shift bit */
#define DMA_CHCTL(channel)                REG32(DMA_CHXCTL_BASE + (uint32_t)0x00000014U * (uint32_t)(channel))     /*!< the address of DMA channel CHXCTL register  */
#define DMA_CHCNT(channel)                REG32(DMA_CHXCNT_BASE + (uint32_t)0x00000014U * (uint32_t)(channel))     /*!< the address of DMA channel CHXCNT register */
#define DMA_CHPADDR(channel)              REG32(DMA_CHXPADDR_BASE + (uint32_t)0x00000014U * (uint32_t)(channel))   /*!< the address of DMA channel CHXPADDR register */
#define DMA_CHMADDR(channel)              REG32(DMA_CHXMADDR_BASE + (uint32_t)0x00000014U * (uint32_t)(channel))   /*!< the address of DMA channel CHXMADDR register */

/* flag bits */
#define DMA_FLAG_G                        DMA_INTF_GIF           /*!< global interrupt flag of channel */
#define DMA_FLAG_FTF                      DMA_INTF_FTFIF         /*!< full transfer finish flag of channel */
#define DMA_FLAG_HTF                      DMA_INTF_HTFIF         /*!< half transfer finish flag of channel */
#define DMA_FLAG_ERR                      DMA_INTF_ERRIF         /*!< error flag of channel */

/* interrupt enable bits */
#define DMA_INT_FTF                       DMA_CHXCTL_FTFIE       /*!< enable bit for channel full transfer finish interrupt */
#define DMA_INT_HTF                       DMA_CHXCTL_HTFIE       /*!< enable bit for channel half transfer finish interrupt */
#define DMA_INT_ERR                       DMA_CHXCTL_ERRIE       /*!< enable bit for channel error interrupt */

/* interrupt flag bits */
#define DMA_INT_FLAG_G                    DMA_INTF_GIF           /*!< global interrupt flag of channel */
#define DMA_INT_FLAG_FTF                  DMA_INTF_FTFIF         /*!< full transfer finish interrupt flag of channel */
#define DMA_INT_FLAG_HTF                  DMA_INTF_HTFIF         /*!< half transfer finish interrupt flag of channel */
#define DMA_INT_FLAG_ERR                  DMA_INTF_ERRIF         /*!< error interrupt flag of channel */

/* channel data transfer direction */
#define DMA_PERIPHERAL_TO_MEMORY          ((uint8_t)0x00U)                      /*!< read from peripheral and write to memory */
#define DMA_MEMORY_TO_PERIPHERAL          ((uint8_t)0x01U)                      /*!< read from memory and write to peripheral */

/* peripheral increasing mode */
#define DMA_PERIPH_INCREASE_DISABLE       ((uint8_t)0x00U)                      /*!< next address of peripheral is fixed address mode */
#define DMA_PERIPH_INCREASE_ENABLE        ((uint8_t)0x01U)                      /*!< next address of peripheral is increasing address mode */

/* memory increasing mode */
#define DMA_MEMORY_INCREASE_DISABLE       ((uint8_t)0x00U)                      /*!< next address of memory is fixed address mode */
#define DMA_MEMORY_INCREASE_ENABLE        ((uint8_t)0x01U)                      /*!< next address of memory is increasing address mode */

/* transfer data size of peripheral */
#define CHCTL_PWIDTH(regval)              (BITS(8,9) & ((regval) << 8U))               /*!< transfer data size of peripheral */
#define DMA_PERIPHERAL_WIDTH_8BIT         CHCTL_PWIDTH(0U)                              /*!< transfer data size of peripheral is 8-bit */
#define DMA_PERIPHERAL_WIDTH_16BIT        CHCTL_PWIDTH(1U)                              /*!< transfer data size of peripheral is 16-bit */
#define DMA_PERIPHERAL_WIDTH_32BIT        CHCTL_PWIDTH(2U)                              /*!< transfer data size of peripheral is 32-bit */

/* transfer data size of memory */
#define CHCTL_MWIDTH(regval)              (BITS(10,11) & ((regval) << 10U))            /*!< transfer data size of memory */
#define DMA_MEMORY_WIDTH_8BIT             CHCTL_MWIDTH(0U)                              /*!< transfer data size of memory is 8-bit */
#define DMA_MEMORY_WIDTH_16BIT            CHCTL_MWIDTH(1U)                              /*!< transfer data size of memory is 16-bit */
#define DMA_MEMORY_WIDTH_32BIT            CHCTL_MWIDTH(2U)                              /*!< transfer data size of memory is 32-bit */

/* channel priority level */
#define CHCTL_PRIO(regval)                (BITS(12,13) & ((uint32_t)(regval) << 12U))  /*!< DMA channel priority level */
#define DMA_PRIORITY_LOW                  CHCTL_PRIO(0U)                                /*!< low priority */
#define DMA_PRIORITY_MEDIUM               CHCTL_PRIO(1U)                                /*!< medium priority */
#define DMA_PRIORITY_HIGH                 CHCTL_PRIO(2U)                                /*!< high priority */
#define DMA_PRIORITY_ULTRA_HIGH           CHCTL_PRIO(3U)                                /*!< ultra high priority */

/* transfer counter */
#define DMA_CHANNEL_CNT_MASK              DMA_CHXCNT_CNT

/* function declarations */
/* DMA initialization functions */
/* deinitialize DMA a channel registers */
void dma_deinit(dma_channel_enum channelx);
/* initialize the parameters of DMA struct with the default values */
void dma_struct_para_init(dma_parameter_struct* init_struct);
/* initialize DMA channel */
void dma_init(dma_channel_enum channelx, dma_parameter_struct* init_struct);
/* enable DMA circulation mode */
void dma_circulation_enable(dma_channel_enum channelx);
/* disable DMA circulation mode */
void dma_circulation_disable(dma_channel_enum channelx);
/* enable memory to memory mode */
void dma_memory_to_memory_enable(dma_channel_enum channelx);
/* disable memory to memory mode */
void dma_memory_to_memory_disable(dma_channel_enum channelx);
/* enable DMA channel */
void dma_channel_enable(dma_channel_enum channelx);
/* disable DMA channel */
void dma_channel_disable(dma_channel_enum channelx);

/* DMA configuration functions */
/* set DMA peripheral base address */
void dma_periph_address_config(dma_channel_enum channelx, uint32_t address);
/* set DMA memory base address */
void dma_memory_address_config(dma_channel_enum channelx, uint32_t address);
/* set the number of remaining data to be transferred by the DMA */
void dma_transfer_number_config(dma_channel_enum channelx, uint32_t number);
/* get the number of remaining data to be transferred by the DMA */
uint32_t dma_transfer_number_get(dma_channel_enum channelx);
/* configure priority level of DMA channel */
void dma_priority_config(dma_channel_enum channelx, uint32_t priority);
/* configure transfer data size of memory */
void dma_memory_width_config (dma_channel_enum channelx, uint32_t mwidth);
/* configure transfer data size of peripheral */
void dma_periph_width_config (dma_channel_enum channelx, uint32_t pwidth);
/* enable next address increasement algorithm of memory */
void dma_memory_increase_enable(dma_channel_enum channelx);
/* disable next address increasement algorithm of memory */
void dma_memory_increase_disable(dma_channel_enum channelx);
/* enable next address increasement algorithm of peripheral */
void dma_periph_increase_enable(dma_channel_enum channelx);
/* disable next address increasement algorithm of peripheral */
void dma_periph_increase_disable(dma_channel_enum channelx);
/* configure the direction of data transfer on the channel */
void dma_transfer_direction_config(dma_channel_enum channelx, uint8_t direction);

/* DMA interrupt and flag functions */
/* check DMA flag is set or not */
FlagStatus dma_flag_get(dma_channel_enum channelx, uint32_t flag);
/* clear DMA a channel flag */
void dma_flag_clear(dma_channel_enum channelx, uint32_t flag);
/* enable DMA interrupt */
void dma_interrupt_enable(dma_channel_enum channelx, uint32_t source);
/* disable DMA interrupt */
void dma_interrupt_disable(dma_channel_enum channelx,uint32_t source);
/* check DMA flag is set or not */
FlagStatus dma_interrupt_flag_get(dma_channel_enum channelx, uint32_t flag);
/* clear DMA a channel flag */
void dma_interrupt_flag_clear(dma_channel_enum channelx, uint32_t flag);

#endif /* GD32F1X0_DMA_H */
