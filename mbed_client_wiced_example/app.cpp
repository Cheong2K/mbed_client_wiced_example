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
#include "simpleclient.h"

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

static wiced_thread_t unregister_thread;
static wiced_thread_t observation_thread;
static wiced_thread_t update_register_thread;

// These are example resource values for the Device Object
struct MbedClientDevice device = {
    "Manufacturer_String",      // Manufacturer
    "Type_String",              // Type
    "ModelNumber_String",       // ModelNumber
    "SerialNumber_String"       // SerialNumber
};

/******************************************************
 *               Function Definitions
 ******************************************************/

void _gettimeofday()
{
}

void wait_for_unregister(void* arg) {
    MbedClient *client;
    client = (MbedClient*) arg;
/*    
    if(client->unregister_successful()) {
        printf("Unregistered done\n");

        pthread_detach(update_register_thread);
        pthread_detach(observation_thread);
        pthread_detach(unregister_thread);

        pthread_cancel(update_register_thread);
        pthread_cancel(observation_thread);
        pthread_cancel(unregister_thread);

    }
    */
    return;
}

void send_observation(void* arg) {
    MbedClient *client;
    client = (MbedClient*) arg;
    static uint8_t counter = 0;
    while(1) {
        wiced_rtos_delay_milliseconds(1 * 1000);

        if(counter >= 10 &&
           client->register_successful()) {
            printf("Incrementing Resource Value\n");
            client->update_resource();
            counter = 0;
        }
        else
            counter++;
            
    }
    return;
}

void update_register(void* arg) {
    MbedClient *client;
    client = (MbedClient*) arg;
    static uint8_t counter = 0;
    while(1) {
        wiced_rtos_delay_milliseconds(20 * 1000);
        if(client->register_successful()) {
            printf("Sending update register\n");
            client->test_update_register();
        }
    }
    return;
}

void application_start( )
{
    /* Initialise the WICED device */
    wiced_init();

    WPRINT_APP_INFO( ( "RedBear: mbed client demo for WICED\n" ) );

    MbedClient mbed_client(device);
    mbed_client.create_interface();
    
    // Create Objects of varying types, see simpleclient.h for more details on implementation.
    M2MSecurity* register_object = mbed_client.create_register_object(); // server object specifying connector info
    M2MDevice*   device_object   = mbed_client.create_device_object();   // device resources object
        
    WPRINT_APP_INFO( ("Registering endpoint\n") );
  
    wiced_rtos_create_thread(&observation_thread, WICED_DEFAULT_LIBRARY_PRIORITY, "observation_thread", (wiced_thread_function_t) send_observation, 3000, (MbedClient *) &mbed_client);
    wiced_rtos_create_thread(&unregister_thread, WICED_DEFAULT_LIBRARY_PRIORITY, "unregister_thread", (wiced_thread_function_t) wait_for_unregister, 3000, (MbedClient *) &mbed_client);
    wiced_rtos_create_thread(&update_register_thread, WICED_DEFAULT_LIBRARY_PRIORITY, "update_register_thread", (wiced_thread_function_t) update_register, 3000, (MbedClient *) &mbed_client);
      
    while ( 1 )
    {
    }
}

#if defined(__cplusplus)
}
#endif
