/*
 * @file    GPIO_testboard.c
 * @brief   GPIO file for turning current source pins
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
#include "include/GPIO_testboard.h"
#include "driver/GPIO_testboard.h"
/**************************** USER INCLUDES *****************************/
/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/
/******************************* VARIABLES ******************************/
/*************************** PUBLIC FUNCTIONS ***************************/

/* Set the GPIO level according to the state (LOW or HIGH)*/
void set_pin(int pin_number, int state)
{
    gpio_set_level(pin_number, state);
}

void reset_all_current_pins()
{
    gpio_set_level(low_source, 0);
    gpio_set_level(mid_source, 0);
    gpio_set_level(high_source, 0);
}

void configure_pin_output(int pin_number)
{
    gpio_reset_pin(pin_number);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(pin_number, GPIO_MODE_OUTPUT);
}

void gpio_init(){

    /* set current source pins as output */
    configure_pin_output(low_source);
    configure_pin_output(mid_source);
    configure_pin_output(high_source);
    configure_pin_output(i2c_probe_PWR);

    /* turn on power for smart probe  */
    set_pin(i2c_probe_PWR,0);
}








