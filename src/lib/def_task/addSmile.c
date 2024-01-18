#include "./addSmile.h"

void addSmile(struct Text **text)
{	
	for (uint32_t i = 0; i < (*text)->len; i++)
	{
		for (uint32_t j = 0; j < (*text)->sentences_array[i]->len; j++)
		{
			if (!wcscmp((*text)->sentences_array[i]->words_array[j]->word, L"smile"))
			{
				(*text)->sentences_array[i]->words_array[j]->word = wcsncat((*text)->sentences_array[i]->words_array[j]->word,
																			L" :=)",
																			wcslen((*text)->sentences_array[i]->words_array[j]->word) + 5);
				(*text)->sentences_array[i]->words_array[j]->len += 4;
				(*text)->sentences_array[i]->words_array[j]->allocated_size += 5;
			}
		}
	}
}