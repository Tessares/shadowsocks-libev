/*
 * encrypt.h - Define the enryptor's interface
 *
 * Copyright (C) 2013 - 2018, Max Lv <max.c.lv@gmail.com>
 *
 * This file is part of the shadowsocks-libev.
 *
 * shadowsocks-libev is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * shadowsocks-libev is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with shadowsocks-libev; see the file COPYING. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef _STREAM_H
#define _STREAM_H

#ifndef __MINGW32__
#include <sys/socket.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#elif HAVE_INTTYPES_H
#include <inttypes.h>
#endif

#include <sodium.h>
#define STREAM_CIPHER_NUM          21

#include "crypto.h"

#ifndef UNUSED
#ifdef __GNUC__
#define UNUSED __attribute__((__unused__))
#else
#define UNUSED
#endif
#endif

int stream_encrypt_all(buffer_t *, cipher_t *, size_t);
int stream_decrypt_all(buffer_t *, cipher_t *, size_t);
int stream_encrypt(buffer_t *, cipher_ctx_t *, size_t);
int stream_decrypt(buffer_t *, cipher_ctx_t *, size_t);

void stream_ctx_init(cipher_t *, cipher_ctx_t *, int);
void stream_ctx_release(cipher_ctx_t *);

static int stream_nocrypt_plain_all(UNUSED buffer_t *b, UNUSED cipher_t *c, UNUSED size_t s) {
        return CRYPTO_OK;
}
static int stream_nocrypt_plain(UNUSED buffer_t *b, UNUSED cipher_ctx_t *ctx, UNUSED size_t s) {
        return CRYPTO_OK;
}
static void stream_plain_ctx_init(UNUSED cipher_t *c, UNUSED cipher_ctx_t *ctx, UNUSED int i) {
        return;
}
static void stream_plain_ctx_release(UNUSED cipher_ctx_t *ctx) {
        return;
}

cipher_t *stream_init(const char *pass, const char *key, const char *method);

#endif // _STREAM_H
