#ifndef READ_SENTENCE_H
#define READ_SENTENCE_H

#include <wchar.h>
#include <stdlib.h>
#include <stdint.h>
#include <wctype.h>

#include "../structs.h"
#include "../safety_realloc_functions/safetyReallocMemToWStr.h"
#include "../safety_realloc_functions/safetyReallocMemToWordStructsArray.h"
#include "../safety_realloc_functions/safetyReallocMemToSentenceStructsArray.h"

struct Sentence* readSentence();

#endif