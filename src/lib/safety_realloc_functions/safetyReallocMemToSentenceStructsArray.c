#include "./safetyReallocMemToSentenceStructsArray.h"

void safetyReallocMemToSentenceStructsArray(struct Sentence*** sentences_array, int32_t* count_of_allocated_sentences)
{
	// пробуем выделить память
	struct Sentence** new_sentences_array = (struct Sentence**)realloc(*sentences_array, (*count_of_allocated_sentences + BLOCK_SIZE)*sizeof(struct Sentence*));

	// если указатель на buffer == NULL, значит произошла ошибка
	if (new_sentences_array == NULL)
	{
		// если память изначально указывала на NULL, это значит что мы её выделяли впервые
		// выводим соответствующее сообщение об ошибке
		if (*sentences_array == NULL)
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
			new_sentences_array[i] = (struct Sentence*)malloc(sizeof(struct Sentence));
			new_sentences_array[i]->words_array = NULL;
			new_sentences_array[i]->is_last = 0;
			new_sentences_array[i]->len = 0;
			new_sentences_array[i]->allocated_size = 0;
			//wprintf(L"Allocate addr: %p\n", new_sentences_array[i]);


			if (new_sentences_array[i] == NULL)
			{
				fwprintf(stderr, L"Error: failed to allocate memory to struct Sentence\n");
				exit(EXIT_FAILURE);
			}
		}
		*sentences_array = new_sentences_array;
		*count_of_allocated_sentences += BLOCK_SIZE;
	}
}