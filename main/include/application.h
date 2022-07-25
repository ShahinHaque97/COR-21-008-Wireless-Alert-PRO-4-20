/*
 * @file    application.h
 * @brief   X
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

#ifndef CONSOLE_APPLICATION_H
#define CONSOLE_APPLICATION_H
/**************************** LIB INCLUDES ******************************/
/**************************** USER INCLUDES *****************************/
#include "include/MCP3421.h"
#include "include/CAT24C04.h"
#include "include/GPIO_testboard.h"
/******************************* DEFINES ********************************/

/******************************** ENUMS *********************************/
/****************************** TYPEDEFS ********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
float MCP3421_voltage(uint32_t data_bit_shifted);
int low_output_test(int argc, char **argv);
int mid_output_test(int argc, char **argv);
int high_output_test(int argc, char **argv);
/******************************* GLOBALS ********************************/
/*        Globals are to be avoided unless justified and documented */
/************************************************************************/

#endif //CONSOLE_APPLICATION_H
