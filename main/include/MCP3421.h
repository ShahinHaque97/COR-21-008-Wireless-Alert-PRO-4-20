/*
 * @file    MCP3421.h
 * @brief   header file for MCP3421.c
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
#ifndef HELLO_WORLD_MCP3421_H
#define HELLO_WORLD_MCP3421_H
/**************************** LIB INCLUDES ******************************/
#include "esp_spi_flash.h"
#include <driver/i2c.h>
/**************************** USER INCLUDES *****************************/
/******************************* DEFINES ********************************/
#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define WRITE_BIT I2C_MASTER_WRITE  /*!< I2C master write */
#define ACK_CHECK_EN 0x1            /*!< I2C master will check ack from slave*/



#define I2C_MASTER_TIMEOUT_MS   2000
#define MCP3421_SENSOR_ADDR     0x68
#define I2C_MASTER_NUM          0

#define I2C_PORT  I2C_NUM_0
#define i2c_gpio_sda  1
#define i2c_gpio_scl  0
#define i2c_frequency 100000
/******************************** ENUMS *********************************/
/****************************** TYPEDEFS ********************************/


/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
esp_err_t MCP3421_initialize(void);
esp_err_t i2c_scanner(int argc, char **argv);
esp_err_t MCP3421_register_write_byte(uint8_t reg_addr, uint8_t data);
esp_err_t MCP3421_register_read(uint8_t reg_addr, uint8_t *data, size_t len);
esp_err_t MCP3421_set_one_shot_read(void);

uint32_t MCP3421_get_raw_data(void);
/******************************* GLOBALS ********************************/
/*        Globals are to be avoided unless justified and documented */
/************************************************************************/


//
// Created by Shahin.Haque on 14/07/2022.
//

#endif //HELLO_WORLD_MCP3421_H
