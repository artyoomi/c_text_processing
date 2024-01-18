#ifndef SAFETY_REALLOC_MEM_TO_WSTR_H
#define SAFETY_REALLOC_MEM_TO_WSTR_H

#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

#include "../macro.h"

void safetyReallocMemToWStr(wchar_t** wstring, int32_t* count_of_allocated_chars);

#endif