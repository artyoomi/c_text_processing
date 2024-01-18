#include "./textStructToString.h"

wchar_t *textStructToString(struct Text **text)
{
	uint32_t count_of_read_chars = 0;                 // хранит количество считанных символов
	uint32_t count_of_allocated_chars = 0; 	

	if ((*text)->len == 0) {
		wprintf(L"\033[33mWarning:\033[0m text is empty\n");
		freeText(text);
		exit(EXIT_SUCCESS);
	}

	// объявляем и выделяем память под строку, которая будет хранить текст единой строкой
	wchar_t *string_text = NULL;
	safetyReallocMemToWStr(&string_text, &count_of_allocated_chars);

	// итерируемся по предложениям текста
	for (uint32_t i = 0; i < (*text)->len; i++)
	{
		// итерирование по словам
		for (uint32_t j = 0; j < (*text)->sentences_array[i]->len; j++)
		{
			// итерирование по символам в слове
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
				// проверяем, что памяти ещё хватает
				if (count_of_read_chars == count_of_allocated_chars)
				{
					safetyReallocMemToWStr(&string_text, &count_of_allocated_chars);
				}
				// записываем знак препинания в строку
				string_text[count_of_read_chars++] = (*text)->sentences_array[i]->words_array[j]->punct;
			}

			// проверяем, что памяти ещё хватает
			if (count_of_read_chars == count_of_allocated_chars)
			{
				safetyReallocMemToWStr(&string_text, &count_of_allocated_chars);
			}

			// ставит пробел между словами
			string_text[count_of_read_chars++] = L' ';
		}
	}

	// снова проверяем, что памяти ещё хватает
	if (count_of_read_chars == count_of_allocated_chars)
	{
		safetyReallocMemToWStr(&string_text, &count_of_allocated_chars);
	}

	// переходим на новую строку и ставим знак конца строки
	string_text[count_of_read_chars - 1] = '\n';
	string_text[count_of_read_chars] = L'\0';

	return string_text;
}