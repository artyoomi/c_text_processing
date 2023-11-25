#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <stdint.h>
#include <string.h>

#include "./include/printWelcomeMessage.h"
#include "./include/printManual.h"

#define BLOCK_SIZE 5

struct Word
{
	wchar_t* word;
	wchar_t punct;
    uint32_t len;
};

struct Sentence
{
	struct Word** words_array;
	uint16_t is_last;
	uint32_t len;
};

struct Text
{
	struct Sentence** sentences_array;
	uint32_t len;
};

void safetyReallocMemToWStr(wchar_t** buffer, int32_t* count_of_allocated_chars)
{
	// сохраняем область памяти, на которую указывает buffer изначально
	wchar_t* old_buffer = *buffer;
	// пробуем выделить память
	*buffer = (wchar_t*)realloc(*buffer, (*count_of_allocated_chars + BLOCK_SIZE)*sizeof(wchar_t));

	// если указатель на buffer == NULL, значит произошла ошибка
	if (*buffer == NULL)
	{
		// если память изначально указывала на NULL, это значит что мы её выделяли впервые
		// выводим соответствующее сообщение об ошибке
		if (old_buffer == NULL)
		{
			fwprintf(stderr, L"error: failed to allocate memory\n");
			exit(0);
		}
		// иначе была ошибка при перевыделении
		else
		{
			*buffer = old_buffer;
			fwprintf(stderr, L"error: failed to re-allocate memory, the part of sequence that has already been read will be returned\n");
			exit(0);
		}
	}
	else
	{
		*count_of_allocated_chars += BLOCK_SIZE;
	}
}

void safetyReallocMemToWordsArray(struct Word*** buffer, int32_t* count_of_allocated_words)
{
	// сохраняем область памяти, на которую указывает buffer изначально
	struct Word** old_buffer = *buffer;
	// пробуем выделить память
	*buffer = (struct Word**)realloc(*buffer, (*count_of_allocated_words + BLOCK_SIZE)*sizeof(struct Word*));
	for (uint32_t i = *count_of_allocated_words; i < *count_of_allocated_words + BLOCK_SIZE; i++)
	{
		(*buffer)[i] = (struct Word*)malloc(sizeof(struct Word));
		if ((*buffer)[i] == NULL)
		{
			fwprintf(stderr, L"error: failed to allocate memory to struct Word\n");
			exit(0);
		}
	}

	// если указатель на buffer == NULL, значит произошла ошибка
	if (*buffer == NULL)
	{
		// если память изначально указывала на NULL, это значит что мы её выделяли впервые
		// выводим соответствующее сообщение об ошибке
		if (old_buffer == NULL)
		{
			fwprintf(stderr, L"error: failed to allocate memory\n");
			exit(0);
		}
		// иначе была ошибка при перевыделении
		else
		{
			*buffer = old_buffer;
			fwprintf(stderr, L"error: failed to re-allocate memory, the part of sequence that has already been read will be returned\n");
			exit(0);
		}
	}
	else
	{
		*count_of_allocated_words += BLOCK_SIZE;
	}
}

void safetyReallocMemToSentencesArray(struct Sentence*** buffer, int32_t* count_of_allocated_sentences)
{
	// сохраняем область памяти, на которую указывает buffer изначально
	struct Sentence** old_buffer = *buffer;

	// пробуем выделить память
	*buffer = (struct Sentence**)realloc(*buffer, (*count_of_allocated_sentences + BLOCK_SIZE)*sizeof(struct Sentence*));
	for (uint32_t i = *count_of_allocated_sentences; i < *count_of_allocated_sentences + BLOCK_SIZE; i++)
	{
		(*buffer)[i] = (struct Sentence*)malloc(sizeof(struct Sentence));

		if ((*buffer)[i] == NULL)
		{
			fwprintf(stderr, L"error: failed to allocate memory to struct Sentence\n");
			exit(0);
		}
	}

	// если указатель на buffer == NULL, значит произошла ошибка
	if (*buffer == NULL)
	{
		// если память изначально указывала на NULL, это значит что мы её выделяли впервые
		// выводим соответствующее сообщение об ошибке
		if (old_buffer == NULL)
		{
			fwprintf(stderr, L"error: failed to allocate memory\n");
			exit(0);
		}
		// иначе была ошибка при перевыделении
		else
		{
			*buffer = old_buffer;
			fwprintf(stderr, L"error: failed to re-allocate memory, the part of sequence that has already been read will be returned\n");
			exit(0);
		}
	}
	else
	{
		*count_of_allocated_sentences += BLOCK_SIZE;
	}
}

