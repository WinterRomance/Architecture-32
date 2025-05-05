#include "gd32f1x0.h"
#include "led.h"

void led_gpio_init(void)
{
    // 启用 GPIOB 的外设时钟
    rcu_periph_clock_enable(RCU_GPIOB);

    // 设置 PB12 为推挽输出模式，无上下拉
    gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_12);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
}

void led_on(void)
{
    // 设置 PB12 为高电平点亮 LED
    gpio_bit_set(GPIOB, GPIO_PIN_12);
}

void led_off(void)
{
    // 设置 PB12 为低电平熄灭 LED
    gpio_bit_reset(GPIOB, GPIO_PIN_12);
}

void led_toggle(void)
{
    // 直接反转 PB12 的输出状态
    gpio_bit_write(GPIOB, GPIO_PIN_12, (gpio_input_bit_get(GPIOB, GPIO_PIN_12) == RESET) ? SET : RESET);
}
