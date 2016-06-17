#
# Copyright 2014, Broadcom Corporation
# All Rights Reserved.
#
# This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
# the contents of this file may not be disclosed to third parties, copied
# or duplicated in any form, in whole or in part, without the prior
# written permission of Broadcom Corporation.
#

NAME := mbed-client_Application

$(NAME)_SOURCES := app.cpp \
	mbedtls/source/aes.c \
	mbedtls/source/aesni.c \
	mbedtls/source/arc4.c \
	mbedtls/source/asn1parse.c \
	mbedtls/source/asn1write.c \
	mbedtls/source/base64.c \
	mbedtls/source/bignum.c \
	mbedtls/source/blowfish.c \
	mbedtls/source/camellia.c \
	mbedtls/source/ccm.c \
	mbedtls/source/certs.c \
	mbedtls/source/cipher_wrap.c \
	mbedtls/source/cipher.c \
	mbedtls/source/ctr_drbg.c \
	mbedtls/source/debug.c \
	mbedtls/source/des.c \
	mbedtls/source/dhm.c \
	mbedtls/source/ecdh.c \
	mbedtls/source/ecdsa.c \
	mbedtls/source/ecjpake.c \
	mbedtls/source/ecp_curves.c \
	mbedtls/source/ecp.c \
	mbedtls/source/entropy_poll.c \
	mbedtls/source/entropy.c \
	mbedtls/source/error.c \
	mbedtls/source/gcm.c \
	mbedtls/source/havege.c \
	mbedtls/source/hmac_drbg.c \
	mbedtls/source/md_wrap.c \
	mbedtls/source/md.c \
	mbedtls/source/md2.c \
	mbedtls/source/md4.c \
	mbedtls/source/md5.c \
	mbedtls/source/memory_buffer_alloc.c \
	mbedtls/source/net.c \
	mbedtls/source/oid.c \
	mbedtls/source/padlock.c \
	mbedtls/source/pem.c \
	mbedtls/source/pk_wrap.c \
	mbedtls/source/pk.c \
	mbedtls/source/pkcs5.c \
	mbedtls/source/pkcs11.c \
	mbedtls/source/pkcs12.c \
	mbedtls/source/pkparse.c \
	mbedtls/source/pkwrite.c \
	mbedtls/source/platform.c \
	mbedtls/source/ripemd160.c \
	mbedtls/source/rsa.c \
	mbedtls/source/sha1.c \
	mbedtls/source/sha256.c \
	mbedtls/source/sha512.c \
	mbedtls/source/ssl_cache.c \
	mbedtls/source/ssl_ciphersuites.c \
	mbedtls/source/ssl_cli.c \
	mbedtls/source/ssl_cookie.c \
	mbedtls/source/ssl_srv.c \
	mbedtls/source/ssl_ticket.c \
	mbedtls/source/ssl_tls.c \
	mbedtls/source/threading.c \
	mbedtls/source/timing.c \
	mbedtls/source/version_features.c \
	mbedtls/source/version.c \
	mbedtls/source/x509_create.c \
	mbedtls/source/x509_crl.c \
	mbedtls/source/x509_csr.c \
	mbedtls/source/x509write_crt.c \
	mbedtls/source/x509write_csr.c \
	mbedtls/source/xtea.c \
	mbed-trace/source/mbed_trace.c \
	nanostack-libservice/source/IPv6_fcf_lib/ip_fsc.c \
	nanostack-libservice/source/libBits/common_functions.c \
	nanostack-libservice/source/libip6string/ip6tos.c \
	nanostack-libservice/source/libip6string/stoip6.c \
	nanostack-libservice/source/libList/ns_list.c \
	nanostack-libservice/source/libTrace/ns_trace.c \
	nanostack-libservice/source/nsdynmemLIB/nsdynmemLIB.c \
	mbed-client-mbedtls/source/m2mconnectionsecurity.cpp \
	mbed-client-mbedtls/source/m2mconnectionsecuritypimpl.cpp \
	mbed-client-c/source/libCoap/src/sn_coap_builder.c \
	mbed-client-c/source/libCoap/src/sn_coap_header_check.c \
	mbed-client-c/source/libCoap/src/sn_coap_parser.c \
	mbed-client-c/source/libCoap/src/sn_coap_protocol.c \
	mbed-client-c/source/libNsdl/src/sn_grs.c \
	mbed-client-c/source/libNsdl/src/sn_nsdl.c \
	mbed-client/source/m2mbase.cpp \
	mbed-client/source/m2mdevice.cpp \
	mbed-client/source/m2mfirmware.cpp \
	mbed-client/source/m2minterfacefactory.cpp \
	mbed-client/source/m2minterfaceimpl.cpp \
	mbed-client/source/m2mnsdlinterface.cpp \
	mbed-client/source/m2mobject.cpp \
	mbed-client/source/m2mobjectinstance.cpp \
	mbed-client/source/m2mreporthandler.cpp \
	mbed-client/source/m2mresource.cpp \
	mbed-client/source/m2mresourceinstance.cpp \
	mbed-client/source/m2msecurity.cpp \
	mbed-client/source/m2mserver.cpp \
	mbed-client/source/m2mstring.cpp \
	mbed-client/source/m2mtlvdeserializer.cpp \
	mbed-client/source/m2mtlvserializer.cpp \
	mbed-client/source/nsdlaccesshelper.cpp \
	mbed-client-wiced/source/m2mtimer.cpp \
	mbed-client-wiced/source/m2mtimerpimpl.cpp \
	mbed-client-wiced/source/m2mconnectionhandler.cpp \
	mbed-client-wiced/source/m2mconnectionhandlerpimpl.cpp \
	mbed-client-wiced/source/connthreadhelper.cpp \
	mbedtls/source/x509_crt.c \
	mbedtls/source/x509.c \

GLOBAL_INCLUDES += mbedtls \
	mbed-client-mbedtls \
	mbed-client-c \
	mbed-client-c/nsdl-c \
	mbed-client-c/source/libCoap/src/include \
	mbed-client-c/source/libNsdl/src/include \
	mbed-trace \
	nanostack-libservice/mbed-client-libservice \
	mbed-client \
	mbed-client/source \
	mbed-client-wiced \

GLOBAL_DEFINES +=

CFLAGS := -nostdlib

