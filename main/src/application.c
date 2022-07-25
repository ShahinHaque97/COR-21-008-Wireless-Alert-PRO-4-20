/*
 * @file    application.c
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

/**************************** LIB INCLUDES ******************************/
#include <stdio.h>
/**************************** USER INCLUDES *****************************/
#include "include/application.h"
#include "include/MCP3421.h"
/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/
const float load_resistor = 47.0f+47.0f;
/******************************* VARIABLES ******************************/
/*************************** PUBLIC FUNCTIONS ***************************/






float MCP3421_voltage(uint32_t data_bit_shifted)
{
    float voltage;
    if (data_bit_shifted >> 17 )
    {
        //printf("\n");
        //printf("Negative\n");
        uint32_t twos_compliment = (0xFFFC0000 | data_bit_shifted);

        twos_compliment = 0-twos_compliment + 1;
        voltage = twos_compliment / 64000.0;
        //printf("voltage:    %2.2f V\n", voltage);

        //printf("\n");
    }
    else
    {
        voltage = data_bit_shifted / 64000.0;
        // printf("\n");
        // printf("Positive\n");
        // printf("data_bit_shifted:    0x%08x\n", data_bit_shifted);
    } //if statement

    return voltage;
}

//-------------

int low_output_test(int argc, char **argv)
{
    printf("low source has been set  - Value we are looking for: 4.3mA \n");
    set_pin(low_source, 1);

    MCP3421_set_one_shot_read();
    uint32_t data = MCP3421_get_raw_data();
    float voltage = MCP3421_voltage(data);

    printf("Voltage:    %2.2f V\n", voltage);
    printf("load resistor value: %2.2f \n", load_resistor);
    printf("Current %2.3f mA\n", (voltage / load_resistor) * 1000.0f);
    printf("\n");

    if ((voltage >= 0.39) & (voltage <= 0.41))
    {
        printf("Correct voltage is being displayed, and thus correct current input\n");
        printf("\n");
    } else
    {
        printf("INCORRECT VOLTAGE reading \n");
        printf("\n");
    }
    set_pin(low_source, 0);
    return 0;
}

int mid_output_test(int argc, char **argv)
{
    printf("mid source has been set  - Value we are looking for: 13.3mA \n");
    set_pin(mid_source, 1);

    MCP3421_set_one_shot_read();
    uint32_t data = MCP3421_get_raw_data();
    float voltage = MCP3421_voltage(data);
    printf("load resistor value: %2.2f \n", load_resistor);
    printf("Voltage:    %2.2f V\n", voltage);
    printf("Current %2.3f mA\n", (voltage / load_resistor) * 1000.0f);
    printf("\n");

    if ((voltage >= 1.24) & (voltage <= 1.26))
    {
        printf("Correct voltage is being displayed, and thus correct current input \n");
        printf("\n");
    } else
    {
        printf("INCORRECT VOLTAGE reading \n");
        printf("\n");
    }
    set_pin(mid_source, 0);
    return 0;
}

int high_output_test(int argc, char **argv)
{
    printf("high source has been set  - Value we are looking for: 20mA \n");
    set_pin(high_source, 1);

    MCP3421_set_one_shot_read();
    uint32_t data = MCP3421_get_raw_data();
    float voltage = MCP3421_voltage(data);
    printf("load resistor value: %2.2f \n", load_resistor);
    printf("Voltage:    %2.2f V\n", voltage);
    printf("Current %2.3f mA\n", (voltage / load_resistor) * 1000.0f);
    printf("\n");

    if ((voltage >= 1.85) & (voltage <= 1.9))
    {
        printf("Correct voltage is being displayed, and thus correct current input \n");
        printf("\n");
    } else
    {
        printf("INCORRECT VOLTAGE reading \n");
        printf("\n");
    }
    set_pin(high_source, 0);
    return 0;
}