struct Sentence* readSentence()
{
	struct Sentence *sentence = (struct Sentence*)malloc( sizeof(struct Sentence) );

	uint32_t count_of_read_words = 0, count_of_allocated_words = 0;

	// определяем массив указателей на структуры Word и выделяем под него память
	//struct Word **words_array = (struct Word**)malloc( BLOCK_SIZE * sizeof(struct Word*) );
	//for (size_t i = 0; i < BLOCK_SIZE; i++) { words_array[i] = (struct Word*)malloc(sizeof(struct Word)); }
	struct Word **words_array = NULL;
	safetyReallocMemToWordsArray(&words_array, &count_of_allocated_words);

	int32_t count_of_read_chars = 0, count_of_allocated_chars = 0;

	wchar_t c = getwchar(), prev_c = '\0';

	uint8_t in_word = 0, is_last = 0;

	wchar_t punct = L'\0';

	while (1)
	{
		// если последний знак препинания равен точке, то это значит что предложение закончилось
		if (c == L'.' && count_of_read_words >= 1)
		{
			if (words_array[count_of_read_words - 1]->punct == L'.')
			{
				break;
			}
		}
		/*else
		{
			if (words_array[0]->punct == L'.')
			{
				break;
			}
		}*/

		// проверяем условие начала слова
		if (!in_word && !iswspace(c) && c != L',' && c != L'.')
		{
			safetyReallocMemToWStr(&words_array[count_of_read_words]->word, &count_of_allocated_chars);
			in_word = 1;
			words_array[count_of_read_words]->word[count_of_read_chars++] = c;

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
			else if (c == ',' && words_array[count_of_read_words - 1]->punct == L'\0') { words_array[count_of_read_words - 1]->punct = L','; }
		}
		else
		{
			if (in_word)
			{
				while(in_word)
				{
					// если символ допустимый - записываем его в слово
					if (!iswspace(c) && c != L',' && c != L'.')
					{
						// проверяем, что памяти ещё хватает, если нет - выделяем ещё
						if (count_of_read_chars + 1 > count_of_allocated_chars) { safetyReallocMemToWStr(&words_array[count_of_read_words]->word, &count_of_allocated_chars); }

						words_array[count_of_read_words]->word[count_of_read_chars++] = c;

						prev_c = c;
						c = getwchar();
						continue;
					}
					else
					{
						in_word = 0;
						words_array[count_of_read_words]->word[count_of_read_chars] = L'\0';

						if (count_of_read_words + 1 >= count_of_allocated_words) { safetyReallocMemToWordsArray(&words_array, &count_of_allocated_words); }

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
				is_last = 1;
				break;
			}

		prev_c = c;
		c = getwchar();
	}

	sentence->words_array = words_array;
	sentence->len = count_of_read_words;
	sentence->is_last = is_last;

	return sentence;
}	

struct Text* readText()
{
	// объявление результирующей структуры Text
	struct Text* text = (struct Text*)malloc(sizeof(struct Text));
	text->sentences_array = NULL;
	text->len = 0;

	struct Sentence* curr_sentence;

	uint32_t count_of_read_sentences = 0, count_of_allocated_sentences = 0;

	while (1)
	{
		if (count_of_read_sentences >= count_of_allocated_sentences) { safetyReallocMemToSentencesArray(&(text->sentences_array), &count_of_allocated_sentences); }

		curr_sentence = readSentence();

		// обрабатываем случай последнего предложения
		if (curr_sentence->is_last)
		{
			// если функция чтения предложения вернула пустой массив words_array, делаем break
			if (curr_sentence->words_array[0]->word == NULL) { break; }
			else
			{
				text->sentences_array[count_of_read_sentences] = curr_sentence;
				count_of_read_sentences++;
				break;
			}
		}
		text->sentences_array[count_of_read_sentences] = curr_sentence;
		count_of_read_sentences++;
	}

	text->len = count_of_read_sentences;

	return text;
}

void remSentence(struct Text **text, uint32_t index_of_sentence)
{
	//struct Sentence *sentence = (*text)->sentences_array[index_of_sentence];
	/*wprintf(L"i is [%ls] | i + 1 is [%ls]\n", (*text)->sentences_array[0]->words_array[0]->word, (*text)->sentences_array[1]->words_array[0]->word);
	free(sentence);
	(*(*text)).len--;
	
	// сдвигаем все значения sentence_array на один влево
	for (uint32_t i = index_of_sentence; i < ((*text)->len - 1); i++)
	{
		(*text)->sentences_array[i] = (*text)->sentences_array[i + 1];
		free((*text)->sentences_array[i + 1]);
		//wprintf(L"i is [%ls]\n", (*text)->sentences_array[i]->words_array[0]->word);
	}*/

	/*if (index_of_sentence < (*text)->len - 1)
	{
		(*text)->sentences_array[index_of_sentence] = memmove(&(*text)->sentences_array[index_of_sentence], &(*text)->sentences_array[index_of_sentence + 1], ((*text)->len - index_of_sentence - 1) * sizeof(struct Sentence*));
		free((*text)->sentences_array[(*text)->len - 1]);
	}
	else
	{
		free(sentence);
	}
	printText(text);*/
	struct Sentence *sentence_to_del = (*text)->sentences_array[index_of_sentence];
    memmove(&(*text)->sentences_array[index_of_sentence], &(*text)->sentences_array[index_of_sentence + 1], ((*text)->len - index_of_sentence - 1) * sizeof(struct Sentence *));
    free(sentence_to_del);
    (*(*text)).len--;
}

void remDupFromText(struct Text** text)
{
	// флаг равенства предложений

	uint8_t flag = 0;
	
	// индекс фиксрованного предложения
	uint32_t i = 0;
	while(1)
	{
		struct Sentence *sentence1;
		// фиксируем предложение
		if(i <= (*text)->len - 1) { sentence1 = (*text)->sentences_array[i]; }
		else { break; }

		// проверяем, что в тексте есть следующиее за зафиксированным предложение
		if (!sentence1->is_last)
		{
			uint32_t j = i + 1;

			// проходимся по всем предложениям, начиная от следующего после зафиксированного
			while(1)
			{
				struct Sentence *sentence2;

				// проверяем, что j ещё не вышел за пределы допустимых индексов
				if (j <= (*text)->len - 1) { sentence2 = (*text)->sentences_array[j]; } 
				else { break; }

				// если количество слов в предложении разное, то дальше проверять смысла нет
				if (sentence1->len != sentence2->len)
				{
					j++;
					continue;
				}
				else
				{
					// сраниваем каждое слово и его знак препинания
					for (uint32_t k = 0; k < sentence1->len; k++)
					{
						if (!wcscasecmp(sentence1->words_array[k]->word, sentence2->words_array[k]->word) && sentence1->words_array[k]->punct == sentence2->words_array[k]->punct)
						{
							flag = 1;
						}
						else
						{
							flag = 0;
							break;
						}	
					}
				}
				if (flag)
				{
					remSentence(&(*text), j);
					//printText(&(*text));
					//wprintf(L"\n");
					flag = 0;
				}
				else{ j++; }
			}
		}
		// если за зафиксированным больше нет предложений - выходим из цикла
		else
		{
			break;
		}
		i++;
	}
}

void printText(struct Text **text)
{
	struct Sentence** sentences_array = (*text)->sentences_array;

	// перебор предложений текста
	for (uint32_t i = 0; i < (*text)->len; i++)
	{
		struct Sentence* sentence = sentences_array[i];

		// перебор слов текста
		for (uint32_t j = 0; j < sentence->len; j++)
		{
			if ((sentence->words_array)[j]->punct != L'\0') { wprintf(L"%ls%lc ", sentence->words_array[j]->word, sentence->words_array[j]->punct); }

			else { wprintf(L"%ls ", (sentence->words_array)[j]->word); }
		}
		//if (!(sentence->is_last)) { wprintf(L"\n"); }
		wprintf(L"\n");
	}
}

int main()
{
	setlocale(LC_ALL, "");
	// вывод сообщения с информацией о варианте и ФИО студента
	//printWelcomeMessage();

	// чтениe номера действия (доработать)
	int N;
	wscanf(L"%d", &N);

	if (N > 5 || N < 0)
	{
		fwprintf(stderr, L"error: wrong option\n");
	}
	else
	{
		if (N == 5) { /*printManual();*/ }
		else
		{
			// вывод данных введённых слов
			//struct Sentence* sentence = readSentence();
			//for (size_t i = 0; i < sentence->len; i++)
			//{
			//	wprintf(L"word is [%ls] | punct is [%lc] | len is [%ld]\n", sentence->words_array[i]->word, sentence->words_array[i]->punct, sentence->words_array[i]->len);
			//}

			// вывод введённого пользователем текста
			struct Text* text = readText();
			remDupFromText(&text);
			printText(&text);

			switch(N)
			{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
			}
		}
	}

	return 0;
}
