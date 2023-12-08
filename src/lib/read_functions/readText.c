#include <wchar.h>
#include <stdlib.h>

#ifndef STRUCTS_H
	#define STRUCTS_H
	#include "../../include/structs.h"
#endif

#ifndef READ_TEXT_H
	#define READ_TEXT_H
	#include "../../include/read_functions/readText.h"
#endif

#ifndef READ_SENTENCE_H
	#define READ_SENTENCE_H
	#include "../../include/read_functions/readSentence.h"
#endif

#ifndef SAFETY_REALLOC_MEM_TO_SENTENCE_STRUCTS_ARRAY_H
	#define SAFETY_REALLOC_MEM_TO_SENTENCE_STRUCTS_ARRAY_H
	#include "../../include/safety_realloc_functions/safetyReallocMemToSentenceStructsArray.h"
#endif

#define TRUE 1

struct Text* readText()
{
	// объявление результирующей структуры Text и иницализиация её значений
	struct Text *text = (struct Text *)malloc(sizeof(struct Text));
	text->sentences_array = NULL;
	text->len = 0;

	struct Sentence* curr_sentence = NULL;          // хранит считанное предложение

	uint32_t count_of_read_sentences = 0;           // хранит количество считанных предложений
	uint32_t count_of_allocated_sentences = 0;      // хранит количество предложений, под которые выделеан память

	while (TRUE)
	{
		// проверяем, что всё ещё хватает памяти для сохранения предложений
		if (count_of_read_sentences >= count_of_allocated_sentences) {
			safetyReallocMemToSentenceStructsArray(&(text->sentences_array),
						                           &count_of_allocated_sentences);
		}

		curr_sentence = readSentence();

		// обрабатываем случай последнего предложения
		if (curr_sentence->is_last)
		{
			// если функция чтения предложения вернула пустой массив words_array, делаем break
			if (curr_sentence->words_array == NULL)
			{
				free(curr_sentence);
				if (count_of_read_sentences >= 1)
				{
					text->sentences_array[count_of_read_sentences - 1]->is_last = 1;
				}
				break;
			}
			else
			{
				text->sentences_array[count_of_read_sentences] = curr_sentence;
				count_of_read_sentences++;
				break;
			}
		}
		text->sentences_array[count_of_read_sentences] = curr_sentence;
		count_of_read_sentences++;
	}

	text->len = count_of_read_sentences;

	return text;
}