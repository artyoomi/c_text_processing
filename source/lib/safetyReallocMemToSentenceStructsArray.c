#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef STRUCTS_H
	#define STRUCTS_H
	#include "../include/structs.h"
#endif

#ifndef SAFETY_REALLOC_MEM_TO_SENTENCE_STRUCTS_ARRAY_H
	#define SAFETY_REALLOC_MEM_TO_SENTENCE_STRUCTS_ARRAY_H
	#include "../include/safetyReallocMemToSentenceStructsArray.h"
#endif

#ifndef BLOCK_SIZE
	#define BLOCK_SIZE 5
#endif

void safetyReallocMemToSentenceStructsArray(struct Sentence*** buffer, int32_t* count_of_allocated_sentences)
{
	// сохраняем область памяти, на которую указывает buffer изначально
	struct Sentence** old_buffer = *buffer;

	// пробуем выделить память
	*buffer = (struct Sentence**)realloc(*buffer, (*count_of_allocated_sentences + BLOCK_SIZE)*sizeof(struct Sentence*));

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
			fwprintf(stderr, L"Error: failed to re-allocate memory, the part of sequence that has already been read will be returned\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		for (uint32_t i = *count_of_allocated_sentences; i < *count_of_allocated_sentences + BLOCK_SIZE; i++)
		{
			(*buffer)[i] = (struct Sentence*)malloc(sizeof(struct Sentence));

			if ((*buffer)[i] == NULL)
			{
				fwprintf(stderr, L"Error: failed to allocate memory to struct Sentence\n");
				exit(EXIT_FAILURE);
			}
		}
		*count_of_allocated_sentences += BLOCK_SIZE;
	}
}