#ifndef SAFETY_REALLOC_MEM_TO_WORD_STRUCTS_ARRAY_H
#define SAFETY_REALLOC_MEM_TO_WORD_STRUCTS_ARRAY_H

#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

#include "../structs.h"
#include "../macro.h"

void safetyReallocMemToWordStructsArray(struct Word*** words_array, int32_t* count_of_allocated_words);

#endif