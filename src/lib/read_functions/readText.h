#ifndef READ_TEXT_H
#define READ_TEXT_H

#include <wchar.h>
#include <stdlib.h>

#include "../structs.h"
#include "../read_functions/readSentence.h"
#include "../safety_realloc_functions/safetyReallocMemToSentenceStructsArray.h"
#include "../free_functions/freeSentence.h"

struct Text* readText();

#endif