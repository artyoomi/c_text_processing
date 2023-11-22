#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <stdint.h>

#define OPTION L"5.13"
#define NAME L"Artem"
#define SURNAME L"Ivanov"

#define BLOCK_SIZE 5

struct Word
{
	wchar_t* word;
	wchar_t punct;
    size_t len;
};

struct Sentence
{
	struct Word* words_array;
	uint8_t is_last;
	size_t len;
};

struct Text
{
	struct Sentence* sentences_array;
	size_t len;
};

void printWelcomeMessage()
{
	wprintf(L"Course work for option %ls, created by %ls %ls.\n", OPTION, NAME, SURNAME);
}

void safetyReallocMemToWStr(wchar_t** buffer, uint32_t* count_of_allocated)
{
	// сохраняем область памяти, на которую указывает buffer изначально
	wchar_t* old_buffer = *buffer;
	// пробуем выделить память
	*buffer = (wchar_t*)realloc(*buffer, (*count_of_allocated + BLOCK_SIZE)*sizeof(wchar_t));

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
		*count_of_allocated += BLOCK_SIZE;
	}
}

void safetyReallocMemToWordArr(struct Word** arr, uint32_t* count_of_allocated)
{
	// сохраняем область памяти, на которую указывает buffer изначально
	struct Word* old_arr = *arr;
	// пробуем выделить память
	*arr = (struct Word*)realloc(*arr, (*count_of_allocated + BLOCK_SIZE)*sizeof(struct Word));

	// если указатель на buffer == NULL, значит произошла ошибка
	if (*arr == NULL)
	{
		// если память изначально указывала на NULL, это значит что мы её выделяли впервые
		// выводим соответствующее сообщение об ошибке
		if (old_arr == NULL)
		{
			fwprintf(stderr, L"error: failed to allocate memory\n");
			exit(0);
		}
		// иначе была ошибка при перевыделении
		else
		{
			*arr = old_arr;
			fwprintf(stderr, L"error: failed to re-allocate memory, the part of array that has already been read will be returned\n");
			exit(0);
		}
	}
	else
	{
		*count_of_allocated += BLOCK_SIZE;
	}
}

void safetyReallocMemToSentArr(struct Sentence** arr, uint32_t* count_of_allocated)
{
	// сохраняем область памяти, на которую указывает buffer изначально
	struct Sentence* old_arr = *arr;
	// пробуем выделить память
	*arr = (struct Sentence*)realloc(*arr, (*count_of_allocated + BLOCK_SIZE)*sizeof(struct Sentence));

	// если указатель на buffer == NULL, значит произошла ошибка
	if (*arr == NULL)
	{
		// если память изначально указывала на NULL, это значит что мы её выделяли впервые
		// выводим соответствующее сообщение об ошибке
		if (old_arr == NULL)
		{
			fwprintf(stderr, L"error: failed to allocate memory\n");
			exit(0);
		}
		// иначе была ошибка при перевыделении
		else
		{
			*arr = old_arr;
			fwprintf(stderr, L"error: failed to re-allocate memory, the part of array that has already been read will be returned\n");
			exit(0);
		}
	}
	else
	{
		*count_of_allocated += BLOCK_SIZE;
	}
}

struct Word* readWord()
{
	// выделяем память под структуру Word
	struct Word* word_obj = (struct Word*)malloc(sizeof(struct Word));

	// переменные для хранения количества считанных элементов и количества выделенной памяти соответственно
	uint32_t count_of_read = 0, count_of_allocated = 0;

	// переменная для хранения слова
	wchar_t* buffer = NULL;

	// если выделить память не удалось, выводим ошибку и завершаем программу
	safetyReallocMemToWStr(&buffer, &count_of_allocated);

	// переменная для хранения текущего символа и знака препинания (если  его нет, то знак препинания - \0)
	wchar_t c, prev_c = L'\0', punct = L'\0';

	// индикатор начала слова: 0 - слово ещё не началось, 1 - началось
	uint16_t word_begin = 0;

	// считываем, пока цикл не завершится с помощью break
	while (1)
	{
		c = getwchar();

		// проверяем условие конца считывания текста
		if (c == L'\n' && prev_c == L'\n')
		{
			word_obj->punct = L'\n';
			break;
		}

		// если выделенная память уже заполнена - перевыделяем
		if (count_of_read == count_of_allocated) { safetyReallocMemToWStr(&buffer, &count_of_allocated); }

		// если слово уже началось
		if (word_begin)
		{
			// провряем, что символ не является пробельным, запятой или точкой
			if (c != L',' && c != L'.' && !iswspace(c))
			{
				buffer[count_of_read] = c;
				count_of_read++;
			}
			
			// если символ равен запятой, точке или символ пробельный
			// то слово закончилось
			else if (c == L',' || c == L'.' || iswspace(c))
			{
				if (c == L'.' || c == L',')
				{
					word_obj->punct = c;
				}
				else
				{
					word_obj->punct = punct;
				}

				// после завершаем считывание, ведь слово уже закончилось
				break;
			}
		}

		// если слово ещё не началось и текущий символ не равен пробельному символу или запятой
		// то это значит что слово началось и надо записать символ в слово
		else if (!word_begin && c != L',' && c != L'.' && !iswspace(c))
		{
			buffer[count_of_read] = c;
			count_of_read++;
			word_begin = 1;
		}

		prev_c = c;
	}

