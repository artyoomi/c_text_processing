#ifndef PRINT_UNIQ_SYMBOLS_IN_TEXT_H
#define PRINT_UNIQ_SYMBOLS_IN_TEXT_H

#include <stdint.h>
#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>

#include "../structs.h"
#include "../textStructToString.h"
#include "../safety_realloc_functions/safetyReallocMemToWStr.h"

void printUniqSymbolsInText(struct Text **text);

#endif