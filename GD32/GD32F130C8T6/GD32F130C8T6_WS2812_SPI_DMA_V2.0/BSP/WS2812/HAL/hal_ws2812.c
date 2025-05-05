/* hal_ws2812.c */
#include "hal_ws2812.h"
#include "ll_ws2812.h"

WS2812_Status HAL_WS2812_Init(void)
{
    LL_WS2812_GPIO_Init();
    LL_WS2812_TIMER_DMA_Init();
    return WS2812_OK;
}

WS2812_Status HAL_WS2812_SendFrame(WS2812_Buffer *buffer)
{
    if (LL_WS2812_IsDMABusy())
        return WS2812_ERR_DMA_BUSY;

    LL_WS2812_StartTransfer(&buffer->buffer[0][0], WS2812_LED_NUM * WS2812_BITS_PER_LED + WS2812_RESET_FRAMES * WS2812_BITS_PER_LED);

    return WS2812_OK;
}

uint8_t HAL_WS2812_IsBusy(void) { return LL_WS2812_IsDMABusy(); }