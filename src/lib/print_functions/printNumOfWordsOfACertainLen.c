#include <wchar.h>
#include <stdlib.h>

#ifndef STRUCTS_H
	#define STRUCTS_H
	#include "../../include/structs.h"
#endif

#ifndef SAFETY_REALLOC_MEM_TO_WORD_STRUCTS_ARRAY_H
	#define SAFETY_REALLOC_MEM_TO_WORD_STRUCTS_ARRAY_H
	#include "../../include/safety_realloc_functions/safetyReallocMemToWordStructsArray.h"
#endif

int32_t words_len_cmp(const void *w1, const void *w2)
{
	const uint32_t len1 = (*(*((struct Word **)w1))).len;
	const uint32_t len2 = (*(*((struct Word **)w2))).len;

	if (len1 > len2) { return 1; }
	else if (len1 == len2) { return 0; }
	else { return -1; }
}

void printNumOfWordsOfACertainLen(struct Text **const text)
{
	uint32_t count_of_read_words = 0;
	uint32_t count_of_allocated_words = 0;

	struct Word **text_words_array = NULL;
	safetyReallocMemToWordStructsArray(&text_words_array, &count_of_allocated_words);

	// запроняем массив слов
	for (uint32_t i = 0; i < (*text)->len; i++)
	{
		for (uint32_t j = 0; j < (*text)->sentences_array[i]->len; j++)
		{
			if (count_of_read_words >= count_of_allocated_words) { safetyReallocMemToWordStructsArray(&text_words_array, 
																									  &count_of_allocated_words); }
			text_words_array[count_of_read_words++] = (*text)->sentences_array[i]->words_array[j];
		}
	}

	// сортируем массив слов по возрастанию длины слова
	qsort(text_words_array, count_of_read_words, sizeof(struct Word *), words_len_cmp);

	// проверяем, что текст не пуст
	if (count_of_read_words == 0)
	{
		wprintf(L"\033[33mWarning: text is empty\n");
	}
	else
	{
		//wprintf(L"Words with certain lens\n");
	}

	// выводим длину слова, и слова этой длины
	uint32_t curr_len = 0;
	for (uint32_t k = 0; k < count_of_read_words; k++)
	{
		if (curr_len != text_words_array[k]->len)
		{
			if (curr_len != 0) { wprintf(L")\n"); }
			wprintf(L"%ld: (%ls", text_words_array[k]->len, text_words_array[k]->word);
			curr_len = text_words_array[k]->len;
			if (k + 1 == count_of_read_words) { wprintf(L")\n"); }
			continue;
		}

		wprintf(L" %ls", text_words_array[k]->word);
		if (k + 1 == count_of_read_words) { wprintf(L")\n"); }
	}
}
