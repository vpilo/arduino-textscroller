#pragma once

// Copyright (c) 2008-2010 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.

#ifdef __cplusplus
extern "C" {
#endif

#define UTF8_ACCEPT 0
#define UTF8_REJECT 12

uint32_t
utf8decode(uint32_t* state, uint32_t* codep, uint32_t byte);

#ifdef __cplusplus
}
#endif
