#ifndef WIRE_H
#define WIRE_H

/*this file is used for the configuration of DC PIN and the RES PIN*/

#include "stm32f4xx_hal.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @defgroup wire wire function
 * @brief    wire function modules
 * @{
 */

/**
 * @brief  wire bus init
 * @return status code
 *         - 0 success
 * @note   IO is PA8
 */
uint8_t wire_init(void);

/**
 * @brief  wire bus deint
 * @return status code
 *         - 0 success
 * @note   none
 */
uint8_t wire_deinit(void);

/**
 * @brief      wire bus read data
 * @param[out] *value points to a read data buffer
 * @return     status code
 *             - 0 success
 * @note       none
 */
uint8_t wire_read(uint8_t *value);

/**
 * @brief     wire bus write data
 * @param[in] value is the write data
 * @return    status code
 *            - 0 success
 * @note      none
 */
uint8_t wire_write(uint8_t value);

/**
 * @brief  wire bus init
 * @return status code
 *         - 0 success
 * @note   IO is PA0
 */
uint8_t wire_clock_init(void);

/**
 * @brief  wire bus deint
 * @return status code
 *         - 0 success
 * @note   none
 */
uint8_t wire_clock_deinit(void);

/**
 * @brief     wire bus write the data
 * @param[in] value is the write data
 * @return    status code
 *            - 0 success
 * @note      none
 */
uint8_t wire_clock_write(uint8_t value);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif




#endif
