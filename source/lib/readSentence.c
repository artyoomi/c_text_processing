#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>

#ifndef STRUCTS_H
	#define STRUCTS_H
	#include "../include/structs.h"
#endif

#ifndef READ_SENTENCE_H
	#define READ_SENTENCE_H
	#include "../include/readSentence.h"
#endif

#ifndef SAFETY_REALLOC_MEM_TO_WORD_STRUCTS_ARRAY_H
	#define SAFETY_REALLOC_MEM_TO_WORD_STRUCTS_ARRAY_H
	#include "../include/safetyReallocMemToWordStructsArray.h"
#endif

#ifndef SAFETY_REALLOC_MEM_TO_WSTR_H
	#define SAFETY_REALLOC_MEM_TO_WSTR_H
	#include "../include/safetyReallocMemToWStr.h"
#endif

struct Sentence* readSentence()
{
	// выделяем память под структуру Sentence и инициализируем флаг is_last нулём
	struct Sentence *sentence = (struct Sentence*)malloc( sizeof(struct Sentence) );
	sentence->is_last = 0;

	uint32_t count_of_read_chars = 0;               // хранит количество считанных символов
	uint32_t count_of_allocated_chars = 0;          // хранит количество символов, под которые выделена память

	uint32_t count_of_read_words = 0;               // хранит количество считанных слов
	uint32_t count_of_allocated_words = 0;          // хранит количество слов, под которые выделена память  

	wchar_t c = getwchar();                         // хранит текущий символ
	wchar_t prev_c = '\0';                          // хранит предыдущий символ

	uint8_t in_word = 0;                            // флаг нахождения внутри слова
	
	// определяем массив указателей на структуры Word и выделяем под него память
	struct Word **words_array = NULL;
	safetyReallocMemToWordStructsArray(&words_array, &count_of_allocated_words);

	while (1)
	{
		// если последний знак препинания равен точке, то это значит что предложение закончилось
		if (c == L'.' && count_of_read_words >= 1)
		{
			if (words_array[count_of_read_words - 1]->punct == L'.') { break; }
		}

		// проверяем условие начала слова
		if (!in_word && !iswspace(c) && c != L',' && c != L'.')
		{
			safetyReallocMemToWStr(&(words_array[count_of_read_words]->word), &count_of_allocated_chars);
			words_array[count_of_read_words]->word[count_of_read_chars++] = c;
			in_word = 1;

		}
		// проверяем какие знаки стоят после слова и записываем 
		else if (count_of_read_words >= 1 && !in_word)
		{
			// если точка, то дальше проверять смысла нет, присваивает точку структуре и выходим из цикла
			if (c == L'.' && words_array[count_of_read_words - 1]->punct != L'.')
			{
				words_array[count_of_read_words - 1]->punct = L'.';
				break;
			}
			
			// если в промежутке между словами появилась запятая
			else if (c == ',' && words_array[count_of_read_words - 1]->punct == L'\0')
			{
				words_array[count_of_read_words - 1]->punct = L',';
			}
		}
		else
		{
			// проверяем, что мы попали в слово
			if (in_word)
			{
				// пока в слове выполняем
				while(in_word)
				{
					// если символ допустимый - записываем его в слово
					if (!iswspace(c) && c != L',' && c != L'.')
					{
						// проверяем, что памяти ещё хватает, если нет - выделяем ещё
						if (count_of_read_chars + 1 >= count_of_allocated_chars)
						{
							safetyReallocMemToWStr(&words_array[count_of_read_words]->word,
							                       &count_of_allocated_chars);
						}

						words_array[count_of_read_words]->word[count_of_read_chars++] = c;

						prev_c = c;
						c = getwchar();
						continue;
					}
					else
					{
						if (count_of_read_words + 1 >= count_of_allocated_words)
						{
							safetyReallocMemToWordStructsArray(&words_array, &count_of_allocated_words);
						}
						
						in_word = 0;
						words_array[count_of_read_words]->word[count_of_read_chars] = L'\0';
						

						//words_array[count_of_read_words]->word = (wchar_t *)realloc(words_array[count_of_read_words]->word, (count_of_read_chars + 1) * sizeof(wchar_t));

						// сохраняем длину слова
						words_array[count_of_read_words]->len = count_of_read_chars;
						
						// сохраняем знак после слова
						if (c == L',' || c == L'.') { words_array[count_of_read_words]->punct = c; }
						else { words_array[count_of_read_words]->punct = '\0'; }

						count_of_read_chars = 0;
						count_of_allocated_chars = 0;

						count_of_read_words++;
					}
				}
				continue;
			}
		}

		if (c == L'\n' && prev_c == L'\n')
			{
				if (count_of_read_words >= 1)
				{
					words_array[count_of_read_words - 1]->punct = L'.';
				}
				sentence->is_last = 1;
				break;
			}

		prev_c = c;
		c = getwchar();
	}

	// если не было считано ни одного слова, то
	if (count_of_read_words == 0)
	{
		free(words_array);
		sentence->words_array = NULL;
		sentence->len = 0;
	}
	else
	{
		sentence->words_array = words_array;
		sentence->len = count_of_read_words;
	}

	return sentence;
}