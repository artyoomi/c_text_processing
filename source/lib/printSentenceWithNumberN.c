#include <wchar.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef STRUCTS_H
	#define STRUCTS_H
	#include "../include/structs.h"
#endif

#ifndef PRINT_SENTENCE_WITH_NUMBER_N_H
	#define PRINT_SENTENCE_WITH_NUMBER_N_H
	#include "../include/printSentenceWithNumberN.h"
#endif

void printSentenceWithNumberN(struct Text **text, const uint32_t number_of_sentence)
{
	uint32_t index_of_sentence = number_of_sentence - 1;
	if (index_of_sentence >= 0 && index_of_sentence <= (*text)->len - 1)
	{
		struct Sentence* sentence = (*text)->sentences_array[index_of_sentence];

		for (uint32_t i = 0; i < sentence->len; i++)
		{
			if (sentence->words_array[i]->punct != '\0') { wprintf(L"%ls%lc ", sentence->words_array[i]->word, sentence->words_array[i]->punct); }
			else { wprintf(L"%ls ", sentence->words_array[i]->word); }
		}
		wprintf(L"\n");
	}
	else 
	{
		fwprintf(stderr, L"Error: the sentence with the number [%u] does not exist\n", index_of_sentence);
		exit(EXIT_FAILURE);
	}
}