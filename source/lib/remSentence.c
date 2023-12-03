#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifndef STRUCTS_H
	#define STRUCTS_H
	#include "../include/structs.h"
#endif

#ifndef REM_SENTENCE_H
	#define REM_SENTENCE_H
	#include "../include/remSentence.h"
#endif

void remSentence(struct Text **text, const uint32_t index_of_sentence)
{
	// сохраняем адрес на структуру, которую необходимо удалить
	struct Sentence *sentence_to_del = (*text)->sentences_array[index_of_sentence];

    memmove(&(*text)->sentences_array[index_of_sentence],
	        &(*text)->sentences_array[index_of_sentence + 1],
	        ((*text)->len - index_of_sentence - 1) * sizeof(struct Sentence *));

    free(sentence_to_del);
    (*(*text)).len--;
}