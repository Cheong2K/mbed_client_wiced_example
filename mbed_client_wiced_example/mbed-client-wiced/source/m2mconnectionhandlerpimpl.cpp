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
}

M2MConnectionHandlerPimpl::~M2MConnectionHandlerPimpl()
{
}

bool M2MConnectionHandlerPimpl::bind_connection(const uint16_t listen_port)
{
    bool success = false;
    if(_listen_port == 0) {
         success = true;
        _listen_port = listen_port;
    }
    return success;
}

bool M2MConnectionHandlerPimpl::resolve_server_address(const String& server_address,
                                                  const uint16_t server_port,
                                                  M2MConnectionObserver::ServerType server_type,
                                                  const M2MSecurity* security)
{
    wiced_ip_address_t address;
   
   // ToDo 
 //   wiced_hostname_lookup(server_address, &)
    return true;
}

bool M2MConnectionHandlerPimpl::start_listening_for_data()
{
    bool success = true;
    
    if (!_receive_data) {
        _receive_data = true;
  //      wiced_rtos_create_thread(&_listen_thread, NULL,__listen_data_function, this);
    }
    
    return success;
}

int M2MConnectionHandlerPimpl::send_to_socket(const unsigned char *buf, size_t len)
{
}

int M2MConnectionHandlerPimpl::receive_from_socket(unsigned char *buf, size_t len)
{
    return -1;
}

void M2MConnectionHandlerPimpl::data_receive(void *object)
{
}

bool M2MConnectionHandlerPimpl::send_data(uint8_t *data,
                                     uint16_t data_len,
                                     sn_nsdl_addr_s *address)
{
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
