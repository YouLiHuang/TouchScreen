#ifndef _TOUCH_H_
#define _TOUCH_H_
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "stm32f4xx_hal_gpio.h"
#include "spi.h"
#include "stm32f4xx.h"
#include "tim.h"

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"



#define SCAN_RATE 50 // 扫描频率
#define SCAN_PREIOD 1000 / SCAN_RATE
#define FILTER 0 // 若要开启触摸均值滤波，设置此宏为1
#define CMD_READX 0xD0
#define CMD_READY 0x90
#define CS_H HAL_GPIO_WritePin(TOUCH_CS_GPIO_Port, TOUCH_CS_Pin, GPIO_PIN_SET)
#define CS_L HAL_GPIO_WritePin(TOUCH_CS_GPIO_Port, TOUCH_CS_Pin, GPIO_PIN_RESET)
#define CLK_H HAL_GPIO_WritePin(TOUCH_CLK_GPIO_Port, TOUCH_CLK_Pin, GPIO_PIN_SET)
#define CLK_L HAL_GPIO_WritePin(TOUCH_CLK_GPIO_Port, TOUCH_CLK_Pin, GPIO_PIN_RESET)
#define DO_H HAL_GPIO_WritePin(TOUCH_DO_GPIO_Port, TOUCH_DO_Pin, GPIO_PIN_SET)
#define DO_L HAL_GPIO_WritePin(TOUCH_DO_GPIO_Port, TOUCH_DO_Pin, GPIO_PIN_RESET)

#define DI_READ HAL_GPIO_ReadPin(TDOICH_DI_GPIO_Port, TDOICH_DI_Pin)
#define TOUCH_IRQ_READ HAL_GPIO_ReadPin(ITOUCH_IRQ_GPIO_Port, ITOUCH_IRQ_Pin)

// it recommend that x and y is between 0-10
#define VERTICALOFFSET 5
#define HORIZONYOFFSET 8

typedef enum{
    PRESSED=0,
    RELEASE=1
}key_state_t;


uint16_t getcoordinate(uint16_t cmd);
void Touch_init(void);
uint8_t press_scan(void); // 弃用

#endif
