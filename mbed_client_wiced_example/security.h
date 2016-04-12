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

#define MBED_DOMAIN "0be6f601-7a86-4ac3-826f-68dbf009aff7"
#define MBED_ENDPOINT_NAME "0365092b-1fb3-4ef1-9294-232afb4c8453"
 
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
"MIIBzzCCAXOgAwIBAgIEKuuSyDAMBggqhkjOPQQDAgUAMDkxCzAJBgNVBAYTAkZ\r\n"
"JMQwwCgYDVQQKDANBUk0xHDAaBgNVBAMME21iZWQtY29ubmVjdG9yLTIwMTYwHh\r\n"
"cNMTYwNDExMTMwOTAyWhcNMTYxMjMxMDYwMDAwWjCBoTFSMFAGA1UEAxNJMGJlN\r\n"
"mY2MDEtN2E4Ni00YWMzLTgyNmYtNjhkYmYwMDlhZmY3LzAzNjUwOTJiLTFmYjMt\r\n"
"NGVmMS05Mjk0LTIzMmFmYjRjODQ1MzEMMAoGA1UECxMDQVJNMRIwEAYDVQQKEwl\r\n"
"tYmVkIHVzZXIxDTALBgNVBAcTBE91bHUxDTALBgNVBAgTBE91bHUxCzAJBgNVBA\r\n"
"YTAkZJMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEkS7exYvGTltnIUrHjZlNv\r\n"
"HL0EDYoFxMP+IV018LB38ESjeLGhH/GHU77c0Iq2sYPWd3Ept9mBEaqShLJavUH\r\n"
"ozAMBggqhkjOPQQDAgUAA0gAMEUCIQCskQ/JF8qer9+qUh0eE2zcX9+poaDBDA5\r\n"
"/DzyIjrBYRAIge4oHX7zzqeAscEZR+1eLrabq/+2d9Z/X+9kiCsuWkRQ=\r\n"
"-----END CERTIFICATE-----\r\n";
 
const uint8_t KEY[] = "-----BEGIN PRIVATE KEY-----\r\n"
"MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQgCENErafC+ik6p6p0\r\n"
"emVc0WNrtfphgwL3O/gq8fqB8c6hRANCAASRLt7Fi8ZOW2chSseNmU28cvQQNigX\r\n"
"Ew/4hXTXwsHfwRKN4saEf8YdTvtzQiraxg9Z3cSm32YERqpKEslq9Qej\r\n"
"-----END PRIVATE KEY-----\r\n";

#endif //__SECURITY_H__
