#ifndef SAFETY_REALLOC_MEM_TO_SENTENCE_STRUCTS_ARRAY_H
#define SAFETY_REALLOC_MEM_TO_SENTENCE_STRUCTS_ARRAY_H

#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

#include "../structs.h"
#include "../macro.h"

void safetyReallocMemToSentenceStructsArray(struct Sentence*** sentences_array, int32_t* count_of_allocated_sentences);

#endif