#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

#define OPTION "5.13"
#define NAME "Artem"
#define SURNAME "Ivanov"

#define BLOCK_SIZE 10

struct Word
{
	char* word;
    	size_t len;
};

struct Sentence
{
	struct Word* sentence;
	size_t len;
};

struct Text
{
	struct Sentence* text;
	size_t len;
};

void printWelcomeMessage()
{
	printf("Course work for option %s, created by %s %s.\n", OPTION, NAME, SURNAME);
}

int safetyReallocMemToStr(char** buffer, int* count_of_allocated)
{
	char* old_buffer = *buffer;
	*buffer = (char*)realloc(*buffer, (*count_of_allocated + BLOCK_SIZE)*sizeof(char));
	*count_of_allocated += BLOCK_SIZE;

	// проверяем, была ли корректно перераспределена память
	if (*buffer == NULL)
	{
		*buffer = old_buffer;
		fprintf(stderr, "error: failed to re-allocate memory, the part of the sentence that has already been read will be returned\n");
		return -1;
	}
	return 0;
}

struct Sentence* readSentence()
{
	char c;
	char prev_c = ' ';
	char prev_prev_c = '.';
	int count_of_read = 0;
	int count_of_allocated = BLOCK_SIZE;
	int done = 0;
	
	// безопасно выделяем память под buffer
	char* buffer = NULL;
	safetyReallocMemToStr(&buffer, &count_of_allocated);

	while (!done)
	{	
		// считываем текущий символ
		c = getchar();

		// если память заполнена, перевыделяем её
		// если при выделении произошла ошибка, выводим сообщение об ошибке
		if ((count_of_read - 1) == count_of_allocated)
		{
			int result = safetyReallocMemToStr(&buffer, &count_of_allocated);

			if (result == -1) { break; }
		}


		// обрабатываем случай конца строки
		if (c == '.')
		{
			// если до точки стоит запятая, заменяем этот пробел на точку
			if (buffer[count_of_read-1] == ' ' || buffer[count_of_read-1] == ',')
			{
				if (count_of_read - 2 >= 0 && buffer[count_of_read-2] == ',')
				{
					buffer[count_of_read-2] = '.';
					buffer[count_of_read-1] = '\0';
				}
				else
				{
					buffer[count_of_read-1] = '.';
					buffer[count_of_read] = '\0';
				}
				break;
			}
			else
			{
				buffer[count_of_read] = '.';
				buffer[count_of_read+1] = '\0';
				break;
			}
		}

		// если символ пробельный - заменяем его на пробел
		if (c != ' ' && isspace(c)) { c = ' '; }

		// начало обработки запятых===========================================================================

		// превращаем "слово ,слово" -> "слово, слово"
		if (c == ',' && prev_c == ' ')
		{
			// проверяем, неотрицателен ли индекс count_of_read - 1
			// это нужно для исключения ошибки при проверке того, не стоит ли случайно запятая
			// в начале предложения
			if (count_of_read - 1 >= 0)
			{
				buffer[count_of_read-1] = ',';
				buffer[count_of_read] = ' ';
				c = ' ';
				prev_c = ',';
				continue;
			}
			else
			{
				continue;
			}
		}

		// превращаем "слово,слово" -> "слово, слово"
		if ((c != ' ' && c != ',' && c != '.') && prev_c == ',')
		{
			if (count_of_read + 1 <= count_of_allocated) { buffer[count_of_read++] = ' '; }
			else
			{
				int result = safetyReallocMemToStr(&buffer, &count_of_allocated);

				if (result == -1) { break; }

				buffer[count_of_read++] = ' ';
			}
		}

		// превращаем "слово, , слово" -> "слово, слово" и "слово,, " -> "слово, слово"
		if ((c == ',' && prev_c == ' ' && prev_prev_c == ',') || (c == ',' && prev_c == ',')) { continue; }

		// конец обработки запятых============================================================================

		// проверяем, стоят ли до первого слова в предложении пробелы или несколько пробелов подряд
		// если текущий символ равен пробелу и предыдущий символ равен пробелу - пропускаем символ
		if (c == ' ' && prev_c == ' ')
		{
			prev_prev_c = prev_c;
			prev_c = ' ';
			continue;
		}
		else
		{
			buffer[count_of_read++] = c;
			prev_prev_c = prev_c;
			prev_c = c;
		}
	}
	
	struct Sentence *sentence_obj_ptr = (struct Sentence*)malloc(sizeof(struct Sentence));
	sentence_obj_ptr->sentence = buffer;

	return sentence_obj_ptr;
}

struct Text readText()
{
	struct Text text;
	struct Text *text_ptr = &text;

	struct Sentence *sentence_obj_ptr = (struct Sentence*)malloc(sizeof(struct Sentence));
	while ((sentence_obj_ptr = readSentence())  != NULL)
	{
		text_ptr->sentence = sentence_obj_ptr;
		text_ptr = text_ptr->next_sentence; 
	}
	return text;
}

struct Text preProcessing()
{
	
};

void printManual()
{
	printf("╔───╦───────────────────────────────────────────╢ MANUAL ╟─────────────────────────────────────────────────────╗\n");
	printf("| 1 | Сделть сдвиг слов в предложении на положительное целое число N.                                          |\n");      	
	printf("|   | Например, предложение “abc b#c ИЙ два” при N = 2 должно принять вид “ИЙ два abc b#c”.                    |\n");
	printf("╠───╬──────────────────────────────────────────────────────────────────────────────────────────────────────────╣\n");
	printf("| 2 | Вывести все уникальные кириллические и латинские символы в тексте.                                       |\n"); 
	printf("╠───╬──────────────────────────────────────────────────────────────────────────────────────────────────────────╣\n");
	printf("| 3 | Подсчитать и вывести количество слов (плюс вывести слова в скобках) длина которых равна 1, 2, 3, и.т.д.. |\n");
	printf("╠───╬──────────────────────────────────────────────────────────────────────────────────────────────────────────╣\n");
	printf("| 4 | Удалить все слова которые заканчиваются на заглавный символ.                                             |\n");
	printf("╚───╩──────────────────────────────────────────────────────────────────────────────────────────────────────────╝\n");
}

int main()
{
	setlocale(LC_ALL, "");
	// вывод сообщения с информацией о варианте и ФИО студента
	printWelcomeMessage();

	// чтения номера действия (доработать)
	int N;
	scanf("%d", &N);

	if (N > 5 || N < 0)
	{
		fprintf(stderr, "error: wrong option\n");
	}
	else
	{
		if (N == 5) { printManual();}
		else
		{
			// output text
			//struct Text *text_ptr = (struct Text*)malloc(sizeof(struct Text));
			//text_ptr->sentence = readSentence();
			//for (; text_ptr->sentence != NULL; (text_ptr->next_sentence)->sentence = readSentence())
			//{}

			// output sentences
			struct Sentence *sentence = readSentence();
			
			printf("%s\n", sentence->sentence);

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
