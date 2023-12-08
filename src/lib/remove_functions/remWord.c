#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef STRUCTS_H
	#define STRUCTS_H
	#include "../../include/structs.h"
#endif

#ifndef REM_WORD_H
	#define REM_WORD_H
	#include "../../include/remove_functions/remWord.h"
#endif

void remWord(struct Text **text, const uint32_t index_of_sentence, const uint32_t index_of_word_in_sentence)
{
	struct Word *word_to_del = (*text)->sentences_array[index_of_sentence]->words_array[index_of_word_in_sentence];
	memmove(&(*text)->sentences_array[index_of_sentence]->words_array[index_of_word_in_sentence],
	        &(*text)->sentences_array[index_of_sentence]->words_array[index_of_word_in_sentence + 1],
			((*text)->sentences_array[index_of_sentence]->len - index_of_word_in_sentence - 1) * sizeof(struct Word*));
	free(word_to_del->word);
	free(word_to_del);
	(*(*text)->sentences_array[index_of_sentence]).len--;

}