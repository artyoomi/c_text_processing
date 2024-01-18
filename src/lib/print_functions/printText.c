#include "./printText.h"

void printText(struct Text **text)
{
	struct Sentence** sentences_array = (*text)->sentences_array;

	if ((*text)->len == 0)
	{
		wprintf(L"\033[33mWarning:\033[0m text is empty\n");
	}
	// перебор предложений текста
	for (uint32_t i = 0; i < (*text)->len; i++)
	{
		struct Sentence* sentence = sentences_array[i];

		// перебор слов текста
		for (uint32_t j = 0; j < sentence->len; j++)
		{
			if ((sentence->words_array)[j]->punct == L'.') { wprintf(L"%ls%lc", sentence->words_array[j]->word, sentence->words_array[j]->punct); }

			else if ((sentence->words_array)[j]->punct != L'\0') { wprintf(L"%ls%lc ", sentence->words_array[j]->word, sentence->words_array[j]->punct); }

			else { wprintf(L"%ls ", (sentence->words_array)[j]->word); }
		}
		wprintf(L"\n");
	}
}