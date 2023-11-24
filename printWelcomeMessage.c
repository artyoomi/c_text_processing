#include <wchar.h>

#include "./include/printWelcomeMessage.h"

#define OPTION L"5.13"
#define NAME L"Artem"
#define SURNAME L"Ivanov"

void printWelcomeMessage()
{
	wprintf(L"Course work for option %ls, created by %ls %ls.\n", OPTION, NAME, SURNAME);
}
