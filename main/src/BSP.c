/*
 * @file    X
 * @brief   X
 * @version X
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
#include "include/BSP.h"
/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/
/******************************* VARIABLES ******************************/
/*************************** PUBLIC FUNCTIONS ***************************/

esp_err_t i2c_init(void)
{
    i2c_driver_install(i2c_port, I2C_MODE_MASTER, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
    i2c_config_t conf = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = i2c_gpio_sda,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_io_num = i2c_gpio_scl,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master.clk_speed = i2c_frequency,
            // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
    };
    return i2c_param_config(i2c_port, &conf);
}

int BSP_init()
{
    i2c_init();

    /* i2c initialization in each of those functions.
     * MCP3421_initialize();
     * CAT24C04_initialize();
     *
     */
    gpio_init();

    return 0;
}
