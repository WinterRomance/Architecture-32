#ifndef __LED_H
#define __LED_H

#include <stdio.h>

#include "gd32f1x0.h"
#include "gd32f1x0_timer.h"
#include "gd32f1x0_dma.h"

void led_gpio_init(void);
void led_on(void);
void led_off(void);
void led_toggle(void);

#endif