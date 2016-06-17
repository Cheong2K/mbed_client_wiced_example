/*
 * Copyright (c) 2015 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed-client-wiced/m2mconnectionhandlerpimpl.h"
#include "include/connthreadhelper.h"
#include "mbed-client/m2msecurity.h"
#include "mbed-trace/mbed_trace.h"

#include "wiced.h"


M2MConnectionHandlerPimpl::M2MConnectionHandlerPimpl(M2MConnectionHandler* base, M2MConnectionObserver &observer,
                                                     M2MConnectionSecurity *sec,
                                                     M2MInterface::BindingMode mode,
                                                     M2MInterface::NetworkStack stack)
:_base(base),
 _observer(observer),
 _security_impl(sec),
 _use_secure_connection(false),
 _binding_mode(mode)
{    
    __connection_impl = this;

//    WPRINT_APP_INFO( ( "i: 1\n" ) );     

    _socket_address = (M2MConnectionObserver::SocketAddress *)malloc(sizeof(M2MConnectionObserver::SocketAddress));
    WPRINT_APP_INFO( ( "i: addr %x\n", _socket_address) );     
    socket = (wiced_tcp_socket_t*)malloc(sizeof(wiced_tcp_socket_t));
    WPRINT_APP_INFO( ( "i: addr %x\n", socket) );     
    
//    WPRINT_APP_INFO( ( "i: 2\n" ) );     
    memset(_socket_address, 0, sizeof(M2MConnectionObserver::SocketAddress));
//    WPRINT_APP_INFO( ( "i: 3\n" ) );     
    _socket_address->_address = _received_address;
    
//    WPRINT_APP_INFO( ( "i: 4\n" ) );     
    wiced_tcp_create_socket(socket, WICED_STA_INTERFACE);
//    WPRINT_APP_INFO( ( "i: 5\n" ) );     
}

M2MConnectionHandlerPimpl::~M2MConnectionHandlerPimpl()
{
    wiced_tcp_delete_socket(socket);
    free(socket);
    socket = NULL;
}

bool M2MConnectionHandlerPimpl::bind_connection(const uint16_t listen_port)
{
    bool success = false;
    
    if (socket)
    {
        wiced_tcp_bind(socket, listen_port);
        success = true;
    }
    
    return success;
}

bool M2MConnectionHandlerPimpl::resolve_server_address(const String& server_address,
                                                  const uint16_t server_port,
                                                  M2MConnectionObserver::ServerType server_type,
                                                  const M2MSecurity* security)
{
    wiced_ip_address_t address;
   
    char *c_str = const_cast<char*>(server_address.c_str());
    if (wiced_hostname_lookup(c_str, &address, 1000))
        return true;

    return false;
}

bool M2MConnectionHandlerPimpl::start_listening_for_data()
{
    bool success = true;
    
    if (!_receive_data) {
        _receive_data = true;
 
        wiced_rtos_create_thread(&_listen_thread, WICED_DEFAULT_LIBRARY_PRIORITY, NULL, (wiced_thread_function_t) __listen_data_function, 1024, (void *)this);
    }
    
    return success;
}

int M2MConnectionHandlerPimpl::send_to_socket(const unsigned char *buf, size_t len)
{
    wiced_tcp_send_buffer(socket, buf, len);
    
    return 1;
}

int M2MConnectionHandlerPimpl::receive_from_socket(unsigned char *buf, size_t len)
{
    return -1;
}

void M2MConnectionHandlerPimpl::data_receive(void *object)
{
    WPRINT_APP_INFO( ("Data Received.\n") );
    
    //wiced_tcp_receive(socket, packet, WICED_NEVER_TIMEOUT);
}

bool M2MConnectionHandlerPimpl::send_data(uint8_t *data,
                                     uint16_t data_len,
                                     sn_nsdl_addr_s *address)
{
    uint16_t d_len = data_len+4;
    uint8_t* d = (uint8_t*)malloc(data_len+4);

    d[0] = (data_len >> 24 )& 0xff;
    d[1] = (data_len >> 16 )& 0xff;
    d[2] = (data_len >> 8 )& 0xff;
    d[3] = data_len & 0xff;
    memmove(d+4, data, data_len);
            
    wiced_tcp_send_buffer(socket, d, d_len);
            
    return true;
}

void M2MConnectionHandlerPimpl::stop_listening()
{
}

void M2MConnectionHandlerPimpl::handle_connection_error(int /*error*/)
{
    //This will come from M2MConnectionSecurity class
    _observer.socket_error(4);
}
