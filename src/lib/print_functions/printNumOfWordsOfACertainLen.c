#include "./printNumOfWordsOfACertainLen.h"

// comparator to quick sort Word structs array 
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

	// total word count
	for (uint32_t i = 0; i < (*text)->len; i++) {
		count_of_read_words += (*text)->sentences_array[i]->len;
	}


	// create Word struct array to contain all words in text
	struct Word **text_words_array = (struct Word**)malloc(count_of_read_words * sizeof(struct Word*));

	// fill words array
	uint32_t k = 0;
	for (uint32_t i = 0; i < (*text)->len; i++)
	{
		for (uint32_t j = 0; j < (*text)->sentences_array[i]->len; j++)
		{
			text_words_array[k++] = (*text)->sentences_array[i]->words_array[j];
		}
	}

	// сортируем массив слов по возрастанию длины слова
	qsort(text_words_array, count_of_read_words, sizeof(struct Word *), words_len_cmp);

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
	
	free(text_words_array);
}