	// если не хватает памяти чтобы записать в конец слова \0 - перевыделяем
	if (count_of_read >= count_of_allocated)
	{
		safetyReallocMemToWStr(&buffer, &count_of_allocated);
	}
	buffer[count_of_read] = L'\0';

	// если был считан хотя бы один символ - записываем слово и его длину в поля структуры
	if (count_of_read != 0)
	{
		word_obj->word = buffer;
		word_obj->len = count_of_read;
	}
	// иначе не было считано ни одного символа, т.е. указатель на первый символ слова это NULL
	else
	{
		word_obj->word = NULL;
		word_obj->len = 0;
	}

	return word_obj;
}

struct Sentence* readSentence()
{
	struct Sentence* sentence_obj = (struct Sentence*)malloc(sizeof(struct Sentence));
	sentence_obj->is_last = 0;

	uint32_t count_of_read = 0, count_of_allocated = 0;

	struct Word* wordsArr = NULL;
	safetyReallocMemToWordArr(&wordsArr, &count_of_allocated);

	struct Word* word_obj = (struct Word*)malloc(sizeof(struct Word));
	
	// чтобы избежать ошибки
	word_obj->punct = L'\0';

	while ((word_obj->punct) != L'.')
	{
		word_obj = readWord();
		if (count_of_read >= count_of_allocated) { safetyReallocMemToWordArr(&wordsArr, &count_of_allocated); }
		if (word_obj->punct == L'\n')
		{
			sentence_obj->is_last = 1;
			break;
		}
		wordsArr[count_of_read] = *word_obj;
		count_of_read++;

		// просто для теста, удалить до защиты!!!
		//wprintf(L"[%d] | seq is [%ls] | len is [%d] | punct is [%lc]\n", count_of_read, word_obj->word, word_obj->len, word_obj->punct);
	}
	sentence_obj->words_array = wordsArr;
	sentence_obj->len = count_of_read;
	//wprintf(L"sentence is_last is [%d]\n", sentence_obj->is_last);
	return sentence_obj;
}

struct Text* readText()
{
	struct Text* text_obj = (struct Text*)malloc(sizeof(struct Text));

	uint32_t count_of_read = 0, count_of_allocated = 0;

	struct Sentence* sentsArr = NULL;
	safetyReallocMemToSentArr(&sentsArr, &count_of_allocated);

	struct Sentence* sentence_obj = (struct Sentence*)malloc(sizeof(struct Sentence));

	while ((sentence_obj->is_last) != 1)
	{
		if (count_of_read  >= count_of_allocated) { safetyReallocMemToSentArr(&sentsArr, &count_of_allocated); }

		sentence_obj = readSentence();
		sentsArr[count_of_read] = *sentence_obj;
		count_of_read++;
	}
	text_obj->sentences_array = sentsArr;
	text_obj->len = count_of_read;

	return text_obj;
}

void printText(struct Text** text)
{
	for (size_t i = 0; i < (*text)->len; i++)
	{
		struct Sentence sent = ((*text)->sentences_array)[i];

		for (size_t j = 0; j < (sent.len); j++)
		{
			struct Word word_obj = sent.words_array[j];
			wprintf(L"%ls%lc ", word_obj.word, word_obj.punct);	
		}
		wprintf(L"\n");
	}
}

struct Text preProcessing()
{
	
};

void printManual()
{
	wprintf(L"╔───╦───────────────────────────────────────────╢ MANUAL ╟─────────────────────────────────────────────────────╗\n");
	wprintf(L"| 1 | Сделть сдвиг слов в предложении на положительное целое число N.                                          |\n");      	
	wprintf(L"|   | Например, предложение “abc b#c ИЙ два” при N = 2 должно принять вид “ИЙ два abc b#c”.                    |\n");
	wprintf(L"╠───╬──────────────────────────────────────────────────────────────────────────────────────────────────────────╣\n");
	wprintf(L"| 2 | Вывести все уникальные кириллические и латинские символы в тексте.                                       |\n"); 
	wprintf(L"╠───╬──────────────────────────────────────────────────────────────────────────────────────────────────────────╣\n");
	wprintf(L"| 3 | Подсчитать и вывести количество слов (плюс вывести слова в скобках) длина которых равна 1, 2, 3, и.т.д.. |\n");
	wprintf(L"╠───╬──────────────────────────────────────────────────────────────────────────────────────────────────────────╣\n");
	wprintf(L"| 4 | Удалить все слова которые заканчиваются на заглавный символ.                                             |\n");
	wprintf(L"╚───╩──────────────────────────────────────────────────────────────────────────────────────────────────────────╝\n");
}

int main()
{
	setlocale(LC_ALL, "");
	// вывод сообщения с информацией о варианте и ФИО студента
	printWelcomeMessage();

	// чтениe номера действия (доработать)
	int N;
	wscanf(L"%d", &N);

	if (N > 5 || N < 0)
	{
		fwprintf(stderr, L"error: wrong option\n");
	}
	else
	{
		if (N == 5) { printManual();}
		else
		{
			// вывод данных введённых слов
			//struct Sentence* wordsArr = NULL;
			//wordsArr = readSentence();

			// вывод введённого пользователем текста
			struct Text* text = (struct Text*)malloc(sizeof(struct Text));
			text = readText();
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
