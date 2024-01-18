#include <stdio.h>
#include <stdint.h>
#include <wchar.h>
#include <locale.h>

#include "./lib/structs.h"
#include "./lib/print_functions/printWelcomeMessage.h"
#include "./lib/print_functions/printManual.h"
#include "./lib/print_functions/printText.h"
#include "./lib/print_functions/printUniqSymbolsInText.h"
#include "./lib/print_functions/printNumOfWordsOfACertainLen.h"
#include "./lib/read_functions/readText.h"
#include "./lib/remove_functions/remDupFromText.h"
#include "./lib/remove_functions/remWordsWithLastUppercaseLetter.h"
#include "./lib/shifting_functions/shiftingWordsInText.h"
#include "./lib/free_functions/freeText.h"

#include "./lib/def_task/addSmile.h"

int main()
{
	// changes
	setlocale(LC_ALL, "");
	
	// печатаем приветственное сообщение
	printWelcomeMessage();

	// считываем номер команды
	uint8_t command;
	//wprintf(L"\nEnter a number (a number from 0 to 5): ");
	uint32_t success = wscanf(L"%u", &command);

	// проверяем команду на корректность
	if (success == 0 && ((command > 5 || command < 0 || command != 9)))
	{
		fwprintf(stderr, L"\033[31mError:\033[0m wrong option\n");
	}
	else
	{
		if (command == 5) { printManual(); }
		else
		{
			//wprintf(L"\nEnter the text below:\n");

			struct Text* text;
			
			uint32_t number_of_shifts = 0;

			// выполняем подзадачи
			switch(command)
			{
				case 0:
					text = readText();
					remDupFromText(&text);

					//wprintf(L"Text without repeating sentences:\n");
					printText(&text);
					break;

				case 1:
					//wprintf(L"\nEnter the number by which you want to shift the words in text: ");
					wscanf(L"%u", &number_of_shifts);

					text = readText();
					remDupFromText(&text);

					shiftingWordsInText(&text, number_of_shifts);

					//wprintf(L"\nText with sentences shifted by [%u]:\n", number_of_shifts);
					printText(&text);
					break;

				case 2:
					text = readText();
					remDupFromText(&text);

					printUniqSymbolsInText(&text);
					break;

				case 3:
					text = readText();
					remDupFromText(&text);

					printNumOfWordsOfACertainLen(&text);
					break;

				case 4:
					text = readText();
					remDupFromText(&text);

					remWordsWithLastUppercaseLetter(&text);

					//wprintf(L"Text without words with the last letter in uppercase:\n");
					printText(&text);
					break;

				case 9:
					text = readText();
					remDupFromText(&text);

					addSmile(&text);
					printText(&text);

					break;
			}
			freeText(&text);
		}
	}

	return 0;
}
