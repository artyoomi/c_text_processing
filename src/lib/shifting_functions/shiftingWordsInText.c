#include "./shiftingWordsInText.h"

void shiftingWordsInText(struct Text **text, const uint32_t number_of_shifts)
{
	// если подано количество сдвигов, равное 0, то обрабатывать далее смысла нет
	if (number_of_shifts > 0 && (*text)->len >= 2)
	{
		for (uint32_t i = 0; i < (*text)->len; i++)
		{
			struct Sentence *sentence = (*text)->sentences_array[i];

			// убираем точку у последнего слова, чтобы в конце поставить её после нового последнего слова
			sentence->words_array[sentence->len - 1]->punct = '\0';
			struct Word** new_words_array = (struct Word**)malloc(sentence->allocated_size*sizeof(struct Word*));

			uint32_t new_ind;
			for(uint32_t j = 0; j < sentence->len; j++) {
				new_ind = (j + number_of_shifts)%(sentence->len);
				new_words_array[new_ind] = sentence->words_array[j];
			}

			for(uint32_t j = sentence->len; j < sentence->allocated_size; j++) {
				new_words_array[j] = sentence->words_array[j];
			}
			free(sentence->words_array);
			sentence->words_array = new_words_array;
			sentence->words_array[sentence->len - 1]->punct = L'.';
		}
	}
}