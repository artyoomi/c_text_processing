#ifndef REM_SENTENCE_H
#define REM_SENTENCE_H

#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../structs.h"
#include "../free_functions/freeSentence.h"

void remSentence(struct Text **text, uint32_t index_of_sentence);

#endif