/*
 * @file    CAT24C04.c
 * @brief   interfacing with the i2c probe (currently with just an EEPROM on it)
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
/**************************** USER INCLUDES *****************************/
#include "include/CAT24C04.h"
#include <argtable3/argtable3.h>
#include <esp_log.h>
#include <esp_console.h>
/******************************* DEFINES ********************************/
#define CAT24C04_SIZE 512
/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
typedef struct {
    struct arg_int *address;
    struct arg_int *data;
    struct arg_end *end;
} cstb_writeArgs_t;

typedef struct {
    struct arg_int *address;
    struct arg_end *end;
} cstb_readArgs_t;
/************************** FUNCTION PROTOTYPES *************************/
bool CAT24C04_readByte(uint16_t address, uint8_t *dataOut);
bool CAT24C04_writeByte(uint16_t address, uint8_t dataIn);
bool CAT24C04_write_16byte_page(uint16_t address, uint8_t dataIn[], uint8_t len);
/******************************* CONSTANTS ******************************/
static const char *TAG = "I2C_PROBE";
/******************************* VARIABLES ******************************/
cstb_writeArgs_t cstb_writeArgsTable;
cstb_writeArgs_t cstb_writeArgsTable_page;
cstb_readArgs_t cstb_readArgsTable;
/*************************** PUBLIC FUNCTIONS ***************************/

esp_err_t CAT24C04_initialize(void)
{
    i2c_driver_install(i2c_port, I2C_MODE_MASTER, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
    i2c_config_t conf = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = i2c_gpio_sda,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_io_num = i2c_gpio_scl,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master.clk_speed = i2c_frequency,
            // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
    };
    return i2c_param_config(i2c_port, &conf);
}

esp_err_t CAT24C04_selective_read_to_slave(uint8_t reg_addr, uint8_t *data, uint8_t register_location)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (reg_addr << 1) | MAIN_I2C_WRITE_BIT, true);
    i2c_master_write_byte(cmd, register_location, true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (reg_addr << 1) | MAIN_I2C_READ_BIT, true);

    i2c_master_read(cmd, data, 1, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    esp_err_t  err = i2c_master_cmd_begin(i2c_port, cmd, 50 / portTICK_RATE_MS);

    i2c_cmd_link_delete(cmd);


    return err;
}

esp_err_t CAT24C04_selective_write_to_slave(uint8_t reg_addr, uint8_t register_location, uint8_t data )
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (reg_addr << 1) | MAIN_I2C_WRITE_BIT, true);
    i2c_master_write_byte(cmd, register_location, true);

    i2c_master_write_byte(cmd, data, true);
    i2c_master_stop(cmd);

    esp_err_t  err = i2c_master_cmd_begin(i2c_port, cmd, 50 / portTICK_RATE_MS);

    i2c_cmd_link_delete(cmd);


    return err;
}

esp_err_t CAT24C04_page_write_to_slave(uint8_t reg_addr, uint8_t register_location, uint8_t data[],uint8_t len )
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (reg_addr << 1) | MAIN_I2C_WRITE_BIT, true);
    i2c_master_write_byte(cmd, register_location, true);

    for (int i = 0; i < len;i++ )
    {
        i2c_master_write_byte(cmd, data[i], true);
    }


    i2c_master_stop(cmd);
    esp_err_t  err = i2c_master_cmd_begin(i2c_port, cmd, 50 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return err;
}


uint8_t CAT24C04_read_printout(int argc, char **argv)
{
    bool retVal = false;
    uint32_t address;
    uint8_t data;
    int32_t nerrors = arg_parse(argc, argv, (void **)&cstb_readArgsTable);

    do {
        if (nerrors != 0)
        {
            /* Arguments failed to parse, cannot continue */
            arg_print_errors(stderr, cstb_readArgsTable.end, argv[0]);
            break;
        }

        address = cstb_readArgsTable.address->ival[0];

        if(false == CAT24C04_readByte(address, &data))
        {
            /* Failed to read the eeprom, cannot continue */
            break;
        }

        /* Read succeeded, print result */
        printf("Location: 0x%04X     Value 0x%02X \n", address, data);
        retVal = true;

    } while(false);


    return retVal ? 0 : 1;


    /*
    int temp_address = cstb_readArgsTable.address->ival[0];

    uint8_t  selective_data[1];
    //int8_t register_location = 6;

    CAT24C04_selective_read_to_slave(probe_address,selective_data, cstb_readArgsTable.address->ival[0]);
    printf("Location: %d     Value %x \n", cstb_readArgsTable.address->ival[0], selective_data[0]);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    return selective_data[0];*/
}

uint8_t CAT24C04_write_printout(int argc, char **argv)
{
    bool retVal = false;
    int book = 0;
    int address;
    int data_in;
    int nerrors = arg_parse(argc, argv, (void **)&cstb_writeArgsTable);

    do{

        if (nerrors != 0) {
            arg_print_errors(stderr, cstb_writeArgsTable.end, argv[0]);
            return 0;
        }
        address = cstb_writeArgsTable.address->ival[0];
        data_in = cstb_writeArgsTable.data->ival[0];


        if(false == CAT24C04_writeByte(address, data_in))
        {
            /* Failed to read the eeprom, cannot continue */
            break;
        }

        printf("Location: 0x%04X     Value 0x%02X \n",address,data_in);
        printf("\n");
        retVal = true;
    } while(false);


return retVal ? 0 : 1;
}

