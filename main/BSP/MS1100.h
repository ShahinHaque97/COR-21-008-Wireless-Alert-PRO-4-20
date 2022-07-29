/*
 * @file    MS1100.h
 * @brief   header file for MS1100.c
 * @version 22/07/2022
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

#ifndef CONSOLE_MS1100_H
#define CONSOLE_MS1100_H
/**************************** LIB INCLUDES ******************************/
#include "esp_spi_flash.h"
#include <driver/i2c.h>
#include "esp_log.h"
#include "esp_console.h"
#include "BSP/GPIO_testboard.h"
/**************************** USER INCLUDES *****************************/
/******************************* DEFINES ********************************/

#define MS1100_device_address 0x48
/******************************** ENUMS *********************************/
/****************************** TYPEDEFS ********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
esp_err_t ADS1100_selective_read_to_slave();
esp_err_t esp_console_register_MS1100_read(void *function);
esp_err_t esp_console_register_MS1100_read_config(void *function);
esp_err_t MS1100_print_out();
esp_err_t MS1100_setup_config_register();
esp_err_t MS1100_general_call_reset();
esp_err_t MS1100_read_to_slave(uint8_t register_data[3]);
bool MS1100_read_registers(uint8_t *dataOut);
uint8_t MS1100_current_calculation(float *current_out);
uint8_t MS1100_display_config_register();
/******************************* GLOBALS ********************************/
/*        Globals are to be avoided unless justified and documented */
/************************************************************************/

#endif //CONSOLE_MS1100_H
