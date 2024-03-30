#ifndef _DRIVER_TFT_H
#define _DRIVER_TFT_H
#include "driver_st7789.h"
#include "driver_st7789_interface.h"

/**
 * @brief st7789  default definition
 */

#define ST7789_TFT_DEFAULT_COLUMN 240 /**< 240 */
#define ST7789_TFT_DEFAULT_ROW 320    /**< 320 */
#define ST7789_TFT_DEFAULT_GAMMA_CURVE ST7789_GAMMA_CURVE_1
#define ST7789_TFT_DEFAULT_ACCESS (ST7789_ORDER_PAGE_TOP_TO_BOTTOM |   \
                                     ST7789_ORDER_COLUMN_LEFT_TO_RIGHT | \
                                     ST7789_ORDER_PAGE_COLUMN_REVERSE |  \
                                     ST7789_ORDER_LINE_TOP_TO_BOTTOM |   \
                                     ST7789_ORDER_COLOR_RGB |            \
                                     ST7789_ORDER_REFRESH_LEFT_TO_RIGHT)                                 /**< access */
#define ST7789_TFT_DEFAULT_RGB_INTERFACE_COLOR_FORMAT ST7789_RGB_INTERFACE_COLOR_FORMAT_262K           /**< 262K color format */
#define ST7789_TFT_DEFAULT_CONTROL_INTERFACE_COLOR_FORMAT ST7789_CONTROL_INTERFACE_COLOR_FORMAT_16_BIT /**< 16bit color format */
#define ST7789_TFT_DEFAULT_BRIGHTNESS 0xFF                                                             /**< 0xFF brightness */
#define ST7789_TFT_DEFAULT_BRIGHTNESS_BLOCK ST7789_BOOL_FALSE                                          /**< disable brightness block */
#define ST7789_TFT_DEFAULT_DISPLAY_DIMMING ST7789_BOOL_FALSE                                           /**< disable display dimming */
#define ST7789_TFT_DEFAULT_BACKLIGHT ST7789_BOOL_FALSE                                                 /**< disable backlight */
#define ST7789_TFT_DEFAULT_COLOR_ENHANCEMENT ST7789_BOOL_TRUE                                          /**< enable color enhancement */
#define ST7789_TFT_DEFAULT_COLOR_ENHANCEMENT_MODE ST7789_COLOR_ENHANCEMENT_MODE_USER_INTERFACE         /**< user interface */
#define ST7789_TFT_DEFAULT_COLOR_ENHANCEMENT_LEVEL ST7789_COLOR_ENHANCEMENT_LEVEL_HIGH                 /**< high level */
#define ST7789_TFT_DEFAULT_CABC_MINIMUM_BRIGHTNESS 0x00                                                /**< 0x00 */
#define ST7789_TFT_DEFAULT_RAM_ACCESS ST7789_RAM_ACCESS_MCU                                            /**< mcu access */
#define ST7789_TFT_DEFAULT_DISPLAY_MODE ST7789_DISPLAY_MODE_MCU                                        /**< mcu display mode */
#define ST7789_TFT_DEFAULT_FRAME_TYPE ST7789_FRAME_TYPE_0                                              /**< frame type 0 */
#define ST7789_TFT_DEFAULT_DATA_MODE ST7789_DATA_MODE_MSB                                              /**< data mode msb */
#define ST7789_TFT_DEFAULT_RGB_BUS_WIDTH ST7789_RGB_BUS_WIDTH_18_BIT                                   /**< 18 bits */
#define ST7789_TFT_DEFAULT_PIXEL_TYPE ST7789_PIXEL_TYPE_0                                              /**< pixel type 0 */
#define ST7789_TFT_DEFAULT_DIRECT_RGB_MODE ST7789_DIRECT_RGB_MODE_MEM                                  /**< rgb mode mem */
#define ST7789_TFT_DEFAULT_RGB_IF_ENABLE_MODE ST7789_RGB_IF_ENABLE_MODE_MCU                            /**< enable mode mcu */
#define ST7789_TFT_DEFAULT_VSPL ST7789_PIN_LEVEL_LOW                                                   /**< level low */
#define ST7789_TFT_DEFAULT_HSPL ST7789_PIN_LEVEL_LOW                                                   /**< level low */
#define ST7789_TFT_DEFAULT_DPL ST7789_PIN_LEVEL_LOW                                                    /**< level low */
#define ST7789_TFT_DEFAULT_EPL ST7789_PIN_LEVEL_LOW                                                    /**< level low */
#define ST7789_TFT_DEFAULT_VBP 0x02                                                                    /**< 0x02 */
#define ST7789_TFT_DEFAULT_HBP 0x14                                                                    /**< 0x14 */
#define ST7789_TFT_DEFAULT_PORCH_NORMAL_BACK 0x0C                                                      /**< 0x0C */
#define ST7789_TFT_DEFAULT_PORCH_NORMAL_FRONT 0x0C                                                     /**< 0x0C */
#define ST7789_TFT_DEFAULT_PORCH_ENABLE ST7789_BOOL_FALSE                                              /**< disable porch */
#define ST7789_TFT_DEFAULT_PORCH_IDEL_BACK 0x03                                                        /**< 0x03 */
#define ST7789_TFT_DEFAULT_PORCH_IDEL_FRONT 0x03                                                       /**< 0x03 */
#define ST7789_TFT_DEFAULT_PORCH_PART_BACK 0x03                                                        /**< 0x03 */
#define ST7789_TFT_DEFAULT_PORCH_PART_FRONT 0x03                                                       /**< 0x03 */
#define ST7789_TFT_DEFAULT_SEPARATE_FR ST7789_BOOL_FALSE                                               /**< disable fr */
#define ST7789_TFT_DEFAULT_FRAME_RATE_DIVIDED ST7789_FRAME_RATE_DIVIDED_CONTROL_DIV_1                  /**< div 1 */
#define ST7789_TFT_DEFAULT_INVERSION_IDLE_MODE ST7789_INVERSION_IDLE_MODE_DOT                          /**< dot mode */
#define ST7789_TFT_DEFAULT_IDLE_FRAME_RATE 0x0F                                                        /**< 0x0F */
#define ST7789_TFT_DEFAULT_INVERSION_PARTIAL_MODE ST7789_INVERSION_PARTIAL_MODE_DOT                    /**< dot mode */
#define ST7789_TFT_DEFAULT_IDLE_PARTIAL_RATE 0x0F                                                      /**< 0x0F */
#define ST7789_TFT_DEFAULT_NON_DISPLAY_SOURCE_OUTPUT_LEVEL ST7789_NON_DISPLAY_SOURCE_OUTPUT_LEVEL_V63  /**< v63 */
#define ST7789_TFT_DEFAULT_NON_DISPLAY_AREA_SCAN_MODE ST7789_NON_DISPLAY_AREA_SCAN_MODE_NORMAL         /**< normal scan mode */
#define ST7789_TFT_DEFAULT_NON_DISPLAY_FRAME_FREQUENCY ST7789_NON_DISPLAY_FRAME_FREQUENCY_EVERY        /**< every frame */
#define ST7789_TFT_DEFAULT_VGHS ST7789_VGHS_14P97_V                                                    /**< 14.97V */
#define ST7789_TFT_DEFAULT_VGLS_NEGATIVE ST7789_VGLS_NEGATIVE_8P23                                     /**< -8.23 */
#define ST7789_TFT_DEFAULT_GATE_ON_TIMING 0x22                                                         /**< 0x22 */
#define ST7789_TFT_DEFAULT_GATE_OFF_TIMING_RGB 0x07                                                    /**< 0x07 */
#define ST7789_TFT_DEFAULT_GATE_OFF_TIMING 0x05                                                        /**< 0x05 */
#define ST7789_TFT_DEFAULT_DIGITAL_GAMMA ST7789_BOOL_TRUE                                              /**< enable digital gamma */
#define ST7789_TFT_DEFAULT_VCOMS 1.625f                                                                /**< 1.625 vcoms */
#define ST7789_TFT_DEFAULT_XMY ST7789_BOOL_FALSE                                                       /**< disable xmy */
#define ST7789_TFT_DEFAULT_XBGR ST7789_BOOL_TRUE                                                       /**< enable xbgr */
#define ST7789_TFT_DEFAULT_XINV ST7789_BOOL_FALSE                                                      /**< disable xinv */
#define ST7789_TFT_DEFAULT_XMX ST7789_BOOL_TRUE                                                        /**< enable xmx */
#define ST7789_TFT_DEFAULT_XMH ST7789_BOOL_TRUE                                                        /**< enable xmh */
#define ST7789_TFT_DEFAULT_XMV ST7789_BOOL_FALSE                                                       /**< disable xmv */
#define ST7789_TFT_DEFAULT_XGS ST7789_BOOL_FALSE                                                       /**< disable xgs */
#define ST7789_TFT_DEFAULT_VDV_VRH_FROM ST7789_VDV_VRH_FROM_CMD                                        /**< from cmd */
#define ST7789_TFT_DEFAULT_VRHS 4.8f                                                                   /**< 4.8 */
#define ST7789_TFT_DEFAULT_VDV 0.0f                                                                    /**< 0.0 */
#define ST7789_TFT_DEFAULT_VCOMS_OFFSET 0.0f                                                           /**< 0.0 */
#define ST7789_TFT_DEFAULT_INVERSION_SELECTION ST7789_INVERSION_SELECTION_DOT                          /**< dot */
#define ST7789_TFT_DEFAULT_FRAME_RATE ST7789_FRAME_RATE_60_HZ                                          /**< frame rate 60Hz */
#define ST7789_TFT_DEFAULT_LED_ON ST7789_BOOL_FALSE                                                    /**< disable led on */
#define ST7789_TFT_DEFAULT_LED_PWM_INIT ST7789_BOOL_FALSE                                              /**< disable led pwm init */
#define ST7789_TFT_DEFAULT_LED_PWM_FIX ST7789_BOOL_FALSE                                               /**< disable led pwm fix */
#define ST7789_TFT_DEFAULT_LED_PWM_POLARITY ST7789_BOOL_FALSE                                          /**< disable led pwm polarity */
#define ST7789_TFT_DEFAULT_PWM_FREQUENCY ST7789_PWM_FREQUENCY_9P8_KHZ                                  /**< pwm 9.8KHz */
#define ST7789_TFT_DEFAULT_AVDD ST7789_AVDD_6P8_V                                                      /**< 6.8V */
#define ST7789_TFT_DEFAULT_AVCL_NEGTIVE ST7789_AVCL_NEGTIVE_4P8_V                                      /**< -4.8V */
#define ST7789_TFT_DEFAULT_VDS ST7789_VDS_2P3_V                                                        /**< 2.3V */
#define ST7789_TFT_DEFAULT_COMMAND_2_ENABLE ST7789_BOOL_FALSE                                          /**< disable command 2 */
#define ST7789_TFT_DEFAULT_POSITIVE_VOLTAGE_GAMMA  \
    {                                                \
        0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F,    \
            0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23 \
    } /**< gamma */
