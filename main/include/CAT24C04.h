/*
 * @file    i2c_probe.h
 * @brief   header file for i2c_probe.c
 * @version 20/07/2022
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
#include "esp_spi_flash.h"
#include <driver/i2c.h>
/**************************** USER INCLUDES *****************************/
/******************************* DEFINES ********************************/
#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define i2c_port  I2C_NUM_0
#define i2c_gpio_sda  1
#define i2c_gpio_scl  0
#define i2c_frequency 100000

#define MAIN_I2C_READ_BIT 1
#define MAIN_I2C_WRITE_BIT 0

#define probe_address     0x50
#define I2C_MASTER_TIMEOUT_MS   2000
/******************************** ENUMS *********************************/
/****************************** TYPEDEFS ********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
esp_err_t CAT24C04_initialize(void);
esp_err_t CAT24C04_selective_read_to_slave(uint8_t reg_addr, uint8_t *data, uint8_t register_location);
esp_err_t CAT24C04_page_write_to_slave(uint8_t reg_addr, uint8_t register_location, uint8_t data[],uint8_t len );
esp_err_t CAT24C04_console_single_write(void);
esp_err_t CAT24C04_console_single_read(void);
esp_err_t CAT24C04_console_single_page_write(void);

uint8_t CAT24C04_read_printout(int argc, char **argv);
uint8_t CAT24C04_write_printout(int argc, char **argv);
uint8_t CAT24C04_pageWrite_printout(int argc, char **argv);
/******************************* GLOBALS ********************************/
/*        Globals are to be avoided unless justified and documented */
/************************************************************************/


//
// Created by Shahin.Haque on 19/07/2022.
//

#ifndef CONSOLE_I2C_PROBE_H
#define CONSOLE_I2C_PROBE_H

#endif //CONSOLE_I2C_PROBE_H
