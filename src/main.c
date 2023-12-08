#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>

#include "./include/structs.h"
#include "./include/macro.h"
#include "./include/textStructToString.h"

#include "./include/print_functions/printWelcomeMessage.h"
#include "./include/print_functions/printManual.h"
#include "./include/print_functions/printText.h"
#include "./include/print_functions/printUniqSymbolsInText.h"
#include "./include/print_functions/printNumOfWordsOfACertainLen.h"

#include "./include/safety_realloc_functions/safetyReallocMemToWStr.h"
#include "./include/safety_realloc_functions/safetyReallocMemToWordStructsArray.h"
#include "./include/safety_realloc_functions/safetyReallocMemToSentenceStructsArray.h"

#include "./include/read_functions/readSentence.h"
#include "./include/read_functions/readText.h"

#include "./include/remove_functions/remSentence.h"
#include "./include/remove_functions/remDupFromText.h"
#include "./include/remove_functions/remWord.h"
#include "./include/remove_functions/remWordsWithLastUppercaseLetter.h"

#include "./include/shifting_functions/shiftingWordsInText.h"

#include "./include/freeText.h"



int main()
{
	setlocale(LC_ALL, "");
	
	// печатаем приветственное сообщение
	printWelcomeMessage();

	// считываем номер команды
	uint8_t command;
	//wprintf(L"\nEnter a number (a number from 0 to 5): ");
	wscanf(L"%u", &command);

	// проверяем команду на корректность
	if (command > 5 || command < 0)
	{
		fwprintf(stderr, L"\033[31mError:\033[0m wrong option\n");
	}
	else
	{
		if (command == 5) { printManual(); }
		else
		{
			//wprintf(L"\nEnter the text below:\n");

			// ввод и первичная обработка текста
			struct Text* text = readText();
			remDupFromText(&text);
			
			uint32_t number_of_shifts = 0;

			// выолпяем подзадачи
			switch(command)
			{
				case 0:
					//wprintf(L"Text without repeating sentences:\n");
					printText(&text);

					break;

				case 1:
					//wprintf(L"\nEnter the number by which you want to shift the words in text: ");
					wscanf(L"%u", &number_of_shifts);

					shiftingWordsInText(&text, number_of_shifts);

					//wprintf(L"\nText with sentences shifted by [%u]:\n", number_of_shifts);
					printText(&text);

					break;

				case 2:
					printUniqSymbolsInText(&text);

					break;

				case 3:
					printNumOfWordsOfACertainLen(&text);

					break;

				case 4:
					remWordsWithLastUppercaseLetter(&text);

					wprintf(L"Text without words with the last letter in uppercase:\n");
					printText(&text);

					break;
			}

			// освобождаем выделенную под текст память
			freeText(&text);
		}
	}

	return 0;
}
