/* ws2812_common.h - 公共基础头文件 */
#ifndef WS2812_COMMON_H
#define WS2812_COMMON_H

#include <stdio.h>
#include "gd32f1x0.h"

typedef enum {
    WS2812_OK,
    WS2812_ERR_DMA_BUSY,
    WS2812_ERR_INVALID_PARAM
} WS2812_Status;  // 状态码定义

#define WS2812_LED_NUM 30
#define WS2812_RESET_FRAMES 3
#define WS2812_BITS_PER_LED 24
#define RGB_ARRAY_SIZE (WS2812_LED_NUM + WS2812_RESET_FRAMES)
#define WS2812_HIGH_CCR 57
#define WS2812_LOW_CCR 28
// 颜色格式定义
typedef struct
{
    uint8_t green;
    uint8_t red;
    uint8_t blue;
} WS2812_Color;

// 七种颜色（正常 RGB 顺序）
static const WS2812_Color colors[] = {
    {255, 0, 0},    // 红
    {255, 255, 0},  // 黄
    {0, 255, 0},    // 绿
    {0, 255, 255},  // 青
    {0, 0, 255},    // 蓝
    {255, 0, 255},  // 紫
    {255, 255, 255} // 白
};

#endif