#define ST7789_TFT_DEFAULT_NEGATIVA_VOLTAGE_GAMMA  \
    {                                                \
        0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F,    \
            0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23 \
    } /**< gamma */
#define ST7789_TFT_DEFAULT_GATE_LINE 320                                        /**< 320 */
#define ST7789_TFT_DEFAULT_FIRST_SCAN_LINE 0x00                                 /**< 0x00 */
#define ST7789_TFT_DEFAULT_GATE_SCAN_MODE ST7789_GATE_SCAN_MODE_INTERLACE       /**< interlace */
#define ST7789_TFT_DEFAULT_GATE_SCAN_DIRECTION ST7789_GATE_SCAN_DIRECTION_0_319 /**< 320 */
#define ST7789_TFT_DEFAULT_SPI2_LANE ST7789_BOOL_FALSE                          /**< disable */
#define ST7789_TFT_DEFAULT_COMMAND_TABLE_2 ST7789_BOOL_FALSE                    /**< disable command table2 */
#define ST7789_TFT_DEFAULT_SBCLK_DIV ST7789_SBCLK_DIV_3                         /**< div3 */
#define ST7789_TFT_DEFAULT_STP14CK_DIV ST7789_STP14CK_DIV_6                     /**< div6 */
#define ST7789_TFT_DEFAULT_SOURCE_EQUALIZE_TIME 0x11                            /**< 0x11 */
#define ST7789_TFT_DEFAULT_SOURCE_PRE_DRIVE_TIME 0x11                           /**< 0x11 */
#define ST7789_TFT_DEFAULT_GATE_EQUALIZE_TIME 0x08                              /**< 0x08 */
#define ST7789_TFT_DEFAULT_PROGRAM_MODE ST7789_BOOL_FALSE                       /**< disable program mode */
#define DISPLAY_INVERSION 0

