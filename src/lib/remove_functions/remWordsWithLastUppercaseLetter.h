#ifndef REM_WORDS_WITH_LAST_UPPERCASE_LETTER_H
#define REM_WORDS_WITH_LAST_UPPERCASE_LETTER_H

#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>

#include "../structs.h"
#include "./remWord.h"
#include "./remSentence.h"

void remWordsWithLastUppercaseLetter(struct Text **text);

#endif