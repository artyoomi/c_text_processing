#include "./safetyReallocMemToWordStructsArray.h"

void safetyReallocMemToWordStructsArray(struct Word*** words_array, int32_t* count_of_allocated_words)
{
	// пробуем выделить память
	struct Word** new_words_array = (struct Word**)realloc(*words_array, (*count_of_allocated_words + BLOCK_SIZE)*sizeof(struct Word*));

	// если указатель на buffer == NULL, значит произошла ошибка
	if (new_words_array == NULL)
	{
		// если память изначально указывала на NULL, это значит что мы её выделяли впервые
		// выводим соответствующее сообщение об ошибке
		if (*words_array == NULL)
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
			new_words_array[i] = (struct Word*)malloc(sizeof(struct Word));
			new_words_array[i]->word = NULL;
			new_words_array[i]->punct = L'\0';
			new_words_array[i]->len = 0;
			new_words_array[i]->allocated_size = 0;
			//wprintf(L"Allocate addr: %p\n", new_words_array[i]);

			
			if (new_words_array[i] == NULL)
			{
				fwprintf(stderr, L"Error: failed to allocate memory to struct Word\n");
				exit(EXIT_FAILURE);
			}
		}

		*words_array = new_words_array;
		*count_of_allocated_words += BLOCK_SIZE;
	}
}