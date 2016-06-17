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
#include "mbed-client/m2mobjectinstance.h"
#include "mbed-client/m2mresource.h"
#include "security.h"
#include "ns_trace.h"

#ifdef __cplusplus
extern "C" {
#endif

//Select binding mode: UDP or TCP
M2MInterface::BindingMode SOCKET_MODE = M2MInterface::TCP;

// This is address to mbed Device Connector
const String &MBED_SERVER_ADDRESS = "coap://api.connector.mbed.com:5684";

const String &MBED_USER_NAME_DOMAIN = MBED_DOMAIN;
const String &ENDPOINT_NAME = MBED_ENDPOINT_NAME;

const String &MANUFACTURER = "manufacturer";
const String &TYPE = "type";
const String &MODEL_NUMBER = "2015";
const String &SERIAL_NUMBER = "12345";

const uint8_t value[] = "MyValue";
const uint8_t STATIC_VALUE[] = "Static value";

int _gettimeofday(struct timeval *tv, struct timezone *tz)
{
	return 0;
}

class MbedClient: public M2MInterfaceObserver {
public:
    MbedClient(){
        _security = NULL;
        _interface = NULL;
        _device = NULL;
        _object = NULL;
        _error = false;
        _registered = false;
        _unregistered = false;
        _registration_updated = false;
        _value = 0;
    }

    ~MbedClient() {
        if(_security) {
            delete _security;
        }
        if( _register_security){
            delete _register_security;
        }
        if(_device) {
            M2MDevice::delete_instance();
        }
        if(_object) {
            delete _object;
        }
        if(_interface) {
            delete _interface;
        }
    }

    bool create_interface() {

       time_t t;
       srand((unsigned) time(&t));

       uint16_t port = rand() % 65535 + 12345;

       _interface = M2MInterfaceFactory::create_interface(*this,
                                                  ENDPOINT_NAME,
                                                  "test",
                                                  100,
                                                  port,
                                                  MBED_USER_NAME_DOMAIN,
                                                  SOCKET_MODE,
                                                  M2MInterface::LwIP_IPv4,
                                                  "");
        WPRINT_APP_INFO( ("Endpoint Name : %s, TYPE %d\n", ENDPOINT_NAME.c_str(), SOCKET_MODE) );
        return (_interface == NULL) ? false : true;
    }

    bool register_successful() {
        while(!_registered && !_error) {
            wiced_rtos_delay_milliseconds(1 * 1000);
        }
        return _registered;
    }

    bool unregister_successful() {
        while(!_unregistered && !_error) {
           wiced_rtos_delay_milliseconds(1 * 1000); 
        }
        return _unregistered;
    }

    bool registration_update_successful() {
        while(!_registration_updated && !_error) {
        }
        return _registration_updated;
    }

    bool create_register_object() {
        bool success = false;
        _register_security = M2MInterfaceFactory::create_security(M2MSecurity::M2MServer);
        if(_register_security) {
            _register_security->set_resource_value(M2MSecurity::M2MServerUri, MBED_SERVER_ADDRESS);
            _register_security->set_resource_value(M2MSecurity::SecurityMode, M2MSecurity::Certificate);
            _register_security->set_resource_value(M2MSecurity::ServerPublicKey,SERVER_CERT,sizeof(SERVER_CERT));
            _register_security->set_resource_value(M2MSecurity::PublicKey,CERT,sizeof(CERT));
            _register_security->set_resource_value(M2MSecurity::Secretkey,KEY,sizeof(KEY));
            success = true;
        }
        return success;
    }

    bool create_device_object() {
        bool success = false;
        _device = M2MInterfaceFactory::create_device();
        if(_device) {
            if(_device->create_resource(M2MDevice::Manufacturer,MANUFACTURER)     &&
               _device->create_resource(M2MDevice::DeviceType,TYPE)        &&
               _device->create_resource(M2MDevice::ModelNumber,MODEL_NUMBER)      &&
               _device->create_resource(M2MDevice::SerialNumber,SERIAL_NUMBER)) {
                success = true;
            }
        }
        return success;
    }

    void execute_function(void *argument) {
        if(argument) {
            char* arguments = (char*)argument;
            WPRINT_APP_INFO( ("Received %s!!\n", arguments) );
        }
        WPRINT_APP_INFO( ("I am executed !!\n") );
    }

    bool create_generic_object() {
        bool success = false;
        _object = M2MInterfaceFactory::create_object("Test");
        if(_object) {
            M2MObjectInstance* inst = _object->create_object_instance();
            if(inst) {
                M2MResource* res = inst->create_dynamic_resource("D",
                                                                 "ResourceTest",
                                                                 M2MResourceInstance::INTEGER,
                                                                 false);
                char buffer[20];
                int size = sprintf(buffer,"%d",_value);
                  res->set_operation(M2MBase::GET_PUT_ALLOWED);
                  res->set_value((const uint8_t*)buffer,
                                 (const uint32_t)size);
                  res->set_execute_function(execute_callback(this,&MbedClient::execute_function));
                _value++;
                inst->create_static_resource("S",
                                             "ResourceTest",
                                             M2MResourceInstance::STRING,
                                             STATIC_VALUE,
                                             sizeof(STATIC_VALUE)-1);
		success = true;
            }
        }
        return success;
    }

    void update_resource() {
        if(_object) {
            M2MObjectInstance* inst = _object->object_instance();
            if(inst) {
                M2MResource* res = inst->resource("D");
                WPRINT_APP_INFO( ("Resource Value /Test/0/D : %d\n", _value) );
                char buffer[20];
                int size = sprintf(buffer,"%d",_value);
                res->set_value((const uint8_t*)buffer,
                               (const uint32_t)size);
                _value++;
            }
        }
    }

    void test_register(){
        M2MObjectList object_list;
        object_list.push_back(_device);
        object_list.push_back(_object);
    if(_interface) {
            _interface->register_object(_register_security,object_list);
        } else {
        WPRINT_APP_INFO( ("Interface doesn't exist, exiting!!\n") );
            exit(1);
    }
    }

    void test_update_register() {
        uint32_t updated_lifetime = 100;
        if(_interface) {
            _interface->update_registration(_register_security,updated_lifetime);
        }
    }

    void test_unregister() {
        if(_interface) {
            _interface->unregister_object(NULL);
        }
    }

    void bootstrap_done(M2MSecurity */*server_object*/){
    }

    void object_registered(M2MSecurity */*security_object*/, const M2MServer &/*server_object*/){
        _registered = true;
        WPRINT_APP_INFO( ("\nRegistered\n") );
    }

    void object_unregistered(M2MSecurity */*server_object*/){
        _unregistered = true;
        WPRINT_APP_INFO( ("\nUnregistered\n") );
    }

    void registration_updated(M2MSecurity */*security_object*/, const M2MServer & /*server_object*/){
        _registration_updated = true;
        WPRINT_APP_INFO( ("\nregistration updated\n") );

    }

    void error(M2MInterface::Error error){
        _error = true;
        String error_code;
	switch(error) {
        case M2MInterface::ErrorNone:
             error_code += "M2MInterface::ErrorNone";
             break;
            case M2MInterface::AlreadyExists:
             error_code += "M2MInterface::AlreadyExists";
             break;
            case M2MInterface::BootstrapFailed:
             error_code += "M2MInterface::BootstrapFailed";
             break;
            case M2MInterface::InvalidParameters:
             error_code += "M2MInterface::InvalidParameters";
             break;
            case M2MInterface::NotRegistered:
             error_code += "M2MInterface::NotRegistered";
             break;
            case M2MInterface::Timeout:
             error_code += "M2MInterface::Timeout";
             break;
            case M2MInterface::NetworkError:
             error_code += "M2MInterface::NetworkError";
             break;
            case M2MInterface::ResponseParseFailed:
             error_code += "M2MInterface::ResponseParseFailed";
             break;
            case M2MInterface::UnknownError:
             error_code += "M2MInterface::UnknownError";
             break;
            case M2MInterface::MemoryFail:
             error_code += "M2MInterface::MemoryFail";
             break;
            case M2MInterface::NotAllowed:
             error_code += "M2MInterface::NotAllowed";
             break;
        }
        WPRINT_APP_INFO( ("\nError occured  : %s\n", error_code.c_str()) );
    }

    void value_updated(M2MBase *base, M2MBase::BaseType type) {
        WPRINT_APP_INFO( ("\nValue updated of Object name %s and Type %d\n",
               base->name().c_str(), type) );

        if(_object) {
		WPRINT_APP_INFO( ("_object %x\n",_object) );
            M2MObjectInstance* inst = _object->object_instance();
		WPRINT_APP_INFO( ("inst %x\n",inst) );
            if(inst) {
                    M2MResource* res = inst->resource("D");

		WPRINT_APP_INFO( ("res %x\n",res) );
                    uint8_t * buffer=NULL;
                        uint32_t size;
                    res->get_value(buffer,size);
		WPRINT_APP_INFO( ("size %x\n",size) );
                        if(buffer)
                        {
                                sscanf((const char*)buffer,"%d",&_value);
        _value ++;
                        }
                }
        }

    }

private:

    M2MInterface        *_interface;
    M2MSecurity         *_security;
    M2MSecurity         *_register_security;
    M2MDevice           *_device;
    M2MObject           *_object;
    bool                _error;
    bool                _registered;
    bool                _unregistered;
    bool                _registration_updated;
    int                 _value;
};

void* wait_for_unregister(void* arg) {
    MbedClient *client;
    client = (MbedClient*) arg;
    if(client->unregister_successful()) {
        WPRINT_APP_INFO( ("Unregistered done\n") );
/*    
        pthread_detach(update_register_thread);
        pthread_detach(observation_thread);
        pthread_detach(unregister_thread);

        pthread_cancel(update_register_thread);
        pthread_cancel(observation_thread);
        pthread_cancel(unregister_thread);
*/
    }
    return NULL;
}

void* send_observation(void* arg) {
    MbedClient *client;
    client = (MbedClient*) arg;
    static uint8_t counter = 0;
    while(1) {
        wiced_rtos_delay_milliseconds(1 * 1000);

        if(counter >= 10 &&
           client->register_successful()) {
            WPRINT_APP_INFO( ("Incrementing Resource Value\n") );
            client->update_resource();
            counter = 0;
        }
        else
            counter++;
    }
    return NULL;
}

void* update_register(void* arg) {
    MbedClient *client;
    client = (MbedClient*) arg;
    static uint8_t counter = 0;
    while(1) {
        wiced_rtos_delay_milliseconds(20 * 1000);
        if(client->register_successful()) {
            WPRINT_APP_INFO( ("Sending update register\n") );
            client->test_update_register();
        }
    }
    return NULL;
}


void application_start( )
{
    MbedClient mbed_client;

    /* Initialise the WICED device */
    wiced_init();
    /* Bring up the network on the STA interface */
    wiced_network_up( WICED_STA_INTERFACE, WICED_USE_EXTERNAL_DHCP_SERVER, NULL );

    
    WPRINT_APP_INFO( ( "RedBear: mbed client demo for WICED\n" ) );

    bool result = mbed_client.create_interface();
    if(true == result) {
        WPRINT_APP_INFO( ("\nInterface created\n") );
    }
    result = mbed_client.create_register_object();
    if(true == result) {
        WPRINT_APP_INFO( ("register object created") );
    }
    result = mbed_client.create_device_object();
    if(true == result){
        WPRINT_APP_INFO( ("\nDevice object created !!\n") );
    }

    result = mbed_client.create_generic_object();

    if(true == result) {
        WPRINT_APP_INFO( ("\nGeneric object created\n") );
    }

    WPRINT_APP_INFO( ("Registering endpoint\n") );
    mbed_client.test_register();

#if 0 
    wiced_rtos_create_thread(&observation_thread, WICED_DEFAULT_LIBRARY_PRIORITY, "observation_thread", (wiced_thread_function_t) send_observation, 3000, (MbedClient *) &mbed_client);
    wiced_rtos_create_thread(&unregister_thread, WICED_DEFAULT_LIBRARY_PRIORITY, "unregister_thread", (wiced_thread_function_t) wait_for_unregister, 3000, (MbedClient *) &mbed_client);
    wiced_rtos_create_thread(&update_register_thread, WICED_DEFAULT_LIBRARY_PRIORITY, "update_register_thread", (wiced_thread_function_t) update_register, 3000, (MbedClient *) &mbed_client);
      
    while ( 1 )
    {
    }
#endif    
}
#if defined(__cplusplus)
}
#endif
