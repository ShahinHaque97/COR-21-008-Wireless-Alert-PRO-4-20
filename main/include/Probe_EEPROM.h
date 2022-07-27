/*
 * @file    Probe_EEPROM.h
 * @brief   X
 * @version 27/07/2022
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

#ifndef CONSOLE_PROBE_EEPROM_H
#define CONSOLE_PROBE_EEPROM_H
/**************************** LIB INCLUDES ******************************/
#include <stdint.h>
#include <stdio.h>
/**************************** USER INCLUDES *****************************/
#include "include/CAT24C04.h"
/******************************* DEFINES ********************************/
#define BSP_I2C_EEPROM_PAGE_SIZE 256
#define BSP_EEPROM_SIZE_OF_CAL_SIGNATURE 32
/******************************** ENUMS *********************************/
/****************************** TYPEDEFS ********************************/
typedef struct {
    uint8_t reserved[80];                       /*80*/
} bsp_probe_eeprom_420specificData_t;

typedef struct {
    float gain;                                 /*4*/
    float offset;                               /*4*/
} bsp_probe_i2c_eeprom_channelCalibration_t;

typedef union {
    uint8_t contents[BSP_I2C_EEPROM_PAGE_SIZE];                     /*256 Bytes*/
    struct {
        uint16_t key_marker;                                        /*2*/
        uint16_t probe_type;                                        /*2*/
        uint8_t eeprom_structure_version;                           /*1*/
        uint8_t probe_hw_version;                                   /*1*/
        uint8_t year_of_manufacture;                                /*1*/
        uint8_t week_of_manufacture;                                /*1*/
        uint32_t batch_number;                                      /*4*/
        uint32_t serial_number;                                     /*4*/
        uint8_t channel_count;                                      /*1*/
        uint8_t reserved_a[3];                                      /*3*/
        bsp_probe_i2c_eeprom_channelCalibration_t channelCals[8];   /*64*/
        uint32_t cal_set_date;                                      /*4*/
        uint32_t cal_exp_date;                                      /*4*/
        char signature[BSP_EEPROM_SIZE_OF_CAL_SIGNATURE];           /*32*/
        uint8_t reserved_b[4];                                      /*4*/
        union {
            uint8_t raw[80];                                        /*80*/
            bsp_probe_eeprom_420specificData_t probe_420_data;
        } probe_specific_data;                                      /*80*/
        uint8_t reserved_c[46];                                     /*46*/
        uint16_t checksum;                                          /*2*/
    } advancedStructure;
} bsp_eeprom_contents_t;





/***************************** STRUCTURES *******************************/

/************************** FUNCTION PROTOTYPES *************************/
uint8_t eeprom_write_struct();
/******************************* GLOBALS ********************************/
/*        Globals are to be avoided unless justified and documented */
/************************************************************************/

#endif //CONSOLE_PROBE_EEPROM_H