/**
 * @brief  TFT example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t st7789_tft_init(void);

/**
 * @brief  TFT example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t st7789_tft_deinit(void);

/**
 * @brief  TFT example clear
 * @return status code
 *         - 0 success
 *         - 1 clear failed
 * @note   none
 */
uint8_t st7789_tft_clear(void);

/**
 * @brief  TFT example display on
 * @return status code
 *         - 0 success
 *         - 1 display on failed
 * @note   none
 */
uint8_t st7789_tft_display_on(void);

/**
 * @brief  TFT example display off
 * @return status code
 *         - 0 success
 *         - 1 display off failed
 * @note   none
 */
uint8_t st7789_tft_display_off(void);

/**
 * @brief     tft example write a point
 * @param[in] x is the coordinate x
 * @param[in] y is the coordinate y
 * @param[in] color is the written color
 * @return    status code
 *            - 0 success
 *            - 1 write point failed
 * @note      none
 */
uint8_t st7789_tft_write_point(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief     TFT example draw a 16 bits picture
 * @param[in] left is the left coordinate x
 * @param[in] top is the top coordinate y
 * @param[in] right is the right coordinate x
 * @param[in] bottom is the bottom coordinate y
 * @param[in] buffer is the source to be write
 * @param[in] *img points to a image buffer
 * @return    status code
 *            - 0 success
 *            - 1 draw picture 16 bits failed
 * @note      none
 */
uint8_t st7789_tft_fill(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint16_t *buffer);

#endif

