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
	mbedtls/library/aes.c \
	mbedtls/library/aesni.c \
	mbedtls/library/arc4.c \
	mbedtls/library/asn1parse.c \
	mbedtls/library/asn1write.c \
	mbedtls/library/base64.c \
	mbedtls/library/bignum.c \
	mbedtls/library/blowfish.c \
	mbedtls/library/camellia.c \
	mbedtls/library/ccm.c \
	mbedtls/library/certs.c \
	mbedtls/library/cipher_wrap.c \
	mbedtls/library/cipher.c \
	mbedtls/library/ctr_drbg.c \
	mbedtls/library/debug.c \
	mbedtls/library/des.c \
	mbedtls/library/dhm.c \
	mbedtls/library/ecdh.c \
	mbedtls/library/ecdsa.c \
	mbedtls/library/ecjpake.c \
	mbedtls/library/ecp_curves.c \
	mbedtls/library/ecp.c \
	mbedtls/library/entropy_poll.c \
	mbedtls/library/entropy.c \
	mbedtls/library/error.c \
	mbedtls/library/gcm.c \
	mbedtls/library/havege.c \
	mbedtls/library/hmac_drbg.c \
	mbedtls/library/md_wrap.c \
	mbedtls/library/md.c \
	mbedtls/library/md2.c \
	mbedtls/library/md4.c \
	mbedtls/library/md5.c \
	mbedtls/library/memory_buffer_alloc.c \
	mbedtls/library/net.c \
	mbedtls/library/oid.c \
	mbedtls/library/padlock.c \
	mbedtls/library/pem.c \
	mbedtls/library/pk_wrap.c \
	mbedtls/library/pk.c \
	mbedtls/library/pkcs5.c \
	mbedtls/library/pkcs11.c \
	mbedtls/library/pkcs12.c \
	mbedtls/library/pkparse.c \
	mbedtls/library/pkwrite.c \
	mbedtls/library/platform.c \
	mbedtls/library/ripemd160.c \
	mbedtls/library/rsa.c \
	mbedtls/library/sha1.c \
	mbedtls/library/sha256.c \
	mbedtls/library/sha512.c \
	mbedtls/library/ssl_cache.c \
	mbedtls/library/ssl_ciphersuites.c \
	mbedtls/library/ssl_cli.c \
	mbedtls/library/ssl_cookie.c \
	mbedtls/library/ssl_srv.c \
	mbedtls/library/ssl_ticket.c \
	mbedtls/library/ssl_tls.c \
	mbedtls/library/threading.c \
	mbedtls/library/timing.c \
	mbedtls/library/version_features.c \
	mbedtls/library/version.c \
	mbedtls/library/x509_create.c \
	mbedtls/library/x509_crl.c \
	mbedtls/library/x509_csr.c \
	mbedtls/library/x509write_crt.c \
	mbedtls/library/x509write_csr.c \
	mbedtls/library/xtea.c \
	mbed-trace/mbed_trace_ip6tos.c \
	mbed-trace/mbed_trace.c \
	nanostack-libservice/source/IPv6_fcf_lib/ip_fsc.c \
	nanostack-libservice/source/libBits/common_functions.c \
	nanostack-libservice/source/libip6string/ip6tos.c \
	nanostack-libservice/source/libip6string/stoip6.c \
	nanostack-libservice/source/libList/ns_list.c \
	nanostack-libservice/source/libTrace/ns_trace.c \
	nanostack-libservice/source/nsdynmemLIB/nsdynmemLIB.c \
	mbed-client-mbedtls/m2mconnectionsecurity.cpp \
	mbed-client-mbedtls/m2mconnectionsecuritypimpl.cpp \
	mbed-client-c/source/libCoap/src/sn_coap_builder.c \
	mbed-client-c/source/libCoap/src/sn_coap_header_check.c \
	mbed-client-c/source/libCoap/src/sn_coap_parser.c \
	mbed-client-c/source/libCoap/src/sn_coap_protocol.c \
	mbed-client-c/source/libNsdl/src/sn_grs.c \
	mbed-client-c/source/libNsdl/src/sn_nsdl.c \
	mbed-client/source/m2mbase.cpp \
	mbed-client/source/m2mconstants.cpp \
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
	mbedtls/library/x509_crt.c \
	mbedtls/library/x509.c \

GLOBAL_INCLUDES += mbedtls/include \
	mbed_client_mbedtls \
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

