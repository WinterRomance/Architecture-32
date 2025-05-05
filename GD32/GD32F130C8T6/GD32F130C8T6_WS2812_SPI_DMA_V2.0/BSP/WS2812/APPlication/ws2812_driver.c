/* ws2812_driver.c */
#include "ws2812_driver.h"
#include "hal_ws2812.h"
#include "systick.h"

static WS2812_Buffer led_buffer;

WS2812_Status WS2812_Update(void) { return HAL_WS2812_SendFrame(&led_buffer); }

WS2812_Status WS2812_SetColor(uint16_t idx, WS2812_Color col, uint8_t bri)
{
    if (idx >= WS2812_LED_NUM)
        return WS2812_ERR_INVALID_PARAM;

    uint32_t g = col.green * bri / 100;
    uint32_t r = col.red * bri / 100;
    uint32_t b = col.blue * bri / 100;
    uint32_t pkt = (g << 16) | (r << 8) | b;

    for (int bit = 0; bit < WS2812_BITS_PER_LED; bit++)
    {
        led_buffer.buffer[idx][bit] = (pkt & (1U << (23 - bit))) ? WS2812_HIGH_CCR : WS2812_LOW_CCR;
    }
    return WS2812_OK;
}

WS2812_Status WS2812_LIUSHUI(void)
{
    static uint16_t pos = 0, color_i = 0;
    const uint8_t C = sizeof(colors) / sizeof(colors[0]);
    for (int i = 0; i < WS2812_LED_NUM; i++)
    {
        WS2812_SetColor(i, (i == pos) ? colors[color_i] : (WS2812_Color){0, 0, 0}, (i == pos) ? 100 : 0);
    }
    WS2812_Update();
    pos = (pos + 1) % WS2812_LED_NUM;
    if (pos == 0)
        color_i = (color_i + 1) % C;
    delay_1ms(50);
    return WS2812_OK;
}