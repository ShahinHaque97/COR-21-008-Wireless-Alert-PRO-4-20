/*
 * @file    MSS1100.c
 * @brief   MS1100 ADC file
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
#include "BSP/MS1100.h"
/******************************* DEFINES ********************************/
#define MAIN_I2C_READ_BIT 1
#define MAIN_I2C_WRITE_BIT 0
#define I2C_PORT  I2C_NUM_0
#define MS1100_VREF 2.048

/*Conversion factor for going from MS110 reading to the actual output voltage*/
#define MS1100_READING_TO_V_M 1.00540606909f  /*C of y = Mx+C*/
#define MS1100_READING_TO_V_C (-0.00541415699f) /*M of y = Mx+C*/

/*Conversion constants to go from Output voltage to loop current*/
#define VOLTAGE_TO_CURRENT_M 0.09187963768f /*M of y = Mx+C*/
#define VOLTAGE_TO_CURRENT_C 0.00154311594f /*C of y = Mx+C*/


/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/
/******************************* VARIABLES ******************************/
/*************************** PUBLIC FUNCTIONS ***************************/

esp_err_t esp_console_register_MS1100_read(void *function)
{
    const esp_console_cmd_t command = {
            .command = "MS1100_read",
            .help = "MS100 read configuration register ",
            .hint = NULL,
            .func = function,
    };
    return esp_console_cmd_register(&command);
}

esp_err_t esp_console_register_MS1100_read_config(void *function)
{
    const esp_console_cmd_t command = {
            .command = "MS1100_config",
            .help = "MS100 read configuration register ",
            .hint = NULL,
            .func = function,
    };
    return esp_console_cmd_register(&command);
}

uint8_t MS1100_display_config_register()
{
    uint8_t register_data[3];
    do{

        if(false == MS1100_read_registers(register_data))
        {
            /* Failed to read the ADC, cannot continue */
            break;
        }

        uint8_t config_register = register_data[2];
        printf("config reg :  0x%04X \n ", config_register);

    } while (false);
   return 0;
}

uint8_t MS1100_current_calculation(float *current_out)
{
    uint8_t register_data[3];
    bool retVal = false;
    float voltage;
   // float current;
    do {

        if(false == MS1100_read_registers(register_data))
        {
            /* Failed to read the ADC, cannot continue */
            break;
        }

        uint32_t raw_adc = ((register_data[0] << 8) + register_data[1]);

        /*Output code = ( 16384 * 2 * VREF ) / (𐤃 Vin ) */
        voltage =  (raw_adc * MS1100_VREF) / (16384.0f * 2.0f);
        *current_out = ((voltage - VOLTAGE_TO_CURRENT_C) / VOLTAGE_TO_CURRENT_M);

        retVal = true;

    }while(false);


    return retVal ? 0 : 1;
}

bool MS1100_read_registers(uint8_t *dataOut)
{
    bool retVal = false;

    if(ESP_OK == MS1100_read_to_slave(dataOut))
    {
        retVal = true;
    }

    return retVal;
}

esp_err_t MS1100_read_to_slave(uint8_t register_data[3])
{
    MS1100_setup_config_register();
    vTaskDelay(200 / portTICK_PERIOD_MS);

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MS1100_device_address<<1 | MAIN_I2C_READ_BIT), true);
    i2c_master_read(cmd, register_data, 3, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    esp_err_t  err = i2c_master_cmd_begin(I2C_PORT, cmd, 50 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return err;
}

esp_err_t MS1100_setup_config_register()
{
    /*Configuration register MSB first */
    uint8_t ST_BSY  = 1;
    //-- Bits 6 must be set to zero
    //-- Bits 5 must be set to zero
    uint8_t SC      = 1; //0 - continuous   1 - single
    uint8_t DR1     = 1;
    uint8_t DR0     = 1;
    uint8_t PGA1    = 0;
    uint8_t PGA0    = 0;

    /* reset data to be OR with new data */
    uint8_t data = 0x00;
    data = (    (ST_BSY << 7)   |   (SC << 4)   |    (DR1 << 3)  |  (DR0 << 2)  |   (PGA1 << 0)  |  (PGA0 << 0));

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MS1100_device_address<<1 | MAIN_I2C_WRITE_BIT), true);

    i2c_master_write_byte(cmd, (data), I2C_MASTER_LAST_NACK);

    i2c_master_stop(cmd);
    esp_err_t  err = i2c_master_cmd_begin(I2C_PORT, cmd, 50 / portTICK_RATE_MS);

    i2c_cmd_link_delete(cmd);


return err;
}

esp_err_t MS1100_general_call_reset()
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (0x00), I2C_MASTER_ACK);

    i2c_master_write_byte(cmd, (0x06), I2C_MASTER_ACK);
    i2c_master_stop(cmd);
    esp_err_t  err = i2c_master_cmd_begin(I2C_PORT, cmd, 50 / portTICK_RATE_MS);

    i2c_cmd_link_delete(cmd);
    return err;
}


