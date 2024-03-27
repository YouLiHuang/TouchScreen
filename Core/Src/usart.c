/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

UART_HandleTypeDef g_uart_handle;              /**< uart handle */
uint8_t g_uart_rx_buffer[UART_MAX_LEN];        /**< uart rx buffer */
uint8_t g_uart_buffer;                         /**< uart one buffer */
volatile uint16_t g_uart_point;                /**< uart rx point */
volatile uint8_t g_uart_tx_done;               /**< uart tx done flag */

/**
 * @brief     uart init with 8 data bits, 1 stop bit and no parity
 * @param[in] baud is the baud rate
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      TX is PA9 and RX is PA10
 */
uint8_t uart_init(uint32_t baud)
{
    g_uart_handle.Instance = USART1;
    g_uart_handle.Init.BaudRate = baud;
    g_uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
    g_uart_handle.Init.StopBits = UART_STOPBITS_1;
    g_uart_handle.Init.Parity = UART_PARITY_NONE;
    g_uart_handle.Init.Mode = UART_MODE_TX_RX;
    g_uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    g_uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;

    /* uart init */
    if (HAL_UART_Init(&g_uart_handle) != HAL_OK)
    {
        return 1;
    }

    /* receive one byte */
    if (HAL_UART_Receive_IT(&g_uart_handle, (uint8_t *)&g_uart_buffer, 1) != HAL_OK)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief  uart deint
 * @return status code
 *         - 0 success
 *         - 1 deinit
 * @note   none
 */
uint8_t uart_deinit(void)
{
    /* uart deinit */
    if (HAL_UART_DeInit(&g_uart_handle) != HAL_OK)
    {
        return 1;
    }

    return 0;
}


/**
 * @brief     uart write data
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t uart_write(uint8_t *buf, uint16_t len)
{
    uint16_t timeout = 1000;

    /* set tx done 0 */
    g_uart_tx_done = 0;

    /* transmit */
    if (HAL_UART_Transmit_IT(&g_uart_handle, (uint8_t *)buf, len) != HAL_OK)
    {
        return 1;
    }

    /* wait for events */
    while ((g_uart_tx_done == 0) && (timeout != 0))
    {
        HAL_Delay(1);
        timeout--;
    }

    /* check the timeout */
    if (timeout != 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
 * @brief      uart read data
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data length
 * @return     length of the read data
 * @note       this function will clear all received buffer even read length is less than received length
 */
uint16_t uart_read(uint8_t *buf, uint16_t len)
{
    uint16_t read_len;
    uint16_t g_uart_point_old;

    /* check receiving */
    start:
    g_uart_point_old = g_uart_point;
    HAL_Delay(1);
    if (g_uart_point > g_uart_point_old)
    {
        goto start;
    }

    /* copy the data */
    read_len = (len < g_uart_point) ? len : g_uart_point;
    memcpy(buf, g_uart_rx_buffer, read_len);

    /* clear the buffer */
    g_uart_point = 0;

    return read_len;
}

/**
 * @brief  uart flush data
 * @return status code
 *         - 0 success
 * @note   none
 */
uint16_t uart_flush(void)
{
    /* clear the buffer */
    g_uart_point = 0;

    return 0;
}

/**
 * @brief     uart print format data
 * @param[in] fmt is the format data
 * @return    length of the sent data
 * @note      none
 */
uint16_t uart_print(const char *const fmt, ...)
{
    char str[256];
    uint16_t len;
    va_list args;

    /* print to the buffer */
    memset((char *)str, 0, sizeof(char) * 256);
    va_start(args, fmt);
    vsnprintf((char *)str, 255, (char const *)fmt, args);
    va_end(args);

    /* send the data */
    len = strlen((char *)str);
    if (uart_write((uint8_t *)str, len) != 0)
    {
        return 0;
    }
    else
    {
        return len;
    }
}

/**
 * @brief  uart get the handle
 * @return points to a uart handle
 * @note   none
 */
UART_HandleTypeDef* uart_get_handle(void)
{
    return &g_uart_handle;
}



/**
 * @brief uart set tx done
 * @note  none
 */
void uart_set_tx_done(void)
{
    g_uart_tx_done = 1;
}



/**
 * @brief uart irq handler
 * @note  none
 */
void uart_irq_handler(void)
{
    /* save one byte */
    g_uart_rx_buffer[g_uart_point] = g_uart_buffer;
    g_uart_point++;
    if (g_uart_point > (UART_MAX_LEN - 1))
    {
        g_uart_point = 0;
    }

    /* receive one byte */
    (void)HAL_UART_Receive_IT(&g_uart_handle, (uint8_t *)&g_uart_buffer, 1);
}





/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
