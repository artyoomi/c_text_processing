#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 5

#define OPTION L"5.13"
#define NAME L"Artem"
#define SURNAME L"Ivanov"

// вывод приветственного сообщения
void printWelcomeMessage()
{
	wprintf(L"Course work for option %ls, created by %ls %ls.\n", OPTION, NAME, SURNAME);
}

// структуры
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

// функции выделения и перевыделения памяти
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
			fwprintf(stderr, L"Error: failed to allocate memory\n");
			exit(EXIT_FAILURE);
		}
		// иначе была ошибка при перевыделении
		else
		{
			fwprintf(stderr, L"Error: failed to re-allocate memory\n");
			free(old_buffer);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		*count_of_allocated_chars += BLOCK_SIZE;
	}
}

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
			free(old_buffer);
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
				for (uint32_t j = 0; j < i + 1; j++)
				{
					free((*buffer)[j]);
				}
				exit(EXIT_FAILURE);
			}
		}
		*count_of_allocated_words += BLOCK_SIZE;
	}
}

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
			free(old_buffer);
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
				for (uint32_t j = 0; j < i + 1; j++)
				{
					free((*buffer)[j]);
				}
				exit(EXIT_FAILURE);
			}
		}
		*count_of_allocated_sentences += BLOCK_SIZE;
	}
}

// функции считывания текста
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

struct Text* readText()
{
	// объявление результирующей структуры Text и иницализиация её значений
	struct Text* text = (struct Text*)malloc(sizeof(struct Text));
	text->sentences_array = NULL;
	text->len = 0;

	struct Sentence* curr_sentence;                 // хранит считанное предложение

	uint32_t count_of_read_sentences = 0;           // хранит количество считанных предложений
	uint32_t count_of_allocated_sentences = 0;      // хранит количество предложений, под которые выделеан память

