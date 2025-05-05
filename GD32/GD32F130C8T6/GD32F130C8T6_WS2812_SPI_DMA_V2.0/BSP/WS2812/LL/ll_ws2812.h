/* ll_ws2812.h - 底层驱动 */
#ifndef LL_WS2812_H
#define LL_WS2812_H

#include <stdint.h>

// 硬件相关定义
#define TIMER_PSC1 0
#define TIMER_ARR1 89
#define WS2812_HIGH_CCR 57
#define WS2812_LOW_CCR 28

// 声明全局变量为 extern
extern volatile uint8_t dma_busy;

void LL_WS2812_GPIO_Init(void);
void LL_WS2812_TIMER_DMA_Init(void);
void LL_WS2812_StartTransfer(uint32_t *buffer, uint32_t length);
uint8_t LL_WS2812_IsDMABusy(void);

#endif