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

#include "mbed-client-wiced/m2mtimerpimpl.h"
#include "mbed-client/m2mtimerobserver.h"

M2MTimerPimpl::M2MTimerPimpl(M2MTimerObserver& observer)
: _observer(observer),
  _single_shot(true),
  _interval(0),
  _type(M2MTimerObserver::Notdefined),
  _intermediate_interval(0),
  _total_interval(0),
  _status(0),
  _still_left(0)
{
}

M2MTimerPimpl::~M2MTimerPimpl()
{
    wiced_rtos_deinit_timer(&_timer);
}

void my_timer_expired(void *t)
{
    M2MTimerPimpl *timer = reinterpret_cast<M2MTimerPimpl *> (t);


    timer->_observer.timer_expired(timer->_type);

    if (!timer->_single_shot) {
        timer->start_timer(timer->_interval, timer->_type, false);
    }
}

void my_still_left_timer_expired(void *t)
{
    M2MTimerPimpl *timer = reinterpret_cast<M2MTimerPimpl *> (t);

    wiced_rtos_stop_timer(&timer->_timer);
    wiced_rtos_deinit_timer(&timer->_timer);

    if (timer->_still_left > 0) {

        if (timer->_still_left > (2000 * 1000)) {

            timer->_still_left = timer->_still_left - (2000 * 1000);

            wiced_rtos_init_timer(&timer->_timer, 2000 * 1000,
                          my_still_left_timer_expired,
                          (void *)timer);

        } else {

            wiced_rtos_init_timer(&timer->_timer, timer->_still_left,
                          my_still_left_timer_expired,
                          (void *)timer);

            timer->_still_left = 0;
        }

        wiced_rtos_start_timer(&timer->_timer);

    } else {

        timer->_observer.timer_expired(timer->_type);

        if(!timer->_single_shot) {
            timer->start_timer(timer->_interval, timer->_type, timer->_single_shot);
        }

    }
}

void my_dtls_timer_expired(void *t)
{
    M2MTimerPimpl *timer = reinterpret_cast<M2MTimerPimpl *> (t);

    timer->_status++;
    if (timer->_status == 1) {
        timer->_observer.timer_expired(timer->_type);
        wiced_rtos_init_timer(&timer->_timer, timer->_total_interval - timer->_intermediate_interval,
                          my_dtls_timer_expired,
                          (void *)timer);
        wiced_rtos_start_timer(&timer->_timer);
    } else {
        wiced_rtos_stop_timer(&timer->_timer);
        wiced_rtos_deinit_timer(&timer->_timer);
        timer->_observer.timer_expired(timer->_type);
    }
}

void M2MTimerPimpl::start_timer( uint64_t interval,
                                 M2MTimerObserver::Type type,
                                 bool single_shot)
{
    _intermediate_interval = 0;
    _total_interval = 0;    
    _single_shot = single_shot;
    _interval = interval;
    _type = type;

    wiced_rtos_stop_timer(&_timer);
    wiced_rtos_deinit_timer(&_timer);

    if(_interval > (2000 * 1000)) {
        _still_left = _interval - (2000 * 1000);
        wiced_rtos_init_timer(&_timer, 2000 * 1000,
                      &my_still_left_timer_expired,
                      (void *) this);
    } else {
        wiced_rtos_init_timer(&_timer, _interval,
                  my_timer_expired,
                  (void *) this);
    }

    wiced_rtos_start_timer(&_timer);
}

void M2MTimerPimpl::start_dtls_timer(uint64_t intermediate_interval, uint64_t total_interval, M2MTimerObserver::Type type)
{
    _intermediate_interval = intermediate_interval;
    _total_interval = total_interval;
    _type = type;

    wiced_rtos_stop_timer(&_timer);
    wiced_rtos_deinit_timer(&_timer);

    _status = 0;

    wiced_rtos_init_timer(&_timer, _intermediate_interval,
                  my_timer_expired,
                  (void *) this);
    wiced_rtos_start_timer(&_timer);
}

void M2MTimerPimpl::stop_timer()
{
    _interval = 0;
    _still_left = 0;
    _single_shot = false;

    wiced_rtos_stop_timer(&_timer);
    wiced_rtos_deinit_timer(&_timer);
}

void M2MTimerPimpl::timer_expired()
{
    _observer.timer_expired(_type);

    if (!_single_shot) {
        start_timer(_interval, _type, false);
    }
}

void M2MTimerPimpl::still_left_timer_expired()
{
    wiced_rtos_stop_timer(&_timer);
    wiced_rtos_deinit_timer(&_timer);

    if(_still_left > 0) {

        if(_still_left > (2000 * 1000)) {

            _still_left = _still_left - (2000 * 1000);

            wiced_rtos_init_timer(&_timer, 2000 * 1000,
                          my_still_left_timer_expired,
                          (void *)this);

        } else {

            wiced_rtos_init_timer(&_timer, _still_left,
                          my_still_left_timer_expired,
                          (void *) this);

            _still_left = 0;
        }

        wiced_rtos_start_timer(&_timer);

    } else {

        _observer.timer_expired(_type);

        if(!_single_shot) {
            start_timer(_interval, _type, _single_shot);
        }

    }
}

void M2MTimerPimpl::dtls_timer_expired()
{
    _status++;
    if (_status == 1) {
        _observer.timer_expired(_type);
        wiced_rtos_init_timer(&_timer, _total_interval - _intermediate_interval,
                          my_dtls_timer_expired,
                          (void *)this);
        wiced_rtos_start_timer(&_timer);
    } else {
        wiced_rtos_stop_timer(&_timer);
        wiced_rtos_deinit_timer(&_timer);
        _observer.timer_expired(_type);
    }
}

bool M2MTimerPimpl::is_intermediate_interval_passed()
{
    if (_status > 0)
        return true;

    return false;
}

bool M2MTimerPimpl::is_total_interval_passed()
{
    if (_status > 1)
        return true;

    return false;
}
