/*
 * @file    application.c
 * @brief   main functions for testing ADCs and EEPROMs
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
#include "../include/MS1100.h"
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

uint8_t low_output_test(int argc, char **argv)
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

uint8_t compare_results()
{
    float MS1100_current;
    float MCP3421_current;
    uint32_t MCP3421_raw_data;


    for(int i = 0; i < 3;i++)
    {
        reset_all_current_pins();
        if (i == 0)
        {
            set_pin(low_source, 1);
        } else if (i == 1)
        {
            set_pin(mid_source, 1);
        } else
        {
            set_pin(high_source, 1);
        }

        MCP3421_set_one_shot_read();

        MCP3421_raw_data = MCP3421_get_raw_data();
        MCP3421_current = (MCP3421_voltage(MCP3421_raw_data) / load_resistor);
        MS1100_current_calculation(&MS1100_current);

        printf("MCP3421 current value:   %2.4f mA   \n", MCP3421_current * 1000);
        printf("MS1100 current value:   %2.4f mA   \n", MS1100_current);

        float diff = 0;
        if (MS1100_current -  (MCP3421_current * 1000) >= 0)
        {
            diff =  MS1100_current -  (MCP3421_current * 1000);
        } else
        {
            diff = (MCP3421_current * 1000) - MS1100_current;
        }

        if (diff < 0.1)
        {
            printf("\033[0;32m");
            printf("passed");
            printf(" \033[0;37m");
        } else
        {
            printf("\033[0;31m");
            printf("failed");
            printf(" \033[0;37m");
        }

        printf("\n");
        printf("\n");

    }
return 0;
}

uint8_t mid_output_test(int argc, char **argv)
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

uint8_t high_output_test(int argc, char **argv)
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



esp_err_t MS1100_print_out()
{
    float current;
    /*  reset MS100 to default settings */
    //MS1100_general_call_reset();

    /*  set to single conversion mode   */

    set_pin(low_source, 0);
    set_pin(mid_source, 0);
    set_pin(high_source, 0);

    uint8_t temp_data[3];
    printf("-----------------------LOW CURRENT SOURCE ON--------------------- \n");

    set_pin(low_source, 1);
    int count =1;
    for(int i = 0; i < count; i++){

        MS1100_current_calculation(&current);
        printf("current:   %2.10f  \n", current);

    }
    set_pin(low_source, 0);

    printf("-----------------------MID CURRENT SOURCE ON--------------------- \n");
    set_pin(mid_source, 1);

    for(int i = 0; i < count; i++){
        MS1100_current_calculation(&current);
        printf("current:   %2.10f  \n", current);
    }
    set_pin(mid_source, 0);

    printf("-----------------------HIGH CURRENT SOURCE ON-------------------- \n");

    set_pin(high_source, 1);

    for(int i = 0; i < count; i++){
        MS1100_current_calculation(&current);
        printf("current:   %2.10f  \n", current);
    }
    set_pin(high_source, 0);

    return 0;
}

