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

#ifndef __SECURITY_H__

#define __SECURITY_H__

 

#include <inttypes.h>

 

#define MBED_DOMAIN "4dee7279-a1b4-4c13-9be8-c2d862a94bc4"

#define MBED_ENDPOINT_NAME "27c481df-462d-4e53-b93d-1d5e4e425d51"

 

const uint8_t SERVER_CERT[] = "-----BEGIN CERTIFICATE-----\r\n"

"MIIBmDCCAT6gAwIBAgIEVUCA0jAKBggqhkjOPQQDAjBLMQswCQYDVQQGEwJGSTEN\r\n"

"MAsGA1UEBwwET3VsdTEMMAoGA1UECgwDQVJNMQwwCgYDVQQLDANJb1QxETAPBgNV\r\n"

"BAMMCEFSTSBtYmVkMB4XDTE1MDQyOTA2NTc0OFoXDTE4MDQyOTA2NTc0OFowSzEL\r\n"

"MAkGA1UEBhMCRkkxDTALBgNVBAcMBE91bHUxDDAKBgNVBAoMA0FSTTEMMAoGA1UE\r\n"

"CwwDSW9UMREwDwYDVQQDDAhBUk0gbWJlZDBZMBMGByqGSM49AgEGCCqGSM49AwEH\r\n"

"A0IABLuAyLSk0mA3awgFR5mw2RHth47tRUO44q/RdzFZnLsAsd18Esxd5LCpcT9w\r\n"

"0tvNfBv4xJxGw0wcYrPDDb8/rjujEDAOMAwGA1UdEwQFMAMBAf8wCgYIKoZIzj0E\r\n"

"AwIDSAAwRQIhAPAonEAkwixlJiyYRQQWpXtkMZax+VlEiS201BG0PpAzAiBh2RsD\r\n"

"NxLKWwf4O7D6JasGBYf9+ZLwl0iaRjTjytO+Kw==\r\n"

"-----END CERTIFICATE-----\r\n";

 

const uint8_t CERT[] = "-----BEGIN CERTIFICATE-----\r\n"

"MIIBzjCCAXOgAwIBAgIEEbEzrDAMBggqhkjOPQQDAgUAMDkxCzAJBgNVBAYTAkZ\r\n"

"JMQwwCgYDVQQKDANBUk0xHDAaBgNVBAMME21iZWQtY29ubmVjdG9yLTIwMTYwHh\r\n"

"cNMTYwNjE1MDM0MTM0WhcNMTYxMjMxMDYwMDAwWjCBoTFSMFAGA1UEAxNJNGRlZ\r\n"

"TcyNzktYTFiNC00YzEzLTliZTgtYzJkODYyYTk0YmM0LzI3YzQ4MWRmLTQ2MmQt\r\n"

"NGU1My1iOTNkLTFkNWU0ZTQyNWQ1MTEMMAoGA1UECxMDQVJNMRIwEAYDVQQKEwl\r\n"

"tYmVkIHVzZXIxDTALBgNVBAcTBE91bHUxDTALBgNVBAgTBE91bHUxCzAJBgNVBA\r\n"

"YTAkZJMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEqrrmV0MTGC7HLDEONTt/F\r\n"

"6uwJvRaIA0wIzmwO5EEryrp9AG2lqGXDbBXkIKBE0PyiexfHuUE1jbhVNy1uBjp\r\n"

"pjAMBggqhkjOPQQDAgUAA0cAMEQCIApOzbu6e7iQ97tr+RjnoJSulL/Ax2c4ANl\r\n"

"1VMQqz9l+AiBxreP8qHz/ZP0wEhZ3aE3M3gOrkWEcJlLc3daK/vgpCQ==\r\n"

"-----END CERTIFICATE-----\r\n";

 

const uint8_t KEY[] = "-----BEGIN PRIVATE KEY-----\r\n"

"MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQgKcI/qMIKCBEUo2OO\r\n"

"qTuFWYBZ1U/V8vbv7sQ8bKVURhWhRANCAASquuZXQxMYLscsMQ41O38Xq7Am9Fog\r\n"

"DTAjObA7kQSvKun0AbaWoZcNsFeQgoETQ/KJ7F8e5QTWNuFU3LW4GOmm\r\n"

"-----END PRIVATE KEY-----\r\n";

 

#endif //__SECURITY_H__

