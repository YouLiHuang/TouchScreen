#include "driver_st7789_tft.h"

/*用户自定义的驱动对象*/
static st7789_handle_t gs_handle;

uint8_t st7789_tft_init(void)
{
    uint8_t res;
    uint8_t reg;
    uint16_t i;
    uint8_t param_positive[14] = ST7789_TFT_DEFAULT_POSITIVE_VOLTAGE_GAMMA;
    uint8_t param_negative[14] = ST7789_TFT_DEFAULT_NEGATIVA_VOLTAGE_GAMMA;
    uint8_t params[64];

    /* 接口对接 */
    DRIVER_ST7789_LINK_INIT(&gs_handle, st7789_handle_t);
    DRIVER_ST7789_LINK_SPI_INIT(&gs_handle, st7789_interface_spi_init);
    DRIVER_ST7789_LINK_SPI_DEINIT(&gs_handle, st7789_interface_spi_deinit);
    DRIVER_ST7789_LINK_SPI_WRITE_COMMAND(&gs_handle, st7789_interface_spi_write_cmd);
    DRIVER_ST7789_LINK_COMMAND_DATA_GPIO_INIT(&gs_handle, st7789_interface_cmd_data_gpio_init);
    DRIVER_ST7789_LINK_COMMAND_DATA_GPIO_DEINIT(&gs_handle, st7789_interface_cmd_data_gpio_deinit);
    DRIVER_ST7789_LINK_COMMAND_DATA_GPIO_WRITE(&gs_handle, st7789_interface_cmd_data_gpio_write);
    DRIVER_ST7789_LINK_RESET_GPIO_INIT(&gs_handle, st7789_interface_reset_gpio_init);
    DRIVER_ST7789_LINK_RESET_GPIO_DEINIT(&gs_handle, st7789_interface_reset_gpio_deinit);
    DRIVER_ST7789_LINK_RESET_GPIO_WRITE(&gs_handle, st7789_interface_reset_gpio_write);
    DRIVER_ST7789_LINK_DELAY_MS(&gs_handle, st7789_interface_delay_ms);
    DRIVER_ST7789_LINK_DEBUG_PRINT(&gs_handle, st7789_interface_debug_print);

    /* st7789 init */
    res = st7789_init(&gs_handle);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: init failed.\n");
        return 1;
    }
    /* set default column */
    res = st7789_set_column(&gs_handle, ST7789_TFT_DEFAULT_COLUMN);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }
    /* set default row */
    res = st7789_set_row(&gs_handle, ST7789_TFT_DEFAULT_ROW);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }
    /* sleep out */
    res = st7789_sleep_out(&gs_handle);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }
    /* idle mode off */
    res = st7789_idle_mode_off(&gs_handle);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }
    /* normal display mode on */
    res = st7789_normal_display_mode_on(&gs_handle);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }
    /* set default gamma */
    res = st7789_set_gamma(&gs_handle, ST7789_TFT_DEFAULT_GAMMA_CURVE);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }
    /* set default memory data access control */
    res = st7789_set_memory_data_access_control(&gs_handle, ST7789_TFT_DEFAULT_ACCESS);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }
    /* set default pixel format */
    res = st7789_set_interface_pixel_format(&gs_handle, ST7789_TFT_DEFAULT_RGB_INTERFACE_COLOR_FORMAT,
                                            ST7789_TFT_DEFAULT_CONTROL_INTERFACE_COLOR_FORMAT);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }
    /* set default brightness */
    res = st7789_set_display_brightness(&gs_handle, ST7789_TFT_DEFAULT_BRIGHTNESS);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }
    /* set default brightness control */
    res = st7789_set_display_control(&gs_handle,
                                     ST7789_TFT_DEFAULT_BRIGHTNESS_BLOCK,
                                     ST7789_TFT_DEFAULT_DISPLAY_DIMMING,
                                     ST7789_TFT_DEFAULT_BACKLIGHT);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }

    /* set default color enhancement */
    res = st7789_set_brightness_control_and_color_enhancement(&gs_handle, ST7789_TFT_DEFAULT_COLOR_ENHANCEMENT,
                                                              ST7789_TFT_DEFAULT_COLOR_ENHANCEMENT_MODE,
                                                              ST7789_TFT_DEFAULT_COLOR_ENHANCEMENT_LEVEL);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }
    /* set default cabc minimum brightness */
    res = st7789_set_cabc_minimum_brightness(&gs_handle, ST7789_TFT_DEFAULT_CABC_MINIMUM_BRIGHTNESS);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }

    /* set default ram control */
    res = st7789_set_ram_control(&gs_handle,
                                 ST7789_TFT_DEFAULT_RAM_ACCESS,
                                 ST7789_TFT_DEFAULT_DISPLAY_MODE,
                                 ST7789_TFT_DEFAULT_FRAME_TYPE,
                                 ST7789_TFT_DEFAULT_DATA_MODE,
                                 ST7789_TFT_DEFAULT_RGB_BUS_WIDTH,
                                 ST7789_TFT_DEFAULT_PIXEL_TYPE);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default rgb interface control */
    res = st7789_set_rgb_interface_control(&gs_handle,
                                           ST7789_TFT_DEFAULT_DIRECT_RGB_MODE,
                                           ST7789_TFT_DEFAULT_RGB_IF_ENABLE_MODE,
                                           ST7789_TFT_DEFAULT_VSPL,
                                           ST7789_TFT_DEFAULT_HSPL,
                                           ST7789_TFT_DEFAULT_DPL,
                                           ST7789_TFT_DEFAULT_EPL,
                                           ST7789_TFT_DEFAULT_VBP,
                                           ST7789_TFT_DEFAULT_HBP);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default porch */
    res = st7789_set_porch(&gs_handle,
                           ST7789_TFT_DEFAULT_PORCH_NORMAL_BACK,
                           ST7789_TFT_DEFAULT_PORCH_NORMAL_FRONT,
                           ST7789_TFT_DEFAULT_PORCH_ENABLE,
                           ST7789_TFT_DEFAULT_PORCH_IDEL_BACK,
                           ST7789_TFT_DEFAULT_PORCH_IDEL_FRONT,
                           ST7789_TFT_DEFAULT_PORCH_PART_BACK,
                           ST7789_TFT_DEFAULT_PORCH_PART_FRONT);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default frame rate control */
    res = st7789_set_frame_rate_control(&gs_handle,
                                        ST7789_TFT_DEFAULT_SEPARATE_FR,
                                        ST7789_TFT_DEFAULT_FRAME_RATE_DIVIDED,
                                        ST7789_TFT_DEFAULT_INVERSION_IDLE_MODE,
                                        ST7789_TFT_DEFAULT_IDLE_FRAME_RATE,
                                        ST7789_TFT_DEFAULT_INVERSION_PARTIAL_MODE,
                                        ST7789_TFT_DEFAULT_IDLE_PARTIAL_RATE);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default partial mode control */
    res = st7789_set_partial_mode_control(&gs_handle,
                                          ST7789_TFT_DEFAULT_NON_DISPLAY_SOURCE_OUTPUT_LEVEL,
                                          ST7789_TFT_DEFAULT_NON_DISPLAY_AREA_SCAN_MODE,
                                          ST7789_TFT_DEFAULT_NON_DISPLAY_FRAME_FREQUENCY);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default gate control */
    res = st7789_set_gate_control(&gs_handle, ST7789_TFT_DEFAULT_VGHS, ST7789_TFT_DEFAULT_VGLS_NEGATIVE);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default gate on timing adjustment */
    res = st7789_set_gate_on_timing_adjustment(&gs_handle,
                                               ST7789_TFT_DEFAULT_GATE_ON_TIMING,
                                               ST7789_TFT_DEFAULT_GATE_OFF_TIMING_RGB,
                                               ST7789_TFT_DEFAULT_GATE_OFF_TIMING);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default digital gamma */
    res = st7789_set_digital_gamma(&gs_handle, ST7789_TFT_DEFAULT_DIGITAL_GAMMA);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* vcom convert to register  */
    res = st7789_vcom_convert_to_register(&gs_handle, ST7789_TFT_DEFAULT_VCOMS, &reg);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default vcoms */
    res = st7789_set_vcoms(&gs_handle, reg);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default lcm control */
    res = st7789_set_lcm_control(&gs_handle,
                                 ST7789_TFT_DEFAULT_XMY,
                                 ST7789_TFT_DEFAULT_XBGR,
                                 ST7789_TFT_DEFAULT_XINV,
                                 ST7789_TFT_DEFAULT_XMX,
                                 ST7789_TFT_DEFAULT_XMH,
                                 ST7789_TFT_DEFAULT_XMV,
                                 ST7789_TFT_DEFAULT_XGS);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default vdv vrh cmd */
    res = st7789_set_vdv_vrh_from(&gs_handle, ST7789_TFT_DEFAULT_VDV_VRH_FROM);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* vrhs convert to register */
    res = st7789_vrhs_convert_to_register(&gs_handle, ST7789_TFT_DEFAULT_VRHS, &reg);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default vrhs */
    res = st7789_set_vrhs(&gs_handle, reg);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* vdv convert to register */
    res = st7789_vdv_convert_to_register(&gs_handle, ST7789_TFT_DEFAULT_VDV, &reg);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default vdv */
    res = st7789_set_vdv(&gs_handle, reg);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* vcoms offset convert to register */
    res = st7789_vcoms_offset_convert_to_register(&gs_handle, ST7789_TFT_DEFAULT_VCOMS_OFFSET, &reg);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default vcoms offset */
    res = st7789_set_vcoms_offset(&gs_handle, reg);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default frame rate */
    res = st7789_set_frame_rate(&gs_handle, ST7789_TFT_DEFAULT_INVERSION_SELECTION, ST7789_TFT_DEFAULT_FRAME_RATE);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default cabc control */
    res = st7789_set_cabc_control(&gs_handle,
                                  ST7789_TFT_DEFAULT_LED_ON,
                                  ST7789_TFT_DEFAULT_LED_PWM_INIT,
                                  ST7789_TFT_DEFAULT_LED_PWM_FIX,
                                  ST7789_TFT_DEFAULT_LED_PWM_POLARITY);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default pwm frequency */
    res = st7789_set_pwm_frequency(&gs_handle, ST7789_TFT_DEFAULT_PWM_FREQUENCY);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default power control 1 */
    res = st7789_set_power_control_1(&gs_handle,
                                     ST7789_TFT_DEFAULT_AVDD,
                                     ST7789_TFT_DEFAULT_AVCL_NEGTIVE,
                                     ST7789_TFT_DEFAULT_VDS);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default command 2 */
    res = st7789_set_command_2_enable(&gs_handle, ST7789_TFT_DEFAULT_COMMAND_2_ENABLE);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default positive voltage gamma control */
    res = st7789_set_positive_voltage_gamma_control(&gs_handle, param_positive);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default negative voltage gamma control */
    res = st7789_set_negative_voltage_gamma_control(&gs_handle, param_negative);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* create the table */
    for (i = 0; i < 64; i++)
    {
        params[i] = i * 4;
    }

    /* set default digital gamma look up table red */
    res = st7789_set_digital_gamma_look_up_table_red(&gs_handle, params);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default digital gamma look up table blue */
    res = st7789_set_digital_gamma_look_up_table_blue(&gs_handle, params);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default gate line convert to register */
    res = st7789_gate_line_convert_to_register(&gs_handle, ST7789_TFT_DEFAULT_GATE_LINE, &reg);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default gate */
    res = st7789_set_gate(&gs_handle,
                          reg,
                          ST7789_TFT_DEFAULT_FIRST_SCAN_LINE,
                          ST7789_TFT_DEFAULT_GATE_SCAN_MODE,
                          ST7789_TFT_DEFAULT_GATE_SCAN_DIRECTION);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default spi2 */
    res = st7789_set_spi2_enable(&gs_handle, ST7789_TFT_DEFAULT_SPI2_LANE, ST7789_TFT_DEFAULT_COMMAND_TABLE_2);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default power control 2 */
    res = st7789_set_power_control_2(&gs_handle, ST7789_TFT_DEFAULT_SBCLK_DIV, ST7789_TFT_DEFAULT_STP14CK_DIV);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);

        return 1;
    }

    /* set default equalize time control */
    res = st7789_set_equalize_time_control(&gs_handle,
                                           ST7789_TFT_DEFAULT_SOURCE_EQUALIZE_TIME,
                                           ST7789_TFT_DEFAULT_SOURCE_PRE_DRIVE_TIME,
                                           ST7789_TFT_DEFAULT_GATE_EQUALIZE_TIME);
    if (res != 0)
    {

        (void)st7789_deinit(&gs_handle);
        return 1;
    }

    /* set default program mode */
    res = st7789_set_program_mode_enable(&gs_handle, ST7789_TFT_DEFAULT_PROGRAM_MODE);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }

    /* display on */
    res = st7789_display_on(&gs_handle);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }

    /* clear */
    res = st7789_clear(&gs_handle);
    if (res != 0)
    {
        (void)st7789_deinit(&gs_handle);
        return 1;
    }

    return 0;
}

