#include "wire.h"
#include "main.h"
/**
 * @brief bit operate definition
 */
#define BITBAND(addr, bitnum)    ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr)           *((uint32_t *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

/**
 * @brief wire gpio operate definition
 */
#define GPIOB_ODR_Addr        (GPIOB_BASE + 0x14)
#define GPIOB_IDR_Addr        (GPIOB_BASE + 0x10)
#define PBout(n)               BIT_ADDR(GPIOB_ODR_Addr, n)
#define PBin(n)                BIT_ADDR(GPIOB_IDR_Addr, n)
#define DQ_OUT                 PBout(1)
#define DQ_IN                  PBin(1)
//IO mode change PB1
#define IO_IN()               {GPIOB->MODER &= ~(3 << (1 * 2)); GPIOB->MODER |= 0 << (1 * 2);}//first clear then set bit
#define IO_OUT()              {GPIOB->MODER &= ~(3 << (1 * 2)); GPIOB->MODER |= 1 << (1 * 2);}


/**
 * @brief  wire bus init
 * @return status code
 *         - 0 success
 * @note   IO is PA4
 */
uint8_t wire_init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    /* enable gpio clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* gpio init */
    GPIO_Initure.Pin = DC_Pin;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);

    /* output mode */
    IO_OUT();

    /* set high */
    DQ_OUT = 1;

    /* input mode */
    IO_IN();

    return 0;
}

/**
 * @brief  wire bus deint
 * @return status code
 *         - 0 success
 * @note   none
 */
uint8_t wire_deinit(void)
{
    /* gpio deinit */
    HAL_GPIO_DeInit(DC_GPIO_Port, DC_Pin);

    return 0;
}

/**
 * @brief      wire bus read data(see as IO to read data )
 * @param[out] *value points to a read data buffer
 * @return     status code
 *             - 0 success
 * @note       none
 */
uint8_t wire_read(uint8_t *value)
{
    /* input mode */
    IO_IN();

    /* read the data */
    *value = DQ_IN;

    return 0;
}

/**
 * @brief     wire bus write data(see as IO to write data DC PIN )
 * @param[in] value is the write data
 * @return    status code
 *            - 0 success
 * @note      none
 */
uint8_t wire_write(uint8_t value)
{
    /* output mode */
    IO_OUT();

    /* set the data */
    DQ_OUT = value;

    return 0;
}

/**
 * @brief  wire bus init(RES IO)
 * @return status code
 *         - 0 success
 * @note   IO is PA0
 */
uint8_t wire_clock_init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    /* enable gpio clock */
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* gpio init */
    GPIO_Initure.Pin = RES_Pin;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(RES_GPIO_Port, &GPIO_Initure);

    return 0;
}

/**
 * @brief  wire bus deint
 * @return status code
 *         - 0 success
 * @note   none
 */
uint8_t wire_clock_deinit(void)
{
    /* gpio deinit */
    HAL_GPIO_DeInit(RES_GPIO_Port, RES_Pin);

    return 0;
}

/**
 * @brief     wire bus write the data
 * @param[in] value is the write data
 * @return    status code
 *            - 0 success
 * @note      none
 */
uint8_t wire_clock_write(uint8_t value)
{
    if (value != 0)
    {
        /* set high */
        HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_SET);
    }
    else
    {
        /* set low */
        HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_RESET);
    }

    return 0;
}
