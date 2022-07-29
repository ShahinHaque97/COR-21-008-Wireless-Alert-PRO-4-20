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
#include "Middleware/Probe_EEPROM.h"
/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
typedef struct {
    struct arg_int *year_of_manufacture;
    struct arg_int *week_of_manufacture;
    struct arg_int *batch_number;
    struct arg_int *serial_number;
   // struct arg_int *gain;
   // struct arg_int *offset;


    struct arg_end *end;
} bsp_eeprom_data_in;


/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/
#define SIZEOF_CHECKSUM_BYTES 2
/******************************* VARIABLES ******************************/
bsp_eeprom_data_in eeprom_struct_test;
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

uint8_t read_entire_EEPROM()
{
    uint8_t data;
    uint8_t contents[256];

    /* save EEPROM data into local array */
    for(uint16_t address = 0; address < 256; address++)
    {
        if(false == CAT24C04_readByte(address, &data))
        {
            /* Failed to read the eeprom, cannot continue */
        }
        else {
            contents[address] = data;
        }
    }

    printf("key marker:                 %X%X \n",     contents[1],contents[0] );
    printf("probe_type:                 %X%X \n",     contents[3],contents[2] );
    printf("eeprom_structure_version:   %X \n",       contents[4]);
    printf("probe_hw_version:           %X \n",       contents[5]);
    printf("year_of_manufacture:        %X \n",       contents[6]);
    printf("week_of_manufacture:        %X \n",       contents[7]);
    printf("batch_number:               %X%X%X%X \n", contents[11],contents[10],contents[9],contents[8]);
    printf("serial_number:              %X%X%X%X \n", contents[15],contents[14],contents[13],contents[12]);
    printf("channel_count:              %X \n",       contents[16]);
    printf("reserved a:                 %X%X%X \n",   contents[19],contents[18],contents[17]);

    printf("1 - calibration gain:       %X%X%X%X \n", contents[23],contents[22],contents[21],contents[20]);
    printf("1 - calibration offset:     %X%X%X%X \n", contents[27],contents[26],contents[25],contents[24]);

    printf("2 - calibration gain:       %X%X%X%X \n", contents[31],contents[30],contents[29],contents[28]);
    printf("2 - calibration offset:     %X%X%X%X \n", contents[35],contents[34],contents[33],contents[32]);

    printf("3 - calibration gain:       %X%X%X%X \n", contents[39],contents[38],contents[37],contents[36]);
    printf("3 - calibration offset:     %X%X%X%X \n", contents[43],contents[42],contents[41],contents[40]);

    printf("4 - calibration gain:       %X%X%X%X \n", contents[47],contents[46],contents[45],contents[44]);
    printf("4 - calibration offset:     %X%X%X%X \n", contents[51],contents[50],contents[49],contents[48]);

    printf("5 - calibration gain:       %X%X%X%X \n", contents[55],contents[54],contents[53],contents[52]);
    printf("5 - calibration offset:     %X%X%X%X \n", contents[59],contents[58],contents[57],contents[56]);

    printf("6 - calibration gain:       %X%X%X%X \n", contents[63],contents[62],contents[61],contents[60]);
    printf("6 - calibration offset:     %X%X%X%X \n", contents[67],contents[66],contents[65],contents[64]);

    printf("7 - calibration gain:       %X%X%X%X\n",  contents[71],contents[70],contents[69],contents[68]);
    printf("7 - calibration offset:     %X%X%X%X \n", contents[75],contents[74],contents[73],contents[72]);

    printf("8 - calibration gain:       %X%X%X%X\n",  contents[79],contents[78],contents[77],contents[76]);
    printf("8 - calibration offset:     %X%X%X%X \n", contents[83],contents[82],contents[81],contents[80]);

    printf("cal_set_date:               %X%X%X%X \n", contents[87],contents[86],contents[85],contents[84]);
    printf("cal_exp_date:               %X%X%X%X \n", contents[91],contents[90],contents[89],contents[88]);

    printf("Signature:                  ");
    for (int i = (91 +32); i > 91; i--)
    {
        printf("%X",contents[i]);
    }
    printf("\n");

    printf("reserved_b:                 %X%X%X%X \n", contents[127],contents[126],contents[125],contents[124]);

    printf("probe_specific_data:        ");
    for (int i = (127+80); i > 127; i--)
    {
        printf("%X",contents[i]);
    }
    printf("\n");

    printf("reserved_c:                 ");
    for (int i = 207+46; i > 207; i--)
    {
        printf("%X",contents[i]);
    }
    printf("\n");

    printf("checksum:                   %X%X \n", contents[254],contents[255] );
    return 0;
}

