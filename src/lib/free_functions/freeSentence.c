#include "./freeSentence.h"

void freeSentence(struct Sentence **sentence)
{
	//wprintf(L"Count of allocated: %d\n", (*sentence)->allocated_size);
	for (uint32_t j = 0; j < (*sentence)->allocated_size; j++)
	{
		//wprintf(L"FreeWord addr: %p\n", (*sentence)->words_array[j]);
		// очищаем выделенную под слово память
		if((*sentence)->words_array[j] != NULL) {
			free((*sentence)->words_array[j]->word);
			// очищаем выделенную под структуру Word память
			free((*sentence)->words_array[j]);
		}
	}
	// очищаем выделенную под массив структур Word память
	free((*sentence)->words_array);
	// очищаем выделенную под структуру Sentence память
	free((*sentence));
	//wprintf(L"FreeSentence addr: %p\n", *sentence);
}