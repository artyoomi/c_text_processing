#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <stdint.h>
#include <string.h>

#include "./include/structs.h"
#include "./include/printWelcomeMessage.h"
#include "./include/printManual.h"
#include "./include/safetyReallocMemToWStr.h"
#include "./include/safetyReallocMemToWordStructsArray.h"
#include "./include/safetyReallocMemToSentenceStructsArray.h"
#include "./include/readSentence.h"
#include "./include/readText.h"
#include "./include/remSentence.h"
#include "./include/remDupFromText.h"
#include "./include/printSentenceWithNumberN.h"
#include "./include/printText.h"
#include "./include/remWord.h"
#include "./include/remWordsWithLastUppercaseLetter.h"
#include "./include/freeText.h"
#include "./include/shiftingWordsInText.h"


#define BLOCK_SIZE 5


int main()
{
	setlocale(LC_ALL, "");
	printWelcomeMessage();

	// чтениe номера действия <REVIEW>
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
					uint32_t number_of_shifts;
					
					wprintf(L"\nEnter the number by which you want to shift the words in text: ");
					wscanf(L"%u", &number_of_shifts);

					shiftingWordsInText(&text, number_of_shifts);

					wprintf(L"\nText with sentences shifted by [%u]:\n", number_of_shifts);

					printText(&text);

					break;

				case 2:
					
					break;

				case 3:

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