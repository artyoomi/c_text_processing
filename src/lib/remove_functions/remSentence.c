#include "./remSentence.h"

void remSentence(struct Text **text, const uint32_t index_of_sentence)
{
	freeSentence(&((*text)->sentences_array[index_of_sentence]));

	for(uint32_t i = index_of_sentence; i < (*text)->len-1; i++) {
		(*text)->sentences_array[i] = (*text)->sentences_array[i+1];
	}
	(*text)->sentences_array[(*text)->len-1] = NULL;
	(*text)->len--;
}
