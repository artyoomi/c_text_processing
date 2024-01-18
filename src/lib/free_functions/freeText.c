#include "./freeText.h"

void freeText(struct Text **text)
{
	// проходимся по предложениям в тексте
	for (uint32_t i = 0; i < (*text)->allocated_size; i++)
	{
		// проходимя по словам в каждом предложении
		if((*text)->sentences_array[i] != NULL) {
			freeSentence(&((*text)->sentences_array[i]));
		}
	}
	free((*text)->sentences_array);	
	free(*text);
}