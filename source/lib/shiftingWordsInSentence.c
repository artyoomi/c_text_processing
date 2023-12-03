// возвращает текст, с ихзменённым предложением номер N


#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef STRUCTS_H
	#define STRUCTS_H
	#include "../include/structs.h"
#endif

#ifndef SHIFTING_WORDS_IN_SENTENCE_H
	#define SHIFTING_WORDS_IN_SENTENCE_H
	#include "../include/shiftingWordsInSentence.h"
#endif

void shiftingWordsInSentence(struct Text **text, const uint32_t number_of_sentence, const uint32_t number_of_shifts)
{
	struct Sentence *sentence;
	// находим индекс предложения
	uint32_t index_of_sentence = number_of_sentence - 1;

	// проверяем, что предложение с полученным номером существует в тексте
	if (index_of_sentence >= 0 && index_of_sentence <= (*text)->len - 1) { sentence = (*text)->sentences_array[index_of_sentence]; }
	else 
	{
		fwprintf(stderr, L"Error: the sentence with the number [%u] does not exist\n", number_of_sentence);
		exit(EXIT_FAILURE);
	}

	// если структура предложения не ссылкается ни на какой массив слов, то оно пусто
	if (sentence->words_array == NULL)
	{
		fwprintf(stderr, L"Error: the sentence is empty\n");
		exit(EXIT_FAILURE);
	}

	// если подано количество сдвигов, равное 0, то обрабатывать далее смысла нет
	if (number_of_shifts == 0) { exit(EXIT_SUCCESS); }
	else
	{
		// убираем точку у последнего слова, чтобы в конце поставить её после нового последнего слова
		sentence->words_array[sentence->len - 1]->punct = '\0';

		struct Sentence *temp_sentence = (struct Sentence*)malloc(sizeof(struct Sentence));
		temp_sentence->words_array = (struct Word**)malloc(sentence->len * sizeof(struct Word*));

		//<REVIEW> comment
		//<REVIEW> while -> for
		//temp_sentence->words_array = sentence->words_array;

		//<REVIEW> comments under
		//uint32_t ind = 0;
		//while(ind != sentence->len)
		for (uint32_t ind = 0; ind < sentence->len; ind++)
		{
			temp_sentence->words_array[(ind + number_of_shifts)%(sentence->len)] = sentence->words_array[ind];
			//ind++;
		}
		sentence->words_array = temp_sentence->words_array;

		// вставляем точку после последнего предложений
		sentence->words_array[sentence->len - 1]->punct = '.';
		free(temp_sentence);
	}
}