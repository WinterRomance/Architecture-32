#include "gd32f1x0.h"
#include "gd32f1x0_libopt.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "timer.h"
#include "led.h"
#include "ws2812_driver.h"
#include "usart.h"

int main(void)
{
    systick_config();
    led_gpio_init();
    uart_init(115200);
    WS2812_Init();
    while (1)
    {
        WS2812_LIUSHUI();
        led_toggle();
        delay_1ms(5000);
    }
}
