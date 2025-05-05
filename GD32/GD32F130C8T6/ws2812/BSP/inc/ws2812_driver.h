#ifndef __WS2812_DRIVER_H__
#define __WS2812_DRIVER_H__

#include "gd32f1x0.h"
#include <stdint.h>
#include "gd32f1x0.h"
#include <string.h>
#include "usart.h"
#include "systick.h"
#include "led.h"

// 灯带参数配置
#define WS2812_LED_NUM 30                                     // 灯珠数量
#define WS2812_RESET_FRAMES 3                                 // 复位帧数量
#define WS2812_BITS_PER_LED 24                                // 每个灯珠数据位数
#define RGB_ARRAY_SIZE (WS2812_LED_NUM + WS2812_RESET_FRAMES) // 多 3 灯位用于复位帧
#define WS2812_HIGH_CCR 57
#define WS2812_LOW_CCR 28
#define TIMER_PSC1 0
#define TIMER_ARR1 89

// 颜色格式定义
typedef struct
{
        uint8_t green;
        uint8_t red;
        uint8_t blue;
} WS2812_Color;

// 驱动状态枚举
typedef enum
{
    WS2812_OK,
    WS2812_ERR_DMA_BUSY,
    WS2812_ERR_INVALID_PARAM
} WS2812_Status;

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

void WS2812_Init(void);
// void WS2812_DebugPrintBuffer(void);
WS2812_Status WS2812_ALL_COLOR_CYCLE(uint16_t delay_ms);
WS2812_Status WS2812_LIUSHUI(void);
WS2812_Status WS2812_SetColor(uint16_t index, WS2812_Color color, uint8_t brightness);
WS2812_Status WS2812_Update(void);
#endif
