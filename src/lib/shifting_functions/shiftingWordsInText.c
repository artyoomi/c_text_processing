#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef STRUCTS_H
	#define STRUCTS_H
	#include "../../include/structs.h"
#endif

#ifndef SHIFTING_WORDS_IN_SENTENCE_H
	#define SHIFTING_WORDS_IN_TEXT_H
	#include "../../include/shifting_functions/shiftingWordsInText.h"
#endif

void shiftingWordsInText(struct Text **text, const uint32_t number_of_shifts)
{
	// если подано количество сдвигов, равное 0, то обрабатывать далее смысла нет
	if (number_of_shifts > 0)
	{
		for (uint32_t i = 0; i < (*text)->len; i++)
		{
			struct Sentence *sentence = (*text)->sentences_array[i];

			// убираем точку у последнего слова, чтобы в конце поставить её после нового последнего слова
			sentence->words_array[sentence->len - 1]->punct = '\0';

			struct Sentence *temp_sentence = (struct Sentence*)malloc(sizeof(struct Sentence));
			temp_sentence->words_array = (struct Word**)malloc(sentence->len * sizeof(struct Word*));


			for (uint32_t ind = 0; ind < sentence->len; ind++)
			{
				temp_sentence->words_array[(ind + number_of_shifts)%(sentence->len)] = sentence->words_array[ind];
			}
			sentence->words_array = temp_sentence->words_array;

			// вставляем точку после последнего предложений
			sentence->words_array[sentence->len - 1]->punct = '.';
			free(temp_sentence);
		}
	}
}