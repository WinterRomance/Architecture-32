#include "ll_ws2812.h"
#include "gd32f1x0.h"

// 定义全局变量
volatile uint8_t dma_busy = 0;

void LL_WS2812_GPIO_Init(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
    gpio_af_set(GPIOB, GPIO_AF_2, GPIO_PIN_10);
}

void LL_WS2812_TIMER_DMA_Init(void)
{
    timer_parameter_struct timerpara;
    timer_oc_parameter_struct ocpara;

    rcu_periph_clock_enable(RCU_TIMER1);
    timer_deinit(TIMER1);

    /* 基本定时器：72MHz，ARR=89 => 1.25us 周期 */
    timerpara.prescaler = TIMER_PSC1;
    timerpara.alignedmode = TIMER_COUNTER_EDGE;
    timerpara.counterdirection = TIMER_COUNTER_UP;
    timerpara.period = TIMER_ARR1;
    timerpara.clockdivision = TIMER_CKDIV_DIV1;
    timerpara.repetitioncounter = 0;
    timer_init(TIMER1, &timerpara);

    /* CH2 PWM 输出比较配置 */
    ocpara.outputstate = TIMER_CCX_ENABLE;
    ocpara.outputnstate = TIMER_CCXN_DISABLE;
    ocpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
    ocpara.ocnpolarity = TIMER_OCN_POLARITY_HIGH;
    ocpara.ocidlestate = TIMER_OC_IDLE_STATE_HIGH;
    ocpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    timer_channel_output_config(TIMER1, TIMER_CH_2, &ocpara);

    /* 设置 PWM 模式0 */
    timer_channel_output_mode_config(TIMER1, TIMER_CH_2, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER1, TIMER_CH_2, TIMER_OC_SHADOW_DISABLE);

    /* 初始比较值为低电平 */
    timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_2, WS2812_LOW_CCR);

    /* 启用输出状态（重要） */
    timer_channel_output_state_config(TIMER1, TIMER_CH_2, ENABLE);

    /* 启用主输出 */
    timer_primary_output_config(TIMER1, ENABLE);
    timer_channel_dma_request_source_select(TIMER1, TIMER_DMAREQUEST_UPDATEEVENT);

    /* 启用 DMA：使用 CH2 比较事件触发 */
    timer_dma_enable(TIMER1, TIMER_DMA_UPD); // ← 关键修改点！

    /* 允许预装载寄存器更新 */
    timer_auto_reload_shadow_enable(TIMER1);
}

void LL_WS2812_StartTransfer(uint32_t *buffer, uint32_t length)
{
    // 关 DMA、配置长度、开 DMA、开定时器
    dma_channel_disable(DMA_CH1);
    dma_transfer_number_config(DMA_CH1, length);
    dma_channel_enable(DMA_CH1);
    timer_enable(TIMER1);
}

uint8_t LL_WS2812_IsDMABusy(void) { return dma_busy; }
