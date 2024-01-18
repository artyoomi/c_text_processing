#ifndef TEXT_STRUCT_TO_STRING_H
#define TEXT_STRUCT_TO_STRING_H

#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

#include "./structs.h"
#include "./safety_realloc_functions/safetyReallocMemToWStr.h"
#include "./free_functions/freeText.h"

wchar_t *textStructToString(struct Text **text);

#endif