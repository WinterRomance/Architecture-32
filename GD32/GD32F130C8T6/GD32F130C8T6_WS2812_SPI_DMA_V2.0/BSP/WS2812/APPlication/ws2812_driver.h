/* ws2812_driver.h - 应用驱动层 */
#ifndef WS2812_DRIVER_H
#define WS2812_DRIVER_H

#include "ws2812_common.h" // 公共类型
#include <stdint.h>

// 应用层接口
WS2812_Status WS2812_SetColor(uint16_t idx, WS2812_Color col, uint8_t bri);
WS2812_Status WS2812_Update(void);
WS2812_Status WS2812_LIUSHUI(void);

#endif