// #include "gd32f1x0.h"
// #include <stdint.h>
// #include "timer.h"
// #include "usart.h"

// /* ------------------------- �궨�� ------------------------- */
// #define LED_RGB_NUM 10                   // ��������
// #define RGB_BIT 24                       // ÿ�ŵ� 24 λ
// #define RGB_ARRAY_SIZE (LED_RGB_NUM + 3) // �� 3 ��λ���ڸ�λ֡

// #define TIMER1_CH2_CCR2_ADDR ((uint32_t)0x4000003CU)

// #define TIMER_PSC1 0
// #define TIMER_ARR1 89
// #define WS2812_HIGH_CCR 57
// #define WS2812_LOW_CCR 28

// static uint32_t led_buf[RGB_ARRAY_SIZE][RGB_BIT];

// void ws2812_gpio_init(void)
// {
//     rcu_periph_clock_enable(RCU_GPIOB);
//     gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10);
//     gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
//     gpio_af_set(GPIOB, GPIO_AF_2, GPIO_PIN_10);
// }

// void ws2812_timer_init(void)
// {
//     timer_parameter_struct timerpara;
//     timer_oc_parameter_struct ocpara;

//     rcu_periph_clock_enable(RCU_TIMER1);
//     timer_deinit(TIMER1);

//     /* ������ʱ����72MHz��ARR=89 => 1.25us ���� */
//     timerpara.prescaler = TIMER_PSC1;
//     timerpara.alignedmode = TIMER_COUNTER_EDGE;
//     timerpara.counterdirection = TIMER_COUNTER_UP;
//     timerpara.period = TIMER_ARR1;
//     timerpara.clockdivision = TIMER_CKDIV_DIV1;
//     timerpara.repetitioncounter = 0;
//     timer_init(TIMER1, &timerpara);

//     /* CH2 PWM ����Ƚ����� */
//     ocpara.outputstate = TIMER_CCX_ENABLE;
//     ocpara.outputnstate = TIMER_CCXN_DISABLE;
//     ocpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
//     ocpara.ocnpolarity = TIMER_OCN_POLARITY_HIGH;
//     ocpara.ocidlestate = TIMER_OC_IDLE_STATE_HIGH;
//     ocpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
//     timer_channel_output_config(TIMER1, TIMER_CH_2, &ocpara);

//     /* ���� PWM ģʽ0 */
//     timer_channel_output_mode_config(TIMER1, TIMER_CH_2, TIMER_OC_MODE_PWM0);
//     timer_channel_output_shadow_config(TIMER1, TIMER_CH_2, TIMER_OC_SHADOW_DISABLE);

//     /* ��ʼ�Ƚ�ֵΪ�͵�ƽ */
//     timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_2, WS2812_LOW_CCR);

//     /* ? �������״̬����Ҫ�� */
//     timer_channel_output_state_config(TIMER1, TIMER_CH_2, ENABLE);

//     /* ? ��������� */
//     timer_primary_output_config(TIMER1, ENABLE);
//     timer_channel_dma_request_source_select(TIMER1, TIMER_DMAREQUEST_UPDATEEVENT);

//     /* ? ���� DMA��ʹ�� CH2 �Ƚ��¼����� */
//     timer_dma_enable(TIMER1, TIMER_DMA_UPD); // �� �ؼ��޸ĵ㣡

//     /* ����Ԥװ�ؼĴ������� */
//     timer_auto_reload_shadow_enable(TIMER1);

//     /* ������������ʱ������ ws2812_send ���� */
// }

// void ws2812_dma_init(void)
// {
//     dma_parameter_struct dma_init_struct;

//     rcu_periph_clock_enable(RCU_DMA);
//     dma_deinit(DMA_CH1);

//     /* ���� DMA ���ڴ浽 CCR2 �Ĵ��� */
//     dma_init_struct.periph_addr = (uint32_t)(&TIMER_CH2CV(TIMER1)); // CCR2 ��ַ
//     dma_init_struct.memory_addr = (uint32_t)led_buf;                // ����Դ��ַ
//     dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;
//     dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_32BIT;
//     dma_init_struct.memory_width = DMA_MEMORY_WIDTH_32BIT;
//     dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
//     dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
//     dma_init_struct.number = RGB_ARRAY_SIZE * RGB_BIT;
//     dma_init_struct.priority = DMA_PRIORITY_HIGH;
//     dma_init(DMA_CH1, &dma_init_struct);

//     dma_circulation_disable(DMA_CH1);
//     dma_memory_to_memory_disable(DMA_CH1);

//     // ��ѡ�жϣ�����ȷ�ϴ������
//     // dma_interrupt_enable(DMA_CH1, DMA_INT_FTF);
//     // nvic_irq_enable(DMA_Channel0_IRQn, 2, 1);
// }

// void ws2812_send(void)
// {
//     dma_channel_disable(DMA_CH1);
//     dma_transfer_number_config(DMA_CH1, RGB_ARRAY_SIZE * RGB_BIT);
//     dma_channel_enable(DMA_CH1);
//     timer_enable(TIMER1);
// }

// void ws2812_show_color(uint32_t grb, uint8_t brightness)
// {
//     uint32_t mask = 1U << 23;
//     uint32_t tmp;
//     uint16_t i, j;

//     for (i = 0; i < LED_RGB_NUM; i++)
//     {
//         uint32_t g = ((grb >> 16) & 0xFF) * brightness / 100;
//         uint32_t r = ((grb >> 8) & 0xFF) * brightness / 100;
//         uint32_t b = ((grb) & 0xFF) * brightness / 100;
//         tmp = (g << 16) | (r << 8) | b;
//         for (j = 0; j < RGB_BIT; j++)
//         {
//             led_buf[i][j] = (tmp & mask) ? WS2812_HIGH_CCR : WS2812_LOW_CCR;
//             tmp <<= 1;
//         }
//     }

//     for (i = LED_RGB_NUM; i < RGB_ARRAY_SIZE; i++)
//     {
//         for (j = 0; j < RGB_BIT; j++)
//         {
//             led_buf[i][j] = 0;
//         }
//     }
//     debug_print_matrix((uint32_t *)led_buf, RGB_ARRAY_SIZE, RGB_BIT);
//     ws2812_send();
// }

// void ws2812_init(void)
// {
//     ws2812_gpio_init();
//     ws2812_dma_init();
//     ws2812_timer_init();
// }
