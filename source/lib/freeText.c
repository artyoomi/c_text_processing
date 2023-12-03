#include <stdlib.h>
#include <stdint.h>

#ifndef STRUCTS_H
	#define STRUCTS_H
	#include "../include/structs.h"
#endif

#ifndef FREE_TEXT_H
	#define FREE_TEXT_H
	#include "../include/freeText.h"
#endif

//<REVIEW>
void freeText(struct Text **text)
{
	// проходимся по предложениям в тексте
	for (uint32_t i = 0; i < (*text)->len; i++)
	{
		// проходимя по словам в каждом предложении
		for (uint32_t j = 0; j < (*text)->sentences_array[i]->len; j++)
		{
			// очищаем выделенную под слово память
			free((*text)->sentences_array[i]->words_array[j]->word);
			// очищаем выделенную под структуру Word память
			free((*text)->sentences_array[i]->words_array[j]);
		}
		// очищаем выделенную под массив структур Word память
		free((*text)->sentences_array[i]->words_array);
		// очищаем выделенную под структуру Sentence память
		free((*text)->sentences_array[i]);
	}
	free((*text)->sentences_array);	
	free(*text);
}