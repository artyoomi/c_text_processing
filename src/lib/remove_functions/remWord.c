#include "./remWord.h"

void remWord(struct Sentence **sentence, const uint32_t index_of_word)
{
	//free(&((*text)->sentences_array[index_of_sentence]));
	free((*sentence)->words_array[index_of_word]->word);
	free((*sentence)->words_array[index_of_word]);

	for(uint32_t i = index_of_word; i < (*sentence)->len-1; i++) {
		(*sentence)->words_array[i] = (*sentence)->words_array[i+1];
	}
	(*sentence)->words_array[(*sentence)->len-1] = NULL;
	(*sentence)->len--;

	/*struct Word *word_to_del = (*text)->sentences_array[index_of_sentence]->words_array[index_of_word_in_sentence];
	memmove(&(*text)->sentences_array[index_of_sentence]->words_array[index_of_word_in_sentence],
	        &(*text)->sentences_array[index_of_sentence]->words_array[index_of_word_in_sentence + 1],
			((*text)->sentences_array[index_of_sentence]->len - index_of_word_in_sentence - 1) * sizeof(struct Word*));
	free(word_to_del->word);
	free(word_to_del);
	(*(*text)->sentences_array[index_of_sentence]).len--;*/
}