	while (1)
	{
		// проверяем, что всё ещё хватает памяти для сохранения предложений
		if (count_of_read_sentences >= count_of_allocated_sentences) {
			safetyReallocMemToSentenceStructsArray(&(text->sentences_array),
						                           &count_of_allocated_sentences);
		}

		curr_sentence = readSentence();

		// обрабатываем случай последнего предложения
		if (curr_sentence->is_last)
		{
			// если функция чтения предложения вернула пустой массив words_array, делаем break
			if (curr_sentence->words_array == NULL)
			{
				free(curr_sentence);
				if (count_of_read_sentences >= 1)
				{
					text->sentences_array[count_of_read_sentences - 1]->is_last = 1;
				}
				break;
			}
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

void remSentence(struct Text **text, const uint32_t index_of_sentence)
{
	// сохраняем адрес на структуру, которую необходимо удалить
	struct Sentence *sentence_to_del = (*text)->sentences_array[index_of_sentence];

    memmove(&(*text)->sentences_array[index_of_sentence],
	        &(*text)->sentences_array[index_of_sentence + 1],
	        ((*text)->len - index_of_sentence - 1) * sizeof(struct Sentence *));

    free(sentence_to_del);
    (*(*text)).len--;
}

void remDupFromText(struct Text** text)
{
	// выполням функцию только если в ней есть хотя бы два предложения, иначе это просто не имеет смысла
	//<REVIEW> if-while
	if ((*text)->len >= 2)
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
							if (!wcscasecmp(sentence1->words_array[k]->word,
							                sentence2->words_array[k]->word) &&
											sentence1->words_array[k]->punct == sentence2->words_array[k]->punct)
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
}

void printSentenceWithNumberN(struct Text **text, const uint32_t number_of_sentence)
{
	uint32_t index_of_sentence = number_of_sentence - 1;
	if (index_of_sentence >= 0 && index_of_sentence <= (*text)->len - 1)
	{
		struct Sentence* sentence = (*text)->sentences_array[index_of_sentence];

		for (uint32_t i = 0; i < sentence->len; i++)
		{
			if (sentence->words_array[i]->punct != '\0') { wprintf(L"%ls%lc ", sentence->words_array[i]->word, sentence->words_array[i]->punct); }
			else { wprintf(L"%ls ", sentence->words_array[i]->word); }
		}
		wprintf(L"\n");
	}
	else 
	{
		fwprintf(stderr, L"Error: the sentence with the number [%u] does not exist\n", index_of_sentence);
		exit(EXIT_FAILURE);
	}
}

// подзадача 0 = выполнено
void printText(struct Text **text)
{
	struct Sentence** sentences_array = (*text)->sentences_array;

	if ((*text)->len == 0)
	{
		wprintf(L"output: text is empty\n");
	}
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
		wprintf(L"\n");
	}
}

// подзадача 1 = выполнено
void shiftingWordsInSentence(struct Text **text, const uint32_t number_of_sentence, const uint32_t number_of_shifts)
{
	struct Sentence *sentence;
	// находим индекс предложения
	uint32_t index_of_sentence = number_of_sentence - 1;

	// проверяем, что предложение с полученным номером существует в тексте
	if (index_of_sentence >= 0 && index_of_sentence <= (*text)->len - 1) { sentence = (*text)->sentences_array[index_of_sentence]; }
	else 
	{
		fwprintf(stderr, L"Error: the sentence with the number [%u] does not exist\n", number_of_sentence);
		exit(EXIT_FAILURE);
	}

	// если структура предложения не ссылкается ни на какой массив слов, то оно пусто
	if (sentence->words_array == NULL)
	{
		fwprintf(stderr, L"Error: the sentence is empty\n");
		exit(EXIT_FAILURE);
	}

	// если подано количество сдвигов, равное 0, то обрабатывать далее смысла нет
	if (number_of_shifts == 0) { exit(EXIT_SUCCESS); }
	else
	{
		// убираем точку у последнего слова, чтобы в конце поставить её после нового последнего слова
		sentence->words_array[sentence->len - 1]->punct = '\0';

		struct Sentence *temp_sentence = (struct Sentence*)malloc(sizeof(struct Sentence));
		temp_sentence->words_array = (struct Word**)malloc(sentence->len * sizeof(struct Word*));

		//<REVIEW> comment
		//<REVIEW> while -> for
		//temp_sentence->words_array = sentence->words_array;

		//<REVIEW> comments under
		//uint32_t ind = 0;
		//while(ind != sentence->len)
		for (uint32_t ind = 0; ind < sentence->len; ind++)
		{
			temp_sentence->words_array[(ind + number_of_shifts)%(sentence->len)] = sentence->words_array[ind];
			//ind++;
		}
		sentence->words_array = temp_sentence->words_array;

		// вставляем точку после последнего предложений
		sentence->words_array[sentence->len - 1]->punct = '.';
		free(temp_sentence);
	}
}

// подзадача 2
/*void printUniqSymbols(struct Text **text)
{
	uint32_t count_of_read_chars = 0, count_of_allocated_chars = 0;
	wchar_t *uniq_symbols_array = NULL;
	safetyReallocMemToWStr(&uniq_symbols_array, &count_of_allocated_chars);

	// перебираем массив предложений
	for (uint32_t i = 0; i < (*text)->len; i++)
	{
		// перебор слов в предложении с индексом i
		for (uint32_t j = 0; j < (*text)->sentences_array[i]->len)
		{
			// перебор символов в массиве символов
			for (uint32_t k = 0; k < (*text)->sentences_array[i]->words_array[j]->len)
			{
				// проверяем, что символ не в массиве уникальных символов
				for (uint32_t l = 0; l < count_of_read_chars; l++)
				{
					if ((*text)->sentences_array[i]->words_array[j]->word[k] == uniq_symbols_array[l])
					{
						is_uniq = 0;
						break;
					}
				}
				
			}
		}
	}
}*/

// подзадача 3
void printCountOfSpecificWords(struct Text **text)
{
	for (uint32_t i = 0; i < (*text)->len; i++)
	{
		
	}
}

// подзадача 4 = выполнено
void remWord(struct Text **text, const uint32_t index_of_sentence, const uint32_t index_of_word_in_sentence)
{
	struct Word *word_to_del = (*text)->sentences_array[index_of_sentence]->words_array[index_of_word_in_sentence];
	memmove(&(*text)->sentences_array[index_of_sentence]->words_array[index_of_word_in_sentence],
	        &(*text)->sentences_array[index_of_sentence]->words_array[index_of_word_in_sentence + 1],
			((*text)->sentences_array[index_of_sentence]->len - index_of_word_in_sentence - 1) * sizeof(struct Word*));
	free(word_to_del->word);
	free(word_to_del);
	(*(*text)->sentences_array[index_of_sentence]).len--;

}

void remWordsWithLastUppercaseLetter(struct Text **text)
{
	//<REVIEW> if-while
	uint32_t i = 0, j = 0;

	// перебор по предложениям текста
	while(i < (*text)->len)
	{
		// перебор по словам в i-м предложении
		while(j < (*text)->sentences_array[i]->len)
		{
			if ((*text)->len != 0)
			{
				// проверяем, что последний символ в верхнем регистре
				if ((*text)->sentences_array[i]->words_array[j]->len >= 1 &&
					iswupper(((*text)->sentences_array[i]->words_array[j]->word)[(*text)->sentences_array[i]->words_array[j]->len - 1]))
				{
					// если слово последнее в предложении и длина предложения не равна 1,
					// то ставим после прошлого слова точку
					if (j == (*text)->sentences_array[i]->len - 1 && (*text)->sentences_array[i]->len != 1)
					{
						(*text)->sentences_array[i]->words_array[j - 1]->punct = L'.';
					}

					// проверяем, что слово не является последним в предложении
					if ((*text)->sentences_array[i]->words_array[j]->len - 1 != j)
					{
						remWord(text, i, j);
						(*(*text)->sentences_array[i]).len--;
						continue;
					}
					else
					{
						free((*text)->sentences_array[i]->words_array[j]->word);
						free((*text)->sentences_array[i]->words_array[j]);
						(*(*text)->sentences_array[i]).len--;
						break;
					}
				}
				// проверяем случай, когда после удаления слова предложение стало пустым
				if ((*text)->sentences_array[i]->len == 0)
				{
					remSentence(text, i);
				}
				else { j++; }
			}
		}
		if ((*text)->sentences_array[i]->len == 0)
		{
			remSentence(text, i);
		}
		i++;
		j = 0;
	}
}

// подзадача 5 = выполнено
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

//<REVIEW>
void freeText(struct Text **text)
{
	// проходимся по предложениям в тексте
	for (uint32_t i = 0; i < (*text)->len; i++)
	{
		// проходимя по словам в каждом предложении
		for (uint32_t j = 0; j < (*text)->sentences_array[i]->len; j++)
		{
			// очищаем выделенную под слово память
			free((*text)->sentences_array[i]->words_array[j]->word);
			// очищаем выделенную под структуру Word память
			free((*text)->sentences_array[i]->words_array[j]);
		}
		// очищаем выделенную под массив структур Word память
		free((*text)->sentences_array[i]->words_array);
		// очищаем выделенную под структуру Sentence память
		free((*text)->sentences_array[i]);
	}
	free((*text)->sentences_array);	
	free(*text);
}

int main()
{
	setlocale(LC_ALL, "");
	// вывод сообщения с информацией о варианте и ФИО студента
	printWelcomeMessage();

	// чтениe номера действия (доработать)
	int command;
	wprintf(L"\nEnter a number (a number from 0 to 5): ");
	wscanf(L"%d", &command);

	if (command > 5 || command < 0)
	{
		fwprintf(stderr, L"Error: wrong option\n");
	}
	else
	{
		if (command == 5) { printManual(); }
		else
		{
			wprintf(L"\nEnter the text below:\n");

			struct Text* text = readText();
			remDupFromText(&text);

			switch(command)
			{
				case 0:
					wprintf(L"Text without repeating sentences:\n");
					printText(&text);
					break;
				case 1:
					uint32_t number_of_shifts = 0;
					uint32_t number_of_sentence = 0; 

					wprintf(L"Enter the number of the sentence in which you want to shift the words: ");
					wscanf(L"%u", &number_of_sentence);
					
					wprintf(L"\nEnter the number by which you want to shift the words in the sentence: ");
					wscanf(L"%u", &number_of_shifts);

					shiftingWordsInSentence(&text, number_of_sentence, number_of_shifts);

					wprintf(L"\nSentence with number [%u] words shifted by [%u]: ", number_of_sentence, number_of_shifts);

					printSentenceWithNumberN(&text, number_of_sentence);

					break;

				case 2:
					//printUniqSymbols(&text);
					break;

				case 3:
					uint32_t count_of_allocated_to_sentences = 0;
					// определяем двумерный массив, где каждый элемент с индексом i, хранит
					// слова длины i+1
					struct Sentence **words = NULL;
					safetyReallocMemToSentenceStructsArray(&words, &count_of_allocated_to_sentences);

					// делаем перебор по предложениям
					for (uint32_t i = 0; i < text->len; i++)
					{
						// делаем перебор по словам в предложении с индексом i
						for (uint32_t j = 0; j < text->sentences_array[i]->len; j++)
						{
							if (text->sentences_array[i]->words_array[j]->len - 1 >= 0)
							{
								//<REVIEW>
								//words[text->sentences_array[i]->words_array[j]->len - 1]
							}
						}
					}

					break;

				case 4:
					remWordsWithLastUppercaseLetter(&text);
					wprintf(L"Text without words with the last letter in uppercase:\n");
					printText(&text);
					break;
			}
			freeText(&text);
		}
	}

	return 0;
}

// для второй задачи:
// создать массив для символов, добавлять если нету 

// для третьей задачи:
// создать массив вордов и отсортировать по количеству символов