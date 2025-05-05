/* hal_ws2812.h - 硬件抽象层 */
#ifndef HAL_WS2812_H
#define HAL_WS2812_H

#include "ws2812_common.h" // 只依赖公共类型
#include <stdint.h>

// 前向声明避免包含驱动层头文件
#define WS2812_LED_NUM 30
#define WS2812_BITS_PER_LED 24
#define WS2812_RESET_FRAMES 3

typedef struct
{
        uint32_t buffer[WS2812_LED_NUM + WS2812_RESET_FRAMES][WS2812_BITS_PER_LED];
} WS2812_Buffer;

// HAL接口
WS2812_Status HAL_WS2812_Init(void);
WS2812_Status HAL_WS2812_SendFrame(WS2812_Buffer *buffer);
uint8_t HAL_WS2812_IsBusy(void);

#endif