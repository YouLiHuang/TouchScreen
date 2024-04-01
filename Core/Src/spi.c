/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.c
  * @brief   This file provides code for the configuration
  *          of the SPI instances.
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
#include "spi.h"

/* USER CODE BEGIN 0 */

SPI_HandleTypeDef g_spi_handle;        /**< spi handle */

/**
 * @brief  spi cs init
 * @return status code
 *         - 0 success
 * @note   none
 */
//static uint8_t a_spi_cs_init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStruct;
//
//    /* enable cs gpio clock */
//    __HAL_RCC_GPIOA_CLK_ENABLE();
//
//    /* gpio init */
//    GPIO_InitStruct.Pin = GPIO_PIN_4;//correct
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//    return 0;
//}

uint8_t spi_init(spi_mode_t mode){

    g_spi_handle.Instance = SPI1;
    g_spi_handle.Init.Mode = SPI_MODE_MASTER;
    g_spi_handle.Init.Direction = SPI_DIRECTION_2LINES;
    g_spi_handle.Init.DataSize = SPI_DATASIZE_8BIT;

    /* set the mode */
    if (mode == SPI_MODE_0)
    {
        g_spi_handle.Init.CLKPolarity = SPI_POLARITY_LOW;
        g_spi_handle.Init.CLKPhase = SPI_PHASE_1EDGE;
    }
    else if (mode == SPI_MODE_1)
    {
        g_spi_handle.Init.CLKPolarity = SPI_POLARITY_LOW;
        g_spi_handle.Init.CLKPhase = SPI_PHASE_2EDGE;
    }
    else if (mode == SPI_MODE_2)
    {
        g_spi_handle.Init.CLKPolarity = SPI_POLARITY_HIGH;
        g_spi_handle.Init.CLKPhase = SPI_PHASE_1EDGE;
    }
    else
    {
        g_spi_handle.Init.CLKPolarity = SPI_POLARITY_HIGH;
        g_spi_handle.Init.CLKPhase = SPI_PHASE_2EDGE;
    }
    g_spi_handle.Init.NSS = SPI_NSS_SOFT;
    g_spi_handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    g_spi_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
    g_spi_handle.Init.TIMode = SPI_TIMODE_DISABLE;
    g_spi_handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    g_spi_handle.Init.CRCPolynomial = 10;

    /* spi init */
    if (HAL_SPI_Init(&g_spi_handle) != HAL_OK)
    {
    	Error_Handler();
        return 1;
    }
    else return 0;

    //return a_spi_cs_init();

}

/**
 * @brief  spi bus deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t spi_deinit(void)
{
    /* cs deinit */
    //HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);

    /* spi deinit */
    if (HAL_SPI_DeInit(&g_spi_handle) != HAL_OK)
    {
        return 1;
    }

    return 0;
}


/**
 * @brief     spi bus write command
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t spi_write_cmd(uint8_t *buf, uint16_t len)
{
    uint8_t res;

    /* set cs low */
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    /* if len > 0 */
    if (len > 0)
    {
        /* transmit the buffer */
    	res =HAL_SPI_Transmit(&g_spi_handle ,buf,len,1000);
        if (res != HAL_OK)
        {
            /* set cs high */
            //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
            return 1;
        }
    }
    /* set cs high */
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

    return 0;
}

/**
 * @brief     spi bus write address 16
 * @param[in] addr is the spi register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t spi_write_address16(uint16_t addr, uint8_t *buf, uint16_t len)
{
    uint8_t buffer[2];
    uint8_t res;

    /* set cs low */
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

    /* transmit the addr  */
    buffer[0] = (addr >> 8) & 0xFF;
    buffer[1] = addr & 0xFF;
    res = HAL_SPI_Transmit(&g_spi_handle, (uint8_t *)buffer, 2, 1000);
    if (res != HAL_OK)
    {
        /* set cs high */
        //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

        return 1;
    }

    /* if len > 0 */
    if (len > 0)
    {
        /* transmit the buffer */
        res = HAL_SPI_Transmit(&g_spi_handle, buf, len, 1000);
        if (res != HAL_OK)
        {
            /* set cs high */
            //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

            return 1;
        }
    }

    /* set cs high */
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

    return 0;
}

