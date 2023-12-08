#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef STRUCTS_H
	#define STRUCTS_H
	#include "../include/structs.h"
#endif

#ifndef TEXT_STRUCT_TO_STRING
	#define TEXT_STRUCT_TO_STRING
	#include "../include/textStructToString.h"
#endif

#ifndef SAFETY_REALLOC_MEM_TO_WSTR_H
	#define SAFETY_REALLOC_MEM_TO_WSTR_H
	#include "../include/safety_realloc_functions/safetyReallocMemToWStr.h"
#endif

wchar_t *textStructToString(struct Text **text)
{
	uint32_t count_of_read_chars = 0;                 // хранит количество считанных символов
	uint32_t count_of_allocated_chars = 0;			  // хранит количество выделенных единиц памяти для символов

	// объявляем и выделяем память под строку, которая будет хранить текст единой строкой
	wchar_t *string_text = NULL;
	safetyReallocMemToWStr(&string_text, &count_of_allocated_chars);

	// итерируемся по предложениям текста
	for (uint32_t i = 0; i < (*text)->len; i++)
	{
		// итерирование по словам
		for (uint32_t j = 0; j < (*text)->sentences_array[i]->len; j++)
		{
			// итерирование по символам слов
			for (uint32_t k = 0; k < (*text)->sentences_array[i]->words_array[j]->len; k++)
			{
				// проверяем, что памяти ещё хватает
				if (count_of_read_chars >= count_of_allocated_chars)
				{
					safetyReallocMemToWStr(&string_text, &count_of_allocated_chars);
				}

				// записываем очередной символ
				string_text[count_of_read_chars++] = (*text)->sentences_array[i]->words_array[j]->word[k];
			}

			// если знак препинания у слова есть
			if ((*text)->sentences_array[i]->words_array[j]->punct != L'\0')
			{
				if (count_of_read_chars == count_of_allocated_chars)
				{
					safetyReallocMemToWStr(&string_text, &count_of_allocated_chars);
				}

				string_text[count_of_read_chars++] = (*text)->sentences_array[i]->words_array[j]->punct;
			}

			if (count_of_read_chars == count_of_allocated_chars)
			{
				safetyReallocMemToWStr(&string_text, &count_of_allocated_chars);
			}

			string_text[count_of_read_chars++] = L' ';
		}
	}

	if (count_of_read_chars == count_of_allocated_chars)
	{
		safetyReallocMemToWStr(&string_text, &count_of_allocated_chars);
	}

	// если количество считанных символов равно нулю, освобождаем память
	if (count_of_read_chars == 0)
	{
		free(string_text);
		fwprintf(stderr, L"\033[33mWarning:\033[0m text is empty\n");
		exit(EXIT_SUCCESS);
	}

	// переходим на новую строку и ставим знак конца строки
	string_text[count_of_read_chars - 1] = '\n';
	string_text[count_of_read_chars] = L'\0';

	return string_text;
}