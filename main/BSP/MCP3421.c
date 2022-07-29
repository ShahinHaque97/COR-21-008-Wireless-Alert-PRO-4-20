/*
 * @file    MCP3421.c
 * @brief   ADC file
 * @version 21/07/2022
 * @par     (c)   Copyright Corintech Ltd
 *          Ashford Mill, Station Road, Fordingbridge, SP6 1DZ, UK
 *          Tel: +44(0)1425 655655. Fax: +44(0)1425 652756
 *
 * @copyright
 *
 *           All information contained herein is, and remains the property of
 *           Corintech Ltd. The intellectual and technical concepts contained
 *           herein are proprietary to Corintech Ltd and may be covered by U.K.
 *           and Foreign Patents, patents in process, and are protected by trade
 *           secret or copyright law. Dissemination of this information or
 *           reproduction of this material is strictly forbidden unless prior
 *           written permission is obtained from Corintech Ltd.
 */

/**************************** LIB INCLUDES ******************************/
/**************************** USER INCLUDES *****************************/
#include "BSP/MCP3421.h"
/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/
/******************************* VARIABLES ******************************/
/*************************** PUBLIC FUNCTIONS ***************************/

/* i2c init */
esp_err_t MCP3421_initialize(void)
{
    i2c_driver_install(I2C_PORT, I2C_MODE_MASTER, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
    i2c_config_t conf = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = i2c_gpio_sda,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_io_num = i2c_gpio_scl,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master.clk_speed = i2c_frequency,
            // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
    };
    return i2c_param_config(I2C_PORT, &conf);
}

esp_err_t MCP3421_register_write_byte(uint8_t reg_addr, uint8_t data)
{
    int ret;
    uint8_t write_buf[1] = {data};

    ret = i2c_master_write_to_device(I2C_MASTER_NUM,
                                     MCP3421_SENSOR_ADDR, write_buf,
                                     sizeof(write_buf), I2C_MASTER_TIMEOUT_MS/ portTICK_RATE_MS);

    return ret;
}

esp_err_t MCP3421_register_read(uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_master_read_from_device(I2C_MASTER_NUM,
                                       MCP3421_SENSOR_ADDR, data, len,
                                       I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
}

esp_err_t MCP3421_set_one_shot_read(void)
{
    uint8_t RDY =               0b1;
    uint8_t sample_rate =       0b11;
    uint8_t gain =              0b00;
    uint8_t conversion_mode=    0b0;

    uint8_t register_command = 0b00000000;
    register_command =  RDY<<7 | conversion_mode <<4 |sample_rate<< 2 | gain;//8C
    MCP3421_register_write_byte(0x68, register_command);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    return 0;
}

uint32_t MCP3421_get_raw_data(void)
{
    uint8_t  output_data[3];
    uint32_t data_bit_shifted;
    MCP3421_register_read(0x68, output_data, 3);
    data_bit_shifted = ((output_data[0]) << 16) |  (output_data[1] << 8) | (output_data[2]) ;

    return data_bit_shifted;
}
