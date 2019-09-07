#pragma once

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

static const bool __debug = true;
void DebugOut(const wchar_t *fmt, ...);