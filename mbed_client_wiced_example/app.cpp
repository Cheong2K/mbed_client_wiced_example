/*
 * Copyright 2016, RedBear
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of RedBear;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

/** @file
 *
 * mbed-client example
 *
 * This application demonstrates how to use the WICED GPIO API
 * to toggle LEDs and read button states
 *
 * Features demonstrated
 *  - GPIO API
 *
 */

#include "wiced.h"

#include "mbed-client/m2minterfacefactory.h"
#include "mbed-client/m2mdevice.h"
#include "mbed-client/m2minterfaceobserver.h"
#include "mbed-client/m2minterface.h"
#include "mbed-client/m2mobject.h"
#include "mbed-client/m2mobjectinstance.h"
#include "mbed-client/m2mresource.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *               Static Function Declarations
 ******************************************************/

/******************************************************
 *               Variable Definitions
 ******************************************************/

#if 0
// These are example resource values for the Device Object
struct MbedClientDevice device = {
    "Manufacturer_String",      // Manufacturer
    "Type_String",              // Type
    "ModelNumber_String",       // ModelNumber
    "SerialNumber_String"       // SerialNumber
};

MbedClient mbed_client(device);
#endif

/******************************************************
 *               Function Definitions
 ******************************************************/

void application_start( )
{
    wiced_bool_t led1 = WICED_FALSE;
    wiced_bool_t button1_pressed;

    /* Initialise the WICED device */
    wiced_init();

//mbed_client.create_interface();

    WPRINT_APP_INFO( ( "The RGB LEDs are flashing. Holding a button will force the corresponding LED on.\n" ) );

    while ( 1 )
    {
        /* Read the state of Button 1 */
        button1_pressed = wiced_gpio_input_get( BTN1 ) ? WICED_FALSE : WICED_TRUE;  /* The button has inverse logic */

        if ( button1_pressed == WICED_TRUE )
        {
            /* Turn red LED on and turn green LED off */
            wiced_gpio_output_low( LED_R );
            wiced_gpio_output_high( LED_G );
            wiced_gpio_output_high( LED_B );
        }
        else
        {
            /* Turn red LED off and toggle green led */
            wiced_gpio_output_high( LED_R );
            if ( led1 == WICED_TRUE )
            {
                wiced_gpio_output_low( LED_B );
                wiced_gpio_output_high( LED_G );
                led1 = WICED_FALSE;
            }
            else
            {
                wiced_gpio_output_high( LED_B );
                wiced_gpio_output_low( LED_G );
                led1 = WICED_TRUE;
            }
        }

        wiced_rtos_delay_milliseconds( 300 );
    }
}

#if defined(__cplusplus)
}
#endif
