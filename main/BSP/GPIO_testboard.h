/*
 * @file    GPIO_testboard.h
 * @brief   header file to for GPIO_testboard.c
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

#ifndef CONSOLE_GPIO_TESTBOARD_H
#define CONSOLE_GPIO_TESTBOARD_H
/**************************** LIB INCLUDES ******************************/
/**************************** USER INCLUDES *****************************/
/******************************* DEFINES ********************************/
#define high_source     GPIO_NUM_10
#define mid_source      GPIO_NUM_4
#define low_source      GPIO_NUM_5
#define i2c_probe_PWR   GPIO_NUM_6
/******************************** ENUMS *********************************/
/****************************** TYPEDEFS ********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
void set_pin(int pin_number, int state);
void configure_pin_output(int pin_number);
void gpio_init();
void reset_all_current_pins();
/******************************* GLOBALS ********************************/
/*        Globals are to be avoided unless justified and documented */
/************************************************************************/

#endif //CONSOLE_GPIO_TESTBOARD_H
