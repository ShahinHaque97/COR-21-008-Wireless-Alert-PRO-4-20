/*
 * @file    console_dir.h
 * @brief   header file for console_dir.c
 * @version 13/07/2022
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
#include "esp_log.h"
#include "esp_console.h"

/**************************** USER INCLUDES *****************************/
#include "Middleware/Probe_EEPROM.h"
#include "BSP/MCP3421.h"
#include "BSP/CAT24C04.h"
#include "application.h"
#include "BSP/MS1100.h"
#include "BSP/BSP.h"
/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/
/****************************** TYPEDEFS ********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
static int clear_screen(); //local
esp_err_t esp_console_register_clear(void);
esp_err_t esp_console_register_i2c_scanner(void *function );
esp_err_t esp_console_register_low_current_test(void *function);
esp_err_t esp_console_register_mid_current_test(void *function);
esp_err_t esp_console_register_high_current_test(void *function);
esp_err_t esp_console_register_compare_ADC(void *function );

esp_err_t esp_console_register_EEPROM_read_all(void *function );

void console_init();
void console_new_reply();
void console_register_commands();
/******************************* GLOBALS ********************************/
/*        Globals are to be avoided unless justified and documented */
/************************************************************************/















//
// Created by Shahin.Haque on 21/07/2022.
//

#ifndef CONSOLE_CONSOLE_DIR_H
#define CONSOLE_CONSOLE_DIR_H

#endif //CONSOLE_CONSOLE_DIR_H
