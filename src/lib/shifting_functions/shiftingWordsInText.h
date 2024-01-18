#ifndef SHIFTING_WORDS_IN_TEXT_H
#define SHIFTING_WORDS_IN_TEXT_H

#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

#include "../structs.h"

void shiftingWordsInText(struct Text **text, const uint32_t number_of_shifts);

#endif