#include "gd32f1x0.h"
#include <stdio.h>
#include "usart.h"

/**
 * @brief 串口初始化函数，使用 USART0（PA9=TX, PA10=RX）
 * @param baudrate 波特率，例如 115200
 */
void uart_init(uint32_t baudrate)
{
    /* 1. 使能 GPIOA 和 USART0 时钟 */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_USART0);

    /* 2. AF 映射：将 PA9/PA10 复用到 USART0（AF1） */
    /* connect port to USARTx_Tx */
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_9);

    /* connect port to USARTx_Rx */
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_10);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_9);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_10);

    /* USART configure */
    usart_deinit(USART0);
    usart_baudrate_set(USART0, baudrate);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_enable(USART0);
}

// 带行列号的增强版打印
void debug_print_matrix(const uint32_t *buf, uint16_t rows, uint16_t cols)
{
    for (uint16_t i = 0; i < rows; i++)
    {
        printf("[Row %2u]: ", i);
        for (uint16_t j = 0; j < cols; j++)
        {
            printf("%03u ", buf[i * cols + j]); // 固定3位数字对齐
        }
        printf("\n");
    }
}

/**
 * @brief 重定向 fputc，用于 printf 输出到 USART0
 * @param ch 要发送的字符
 * @param *f 文件指针（忽略）
 * @return 返回发送的字符
 */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t)ch);
    while (RESET == usart_flag_get(USART0, USART_FLAG_TBE))
        ;

    return ch;
}
