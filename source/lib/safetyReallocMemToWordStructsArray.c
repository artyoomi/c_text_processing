#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef STRUCTS_H
	#define STRUCTS_H
	#include "../include/structs.h"
#endif

#ifndef SAFETY_REALLOC_MEM_TO_WORD_STRUCTS_ARRAY_H
	#define SAFETY_REALLOC_MEM_TO_WORD_STRUCTS_ARRAY_H
	#include "../include/safetyReallocMemToWordStructsArray.h"
#endif

#ifndef BLOCK_SIZE
	#define BLOCK_SIZE 5
#endif

void safetyReallocMemToWordStructsArray(struct Word*** buffer, int32_t* count_of_allocated_words)
{
	// сохраняем область памяти, на которую указывает buffer изначально
	struct Word** old_buffer = *buffer;

	// пробуем выделить память
	*buffer = (struct Word**)realloc(*buffer, (*count_of_allocated_words + BLOCK_SIZE)*sizeof(struct Word*));

	// если указатель на buffer == NULL, значит произошла ошибка
	if (*buffer == NULL)
	{
		// если память изначально указывала на NULL, это значит что мы её выделяли впервые
		// выводим соответствующее сообщение об ошибке
		if (old_buffer == NULL)
		{
			fwprintf(stderr, L"Error: failed to allocate memory\n");
			exit(EXIT_FAILURE);
		}
		// иначе была ошибка при перевыделении
		else
		{
			fwprintf(stderr, L"Error: failed to re-allocate memory\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		for (uint32_t i = *count_of_allocated_words; i < *count_of_allocated_words + BLOCK_SIZE; i++)
		{
			(*buffer)[i] = (struct Word*)malloc(sizeof(struct Word));
			if ((*buffer)[i] == NULL)
			{
				fwprintf(stderr, L"Error: failed to allocate memory to struct Word\n");
				exit(EXIT_FAILURE);
			}
		}
		*count_of_allocated_words += BLOCK_SIZE;
	}
}