uint8_t EEPROM_write_console_data_test(int argc, char **argv) {

    bool retVal = false;
    int nerrors = arg_parse(argc, argv, (void **)&eeprom_struct_test);

    uint8_t year_of_manufacture;
    uint8_t week_of_manufacture;
    uint32_t batch_number;
    uint32_t serial_number;
    float gain;
    float offset;


    do{
        if (nerrors != 0) {
            arg_print_errors(stderr, eeprom_struct_test.end, argv[0]);
            return 0;
        }

        year_of_manufacture = eeprom_struct_test.year_of_manufacture->ival[0];
        week_of_manufacture = eeprom_struct_test.week_of_manufacture->ival[0];
        batch_number = eeprom_struct_test.batch_number->ival[0];
        serial_number = eeprom_struct_test.serial_number->ival[0];
        // gain = eeprom_struct_test.gain->ival[0];
        //offset = eeprom_struct_test.offset->ival[0];

        bsp_probe_eeprom_420specificData_t probe_eeprom_specificData;
        //probe_eeprom_specificData.reserved;

        bsp_probe_i2c_eeprom_channelCalibration_t probe_eeprom_channelCalibration;
        probe_eeprom_channelCalibration.gain = 0;
        probe_eeprom_channelCalibration.offset = 0;

        bsp_eeprom_contents_t probe_eeprom_contents;
        probe_eeprom_contents.advancedStructure.key_marker                  = 0xEFBE;    /*2*/
        probe_eeprom_contents.advancedStructure.probe_type                  = 0x0103;    /*2*/
        probe_eeprom_contents.advancedStructure.eeprom_structure_version    = 0x00;      /*1*/
        probe_eeprom_contents.advancedStructure.probe_hw_version            = 0x00;      /*1*/
        probe_eeprom_contents.advancedStructure.year_of_manufacture         = year_of_manufacture;      /*1*/
        probe_eeprom_contents.advancedStructure.week_of_manufacture         = week_of_manufacture;      /*1*/
        probe_eeprom_contents.advancedStructure.batch_number                = batch_number;/*4*/
        probe_eeprom_contents.advancedStructure.serial_number               = serial_number;/*4*/
        probe_eeprom_contents.advancedStructure.channel_count               = 0x01;      /*1*/
        //probe_eeprom_contents.advancedStructure.reserved_a;
        //probe_eeprom_contents.advancedStructure.channelCals
        probe_eeprom_contents.advancedStructure.cal_set_date                = 0xAABBCCDD;
        probe_eeprom_contents.advancedStructure.cal_exp_date                = 0xEEFF1122;

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
    } while(false);
    return 0;
}

esp_err_t esp_console_register_EEPROM_write_console_data()
{

    eeprom_struct_test.year_of_manufacture = arg_int1("y", "year", "<int>", "the year of manufacture");
    eeprom_struct_test.week_of_manufacture = arg_int1("w", "week", "<int>", "the week of manufacture");
    eeprom_struct_test.batch_number = arg_int1("b", "batch", "<int>", "the batch number");
    eeprom_struct_test.serial_number = arg_int1("s", "serial", "<int>", "the serial number");

  //  eeprom_struct_test.gain = arg_int1("g", "gain", "<int>", "the calibration gain (M) in MX+C");
  //  eeprom_struct_test.offset = arg_int1("o", "offset", "<int>", "the calibration offset (C) in MX+C");

    eeprom_struct_test.end = arg_end(0);

    const esp_console_cmd_t command = {
            .command = "EEPROM_write_test",
            .help = "test function to write EEPROM data",
            .hint = NULL,
            .func = (esp_console_cmd_func_t)&EEPROM_write_console_data_test,
            .argtable = &eeprom_struct_test
    };
    return esp_console_cmd_register(&command);
}









