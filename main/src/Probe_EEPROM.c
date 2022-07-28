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
#define SIZEOF_CHECKSUM_BYTES 2
/******************************* VARIABLES ******************************/
/*************************** PUBLIC FUNCTIONS ***************************/

uint16_t compute_checksum(bsp_eeprom_contents_t in_eeprom) {
    uint16_t checksum = 0;
    for (uint16_t idx = 0; idx < BSP_I2C_EEPROM_PAGE_SIZE - SIZEOF_CHECKSUM_BYTES; idx++) {
        checksum += in_eeprom.contents[idx];
    }
    /*Compute the 2's Complement */
    checksum = (~checksum + 1);
    /*reverse endianness*/
    return (checksum >> 8) | ((checksum & 0xFF) << 8);
}

uint8_t eeprom_write_struct(){
    printf("---START EEPROM STRUCT TEST ROUTINE--- \n \n \n");

    bsp_probe_eeprom_420specificData_t probe_eeprom_specificData;
    //probe_eeprom_specificData.reserved;

    bsp_probe_i2c_eeprom_channelCalibration_t probe_eeprom_channelCalibration;
    //probe_eeprom_channelCalibration.gain;
    //probe_eeprom_channelCalibration.offset;

    bsp_eeprom_contents_t probe_eeprom_contents;

    probe_eeprom_contents.advancedStructure.key_marker                  = 0xEFBE;    /*2*/
    probe_eeprom_contents.advancedStructure.probe_type                  = 0x0103;    /*2*/
    probe_eeprom_contents.advancedStructure.eeprom_structure_version    = 0x00;      /*1*/
    probe_eeprom_contents.advancedStructure.probe_hw_version            = 0x00;      /*1*/
    probe_eeprom_contents.advancedStructure.year_of_manufacture         = 0x00;      /*1*/ //2022
    probe_eeprom_contents.advancedStructure.week_of_manufacture         = 0x00;      /*1*/ //Week 30 -  July 26 to Aug 1
    probe_eeprom_contents.advancedStructure.batch_number                = 0x00000000;/*4*/
    probe_eeprom_contents.advancedStructure.serial_number               = 0x00000000;/*4*/
    probe_eeprom_contents.advancedStructure.channel_count               = 0x01;      /*1*/

    //probe_eeprom_contents.advancedStructure.reserved_a;
    //probe_eeprom_contents.advancedStructure.channelCals
    probe_eeprom_contents.advancedStructure.cal_exp_date                = 0x00000000;
    probe_eeprom_contents.advancedStructure.cal_set_date                = 0x00000000;

    //probe_eeprom_contents.advancedStructure.signature;

    //probe_eeprom_contents.advancedStructure.reserved_b;
    //probe_eeprom_contents.advancedStructure.probe_specific_data.raw ;
    //probe_eeprom_contents.advancedStructure.probe_specific_data.probe_420_data;

    // probe_eeprom_contents.advancedStructure.reserved_c;

    probe_eeprom_contents.advancedStructure.checksum =compute_checksum(probe_eeprom_contents); // memory location 254


    do {
        /* write data from union to  */
        for(uint16_t address = 0; address < 256; address++)
        {

                if (false == CAT24C04_writeByte(address, probe_eeprom_contents.contents[address])) {
                    /* Failed to write to EEPROM book 1, cannot continue */
                    break;
                }
                vTaskDelay(50 / portTICK_PERIOD_MS);
                printf("EEPROM book 1 memory location: [%d / 255] \n", address);

                if (false == CAT24C04_writeByte((address + 0x0100), probe_eeprom_contents.contents[address])) {
                    /* Failed to write to EEPROM book 2, cannot continue */
                    break;
                }

                /* duplicate data to second EEPROM book */
                vTaskDelay(50 / portTICK_PERIOD_MS);
                printf("EEPROM book 2 memory location: [%d / 255] \n \n", address);



        }
    } while(false);
    printf("---END EEPROM STRUCT TEST ROUTINE--- \n \n \n");

return 0;
}

uint8_t read_entire_EEPROM()
{
    //uint32_t address = 0x00;
    uint8_t data;

    for(uint16_t address = 0; address < 512; address++)
    {
        if(false == CAT24C04_readByte(address, &data))
        {
            /* Failed to read the eeprom, cannot continue */
        }
        else {
            printf("Location: %d - 0x%04X     Value 0x%02X \n", address,address, data);
        }
    }



    return 0;
}