uint8_t CAT24C04_pageWrite_printout(int argc, char **argv)
{
    bool retVal = false;
    uint8_t address;
    uint8_t nerrors = arg_parse(argc, argv, (void **)&cstb_writeArgsTable_page);

    do {

        if (nerrors != 0) {
            arg_print_errors(stderr, cstb_writeArgsTable_page.end, argv[0]);
            return 0;
        }

        address = cstb_writeArgsTable_page.address->ival[0];
        uint8_t len = cstb_writeArgsTable_page.data->count;

        uint8_t temp[16];



        for (uint8_t idx = 0; idx < len; idx++) {
            temp[idx] = cstb_writeArgsTable_page.data->ival[idx];
        }

        if(false ==  CAT24C04_write_16byte_page(address, temp, len))
        {
            break;
        }

        for (uint8_t idx = 0; idx < len; idx++) {
            printf("Location: 0x%04X     Value 0x%02X \n", cstb_writeArgsTable_page.address->ival[0]+ idx,cstb_writeArgsTable_page.data->ival[idx]);
        }
        retVal = true;


    } while(false);
    return retVal ? 0 : 1;
}


/*  interface with EEPROM */
bool CAT24C04_write_16byte_page(uint16_t address, uint8_t dataIn[], uint8_t len)
{
    bool retVal = false;
    /* EEPROM is organised into 2 "books" of 2kb so when addressing values
     * from over the 1st 2k, the address is incremented */
    uint8_t book = 0;

    do{
        /* check the input address doesn't exceed the max */
        if(address >= CAT24C04_SIZE)
        {
            /* Address is too large (511), cannot continue */
            break;
        }


        /* if the address is more than 255, it has wrapped onto the seconds page */
        if(address >= 0xFF)
        {
            /* move to next book and remove 1 book worth of address index */
            book = 1;
            address -= 0xFF;
        }

        if(ESP_OK == CAT24C04_page_write_to_slave(probe_address + book, address, dataIn,len ))
        {
            retVal = true;
        }

    }while (false);

    return retVal;
}

bool CAT24C04_writeByte(uint16_t address, uint8_t dataIn)
{
    bool retVal = false;
    /* EEPROM is organised into 2 "books" of 2kb so when addressing values
     * from over the 1st 2k, the address is incremented */
    uint8_t book = 0;

    do{
        /* check the input address doesn't exceed the max */
        if(address >= CAT24C04_SIZE)
        {
            /* Address is too large (511), cannot continue */
            break;
        }


        /* if the address is more than 255, it has wrapped onto the seconds page */
        if(address >= 0xFF)
        {
            /* move to next book and remove 1 book worth of address index */
            book = 1;
            address -= 0xFF;
        }

        if(ESP_OK == CAT24C04_selective_write_to_slave(probe_address + book,address, dataIn))
        {
            retVal = true;
        }

    }while (false);

    return retVal;
}

bool CAT24C04_readByte(uint16_t address, uint8_t *dataOut)
{

    bool retVal = false;
    uint8_t data;
    /* EEPROM is organised into 2 "books" of 2kb so when addressing values
     * from over the 1st 2k, the address is incremented */
    uint8_t book = 0;
    do{

        if(address >= CAT24C04_SIZE)
        {
            /* Address is too large (511), cannot continue */
            break;
        }

        /* if the address is more than 255, it has wrapped onto the seconds page */
        if(address >= 0xFF)
        {
            /* move to next book and remove 1 book worth of address index */
            book = 1;
            address -= 0xFF;
        }

        if(ESP_OK == CAT24C04_selective_read_to_slave(probe_address + book, &data, address))
        {
            if(dataOut != NULL)
            {
                dataOut[0] = data;
                retVal = true;
            }
        }

    }  while (false);

    return retVal;
}

/*  console procedures */
esp_err_t CAT24C04_console_single_write(void)
{
    cstb_writeArgsTable.address = arg_int1("a", "addr", "<int>", "the address to write to");
    cstb_writeArgsTable.data = arg_intn("d", "data", "<int>", 1, 8, "the data to be written");
    cstb_writeArgsTable.end = arg_end(0);

    const esp_console_cmd_t command = {
            .command = "write",
            .help = "Write a single register from the EEPROM",
            .hint = NULL,
            .func = (esp_console_cmd_func_t) &CAT24C04_write_printout,
            .argtable = &cstb_writeArgsTable
    };
    return esp_console_cmd_register(&command);
}

esp_err_t CAT24C04_console_single_page_write(void)
{
    cstb_writeArgsTable_page.address = arg_int1("a", "addr", "<int>", "the address to write to");
    cstb_writeArgsTable_page.data = arg_intn("d", "data", "<int>", 1, 16, "the data to be written");
    cstb_writeArgsTable_page.end = arg_end(0);

    const esp_console_cmd_t command = {
            .command = "write_page",
            .help = "write multiple values to the register",
            .hint = NULL,
            .func = (esp_console_cmd_func_t) &CAT24C04_pageWrite_printout,
            .argtable = &cstb_writeArgsTable_page
    };
    return esp_console_cmd_register(&command);



}

esp_err_t CAT24C04_console_single_read(void)
{
    cstb_readArgsTable.address = arg_int1("a", "addr", "<int>", "the address to read from");
    cstb_readArgsTable.end = arg_end(0);

    const esp_console_cmd_t command = {
            .command = "read",
            .help = "Read a single register from the EEPROM",
            .hint = NULL,
            .func = (esp_console_cmd_func_t) &CAT24C04_read_printout,
            .argtable = & cstb_readArgsTable

    };
    return esp_console_cmd_register(&command);
}