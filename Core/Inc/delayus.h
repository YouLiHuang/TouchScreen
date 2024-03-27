#ifndef _DELAYUS_H
#define _DELAYUS_H

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void delay_ms(uint16_t nms);
void delay_us(uint32_t nus);

#endif