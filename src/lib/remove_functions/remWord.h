#ifndef REM_WORD_H
#define REM_WORD_H

#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "../structs.h"

void remWord(struct Sentence **sentence, const uint32_t index_of_word);

#endif