/**
 * @brief  tft example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t st7789_tft_deinit(void)
{
    /* st7789 deinit */
    if (st7789_deinit(&gs_handle) != 0)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief  tft example clear
 * @return status code
 *         - 0 success
 *         - 1 clear failed
 * @note   none
 */
uint8_t st7789_tft_clear(void)
{
    /* st7789 clear */
    if (st7789_clear(&gs_handle) != 0)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief  tft example display on
 * @return status code
 *         - 0 success
 *         - 1 display on failed
 * @note   none
 */
uint8_t st7789_tft_display_on(void)
{
    /* display on */
    if (st7789_display_on(&gs_handle) != 0)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief  tft example display off
 * @return status code
 *         - 0 success
 *         - 1 display off failed
 * @note   none
 */
uint8_t st7789_tft_display_off(void)
{
    /* display off */
    if (st7789_display_off(&gs_handle) != 0)
    {
        return 1;
    }

    return 0;
}

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
uint8_t st7789_tft_write_point(uint16_t x, uint16_t y, uint32_t color)
{
    /* draw point */
    if (st7789_draw_point(&gs_handle, x, y, color) != 0)
    {
        return 1;
    }

    return 0;
}
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
uint8_t st7789_tft_fill(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint16_t *buffer)
{

     lvgl_fill_16bits_color(&gs_handle, left, top, right, bottom, buffer);
     return 0;
}


