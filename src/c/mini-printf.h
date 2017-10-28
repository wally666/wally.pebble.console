#pragma once

/*
 * The Minimal snprintf() implementation
 * Copyright (c) 2013 Michal Ludvig <michal@logix.cz>
 */

#include <stdarg.h>

int mini_vsnprintf(char* buffer, unsigned int buffer_len, const char *fmt, va_list va);
int mini_snprintf(char* buffer, unsigned int buffer_len, const char *fmt, ...);