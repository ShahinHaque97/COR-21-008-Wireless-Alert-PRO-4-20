/*
 * @file    main.c
 * @brief   main program file
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

#include "include/CAT24C04.h"
#include "include/console_dir.h"
#include "include/BSP.h"
/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/
/******************************* VARIABLES ******************************/
/*************************** PUBLIC FUNCTIONS ***************************/

void app_main(void)
{

    /* init - GPIO - MCP3421 - CAT24C04 */
    BSP_init();

    /* init terminal */
    console_init();

    /* list of commands to be executed */
    console_register_commands();

    /* to return to selection screen for new reply command */
    console_new_reply();

}