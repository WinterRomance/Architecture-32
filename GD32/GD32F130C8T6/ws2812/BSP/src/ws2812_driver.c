#include "ws2812_driver.h"

volatile uint8_t dma_busy = 0;
// 数据缓冲区（兼容DMA访问要求）
static __attribute__((aligned(4))) uint32_t led_buffer[RGB_ARRAY_SIZE][WS2812_BITS_PER_LED];
static uint32_t reset_frame[WS2812_RESET_FRAMES][WS2812_BITS_PER_LED];

// 硬件抽象层函数声明
static void HAL_GPIO_Init(void);
static void HAL_TIMER_Init(void);
static void HAL_DMA_Init(void);

void WS2812_Init(void)
{
    memset(led_buffer, 0, sizeof(led_buffer));
    memset(reset_frame, 0, sizeof(reset_frame));

    HAL_GPIO_Init();
    HAL_TIMER_Init();
    HAL_DMA_Init();
}

WS2812_Status WS2812_SetColor(uint16_t index, WS2812_Color color, uint8_t brightness)
{
    if (index >= WS2812_LED_NUM)
        return WS2812_ERR_INVALID_PARAM;

    // 亮度调整（定点数运算优化）
    uint32_t g = (color.green * brightness) / 100;
    uint32_t r = (color.red * brightness) / 100;
    uint32_t b = (color.blue * brightness) / 100;

    // 生成PWM占空比序列
    uint32_t color_packet = (g << 16) | (r << 8) | b;
    for (uint8_t bit = 0; bit < WS2812_BITS_PER_LED; bit++)
    {
        led_buffer[index][bit] = (color_packet & (1UL << 23)) ? WS2812_HIGH_CCR : WS2812_LOW_CCR;
        color_packet <<= 1;
    }
    return WS2812_OK;
}

WS2812_Status WS2812_LIUSHUI(void)
{
    static uint8_t pos = 0;         // 当前要点亮的像素
    static uint8_t color_index = 0; // 当前颜色在表里的索引
    // 七种颜色（正常 RGB 顺序）
    const WS2812_Color colors[] = {
        {255, 0, 0},    // 红
        {255, 255, 0},  // 黄
        {0, 255, 0},    // 绿
        {0, 255, 255},  // 青
        {0, 0, 255},    // 蓝
        {255, 0, 255},  // 紫
        {255, 255, 255} // 白
    };
    const uint8_t N = WS2812_LED_NUM;
    const uint8_t C = sizeof(colors) / sizeof(colors[0]);

    // —— 重建整条链 ——
    for (uint16_t i = 0; i < N; i++)
    {
        if (i == pos)
        {
            // 当前位置：亮当前颜色，100% 亮度
            WS2812_SetColor(i, colors[color_index], 100);
        }
        else
        {
            // 其它位置：灭灯（brightness = 0 会让 SetColor 全部填 低电平）
            WS2812_SetColor(i, (WS2812_Color){0, 0, 0}, 0);
        }
    }
    // 调试打印（修正数据类型）
    debug_print_matrix((uint32_t *)led_buffer, RGB_ARRAY_SIZE, WS2812_BITS_PER_LED);
    // —— 一次性发完整帧 ——
    WS2812_Update();

    // —— 更新索引 ——
    pos = (pos + 1) % N;
    if (pos == 0)
    {
        color_index = (color_index + 1) % C;
    }

    delay_1ms(300); // 调整速度
    return WS2812_OK;
}

WS2812_Status WS2812_Update(void)
{
    if (dma_busy)
        return WS2812_ERR_DMA_BUSY;

    // 禁用旧传输
    dma_channel_disable(DMA_CH1);

    // 配置传输数据量（LED数据 + 复位帧）
    uint32_t data_size = RGB_ARRAY_SIZE * WS2812_BITS_PER_LED;
    dma_transfer_number_config(DMA_CH1, data_size);

    // 启用DMA通道
    dma_channel_enable(DMA_CH1);

    // 启动定时器
    timer_enable(TIMER1);

    dma_busy = 1;
    return WS2812_OK;
}

/* ------------------------- 硬件抽象层实现 ------------------------- */

static void HAL_GPIO_Init(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
    gpio_af_set(GPIOB, GPIO_AF_2, GPIO_PIN_10);
}

static void HAL_TIMER_Init(void)
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

static void HAL_DMA_Init(void)
{
    dma_parameter_struct dma_init_struct;

    rcu_periph_clock_enable(RCU_DMA);
    dma_deinit(DMA_CH1);

    /* 配置 DMA 从内存到 CCR2 寄存器 */
    dma_init_struct.periph_addr = (uint32_t)(&TIMER_CH2CV(TIMER1)); // CCR2 地址
    dma_init_struct.memory_addr = (uint32_t)led_buffer;             // 数据源地址
    dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;
    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_32BIT;
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_32BIT;
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.number = RGB_ARRAY_SIZE * WS2812_BITS_PER_LED;
    dma_init_struct.priority = DMA_PRIORITY_HIGH;
    dma_init(DMA_CH1, &dma_init_struct);

    dma_circulation_disable(DMA_CH1);
    dma_memory_to_memory_disable(DMA_CH1);

    // 可选中断，用于确认传输完成
    dma_interrupt_enable(DMA_CH1, DMA_INT_FTF);
    //MARK:DMA_CH1对应的中断是DMA_Channel1_2_IRQn
    nvic_irq_enable(DMA_Channel1_2_IRQn, 1, 0);
}

// DMA 结束后回调
void DMA_TransferComplete_Callback(void) { }
