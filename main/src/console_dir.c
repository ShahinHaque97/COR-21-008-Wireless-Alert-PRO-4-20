/*
 * @file    console_dir.C
 * @brief   file for console commands
 * @version 26/07/2022
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
#include "include/console_dir.h"
/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/
esp_console_repl_t *repl = NULL;
esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
esp_console_dev_uart_config_t uart_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();
/******************************* VARIABLES ******************************/
/*************************** PUBLIC FUNCTIONS ***************************/

void console_init()
{
    repl_config.max_cmdline_length = CONFIG_CONSOLE_MAX_COMMAND_LINE_LENGTH;
}

void console_new_reply()
{

    ESP_ERROR_CHECK(esp_console_new_repl_uart(&uart_config, &repl_config, &repl));
    ESP_ERROR_CHECK(esp_console_start_repl(repl));
}

void console_register_commands(){

    esp_console_register_help_command();
    esp_console_register_low_current_test(low_output_test);
    esp_console_register_mid_current_test(mid_output_test);
    esp_console_register_high_current_test(high_output_test);
    esp_console_register_i2c_scanner(i2c_scanner);
    CAT24C04_console_single_read();
    CAT24C04_console_single_write();
    CAT24C04_console_single_page_write();
    esp_console_register_clear();

    esp_console_register_MS1100_read(MS1100_print_out);
    esp_console_register_MS1100_read_config(MS1100_display_config_register);
    esp_console_register_compare_ADC(compare_results);
    esp_console_register_EEPROM_datawrite_test(eeprom_write_struct);
    esp_console_register_EEPROM_read_all(read_entire_EEPROM);

}


esp_err_t esp_console_register_EEPROM_read_all(void *function )
{
    const esp_console_cmd_t command = {
            .command = "read_all",
            .help = "test function to write EEPROM data",
            .hint = NULL,
            .func = function,
    };
    return esp_console_cmd_register(&command);
}



esp_err_t esp_console_register_EEPROM_datawrite_test(void *function )
{
    const esp_console_cmd_t command = {
            .command = "test",
            .help = "test function to write EEPROM data",
            .hint = NULL,
            .func = function,
    };
    return esp_console_cmd_register(&command);
}



esp_err_t esp_console_register_compare_ADC(void *function )
{
    const esp_console_cmd_t command = {
            .command = "ADC",
            .help = "compare the two ADC results",
            .hint = NULL,
            .func = function,
    };
    return esp_console_cmd_register(&command);
}




esp_err_t esp_console_register_clear(void)
{
    const esp_console_cmd_t command = {
            .command = "clear",
            .help = "clear screen",
            .hint = NULL,
            .func = &clear_screen,
    };
    return esp_console_cmd_register(&command);
}

esp_err_t esp_console_register_i2c_scanner(void *function )
{
    const esp_console_cmd_t command = {
            .command = "i2c",
            .help = "scan all i2c devices on the i2c bus",
            .hint = NULL,
            .func = function,
    };
    return esp_console_cmd_register(&command);
}

esp_err_t esp_console_register_low_current_test(void *function)
{
    const esp_console_cmd_t command = {
            .command = "low",
            .help = "set low output high to turn on 4.3mA current source",
            .hint = NULL,
            .func = function,
    };
    return esp_console_cmd_register(&command);
}

esp_err_t esp_console_register_mid_current_test(void *function)
{
    const esp_console_cmd_t command = {
            .command = "mid",
            .help = "set mid output high to turn on 13.3mA current source",
            .hint = NULL,
            .func = function,
    };
    return esp_console_cmd_register(&command);
}

esp_err_t esp_console_register_high_current_test(void *function)
{
    const esp_console_cmd_t command = {
            .command = "high",
            .help = "set high output high to turn on 20mA current source",
            .hint = NULL,
            .func = function,
    };
    return esp_console_cmd_register(&command);
}





static int clear_screen()
{
    /* code to clear terminal */
    printf("\033\143");
    return 0;
}


