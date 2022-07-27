/*
 * @file    Probe_EEPROM.c
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

/**************************** LIB INCLUDES ******************************/
/**************************** USER INCLUDES *****************************/
#include "../include/Probe_EEPROM.h"
/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/
/******************************* VARIABLES ******************************/
/*************************** PUBLIC FUNCTIONS ***************************/

uint8_t eeprom_write_struct(){
    printf("---START EEPROM STRUCT TEST ROUTINE--- \n \n \n");


    bsp_probe_eeprom_420specificData_t probe_eeprom_specificData;
    //probe_eeprom_specificData.reserved;

    bsp_probe_i2c_eeprom_channelCalibration_t probe_eeprom_channelCalibration;
    //probe_eeprom_channelCalibration.gain;
    //probe_eeprom_channelCalibration.offset;

    bsp_eeprom_contents_t probe_eeprom_contents;

    probe_eeprom_contents.advancedStructure.key_marker                  = 0x1111;               /*2*/
    probe_eeprom_contents.advancedStructure.probe_type                  = 0x2222;               /*2*/
    probe_eeprom_contents.advancedStructure.eeprom_structure_version    = 0x33;   /*1*/
    probe_eeprom_contents.advancedStructure.probe_hw_version            = 0x44;           /*1*/
    probe_eeprom_contents.advancedStructure.year_of_manufacture         = 0x55;        /*1*/  //2022
    probe_eeprom_contents.advancedStructure.week_of_manufacture         = 0x66;        /*1*/ //Week 30 -  July 26 to Aug 1
    probe_eeprom_contents.advancedStructure.batch_number                = 0x77777777;         /*4*/
    probe_eeprom_contents.advancedStructure.serial_number               = 0x88888888;        /*4*/
    probe_eeprom_contents.advancedStructure.channel_count               = 0x99;              /*1*/

    //probe_eeprom_contents.advancedStructure.reserved_a;
    //probe_eeprom_contents.advancedStructure.channelCals
    probe_eeprom_contents.advancedStructure.cal_exp_date                = 0x00;
    probe_eeprom_contents.advancedStructure.cal_set_date                = 0x0;

    //probe_eeprom_contents.advancedStructure.signature;

    //probe_eeprom_contents.advancedStructure.reserved_b;
    //probe_eeprom_contents.advancedStructure.probe_specific_data.raw ;
    //probe_eeprom_contents.advancedStructure.probe_specific_data.probe_420_data;

    // probe_eeprom_contents.advancedStructure.reserved_c;

    probe_eeprom_contents.advancedStructure.checksum =0x00; // memory location 254

    /* write data from union to  */
    for(uint16_t address = 0; address < 256; address++)
    {
        CAT24C04_writeByte(address,probe_eeprom_contents.contents[address]);

        vTaskDelay(50 / portTICK_PERIOD_MS);

        /* duplicate data to second EEPROM book */
        CAT24C04_writeByte((address + 0x0100),probe_eeprom_contents.contents[address]);
        vTaskDelay(50 / portTICK_PERIOD_MS);
        printf("data: [%d / 255] \n",address);
    }

    printf("---END EEPROM STRUCT TEST ROUTINE--- \n \n \n");

return 0;
}