/**
 * @brief      spi bus read command
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t spi_read_cmd(uint8_t *buf, uint16_t len)
{
    uint8_t res;

    /* set cs low */
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

    /* if len > 0 */
    if (len > 0)
    {
        /* receive to the buffer */
        res = HAL_SPI_Receive(&g_spi_handle, buf, len, 1000);
        if (res != HAL_OK)
        {
            /* set cs high */
            //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

            return 1;
        }
    }

    /* set cs high */
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

    return 0;
}

/**
 * @brief      spi bus read
 * @param[in]  addr is the spi register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t spi_read(uint8_t addr, uint8_t *buf, uint16_t len)
{
    uint8_t buffer;
    uint8_t res;

    /* set cs low */
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

    /* transmit the addr */
    buffer = addr;
    res = HAL_SPI_Transmit(&g_spi_handle, (uint8_t *)&buffer, 1, 1000);
    if (res != HAL_OK)
    {
        /* set cs high */
        //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

        return 1;
    }

    /* if len > 0 */
    if (len > 0)
    {
        /* receive to the buffer */
        res = HAL_SPI_Receive(&g_spi_handle, buf, len, 1000);
        if (res != HAL_OK)
        {
            /* set cs high */
            //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

            return 1;
        }
    }

    /* set cs high */
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

    return 0;
}

/**
 * @brief      spi bus read address 16
 * @param[in]  addr is the spi register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t spi_read_address16(uint16_t addr, uint8_t *buf, uint16_t len)
{
    uint8_t buffer[2];
    uint8_t res;

    /* set cs low */
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

    /* transmit the addr  */
    buffer[0] = (addr >> 8) & 0xFF;
    buffer[1] = addr & 0xFF;
    res = HAL_SPI_Transmit(&g_spi_handle, (uint8_t *)buffer, 2, 1000);
    if (res != HAL_OK)
    {
        /* set cs high */
        //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

        return 1;
    }

    /* if len > 0 */
    if (len > 0)
    {
        /* receive to the buffer */
        res = HAL_SPI_Receive(&g_spi_handle, buf, len, 1000);
        if (res != HAL_OK)
        {
            /* set cs high */
            //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

            return 1;
        }
    }

    /* set cs high */
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

    return 0;
}

/**
 * @brief      spi transmit
 * @param[in]  *tx points to a tx buffer
 * @param[out] *rx points to a rx buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 transmit failed
 * @note       none
 */
uint8_t spi_transmit(uint8_t *tx, uint8_t *rx, uint16_t len)
{
    uint8_t res;

    /* set cs low */
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

    /* if len > 0 */
    if (len > 0)
    {
        /* transmit */
        res = HAL_SPI_TransmitReceive(&g_spi_handle, tx, rx, len, 1000);
        if (res != HAL_OK)
        {
            /* set cs high */
            //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

            return 1;
        }
    }

    /* set cs high */
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

    return 0;
}

/**
 * @brief      spi bus write read
 * @param[in]  *in_buf points to an input buffer
 * @param[in]  in_len is the input length
 * @param[out] *out_buf points to an output buffer
 * @param[in]  out_len is the output length
 * @return     status code
 *             - 0 success
 *             - 1 write read failed
 * @note       none
 */
uint8_t spi_write_read(uint8_t *in_buf, uint32_t in_len, uint8_t *out_buf, uint32_t out_len)
{
    uint8_t res;

    /* set cs low */
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

    /* if in_len > 0 */
    if (in_len > 0)
    {
        /* transmit the input buffer */
        res = HAL_SPI_Transmit(&g_spi_handle, in_buf, in_len, 1000);
        if (res != HAL_OK)
        {
            /* set cs high */
            //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

            return 1;
        }
    }

    /* if out_len > 0 */
    if (out_len > 0)
    {
        /* transmit to the output buffer */
        res = HAL_SPI_Receive(&g_spi_handle, out_buf, out_len, 1000);
        if (res != HAL_OK)
        {
            /* set cs high */
            //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

            return 1;
        }
    }

    /* set cs high */
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

    return 0;
}

/* USER CODE END 0 */

SPI_HandleTypeDef hspi1;

/* SPI1 init function */
void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
