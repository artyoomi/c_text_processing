#include <stdint.h>
#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>

#ifndef STRUCTS_H
	#define STRUCTS_H
	#include "../../include/structs.h"
#endif

#ifndef TEXT_STRUCT_TO_STRING_H
	#define TEXT_STRUCT_TO_STRING_H
	#include "../../include/textStructToString.h"
#endif

#ifndef SAFETY_REALLOC_MEM_TO_WSTR_H
	#define SAFETY_REALLOC_MEM_TO_WSTR_H
	#include "../../include/safety_realloc_functions/safetyReallocMemToWStr.h"
#endif

int32_t chars_cmp(const void *x, const void *y)
{
	wchar_t f = *((wchar_t *)x);
	wchar_t s = *((wchar_t *)y);

	if (f > s) { return -1; }
	else if (f == s) { return 0; }
	else { return 1; }
}

void printUniqSymbolsInText(struct Text **text)
{
	uint32_t count_of_read_chars = 0;
	uint32_t count_of_allocated_chars = 0;

	wchar_t *uniq_symbols_string  = NULL;
	safetyReallocMemToWStr(&uniq_symbols_string, &count_of_allocated_chars);

	wchar_t *text_string = textStructToString(text);
	
	uint32_t string_len = wcslen(text_string);

	// сортируем строку
	qsort(text_string, string_len, sizeof(wchar_t), chars_cmp);
	
	for (uint32_t i = 0; i < string_len - 1; i++)
	{
		if (iswalpha(text_string[i]))
		{
			if (i == 0 && text_string[i] != text_string[i + 1])
			{
				if (count_of_read_chars == count_of_allocated_chars)
				{
					safetyReallocMemToWStr(&uniq_symbols_string, &count_of_allocated_chars);
				}

				uniq_symbols_string[count_of_read_chars++] = text_string[i];
			}
			else if (i >= 1 && text_string[i - 1] != text_string[i] && text_string[i] != text_string[i + 1])
			{
				if (count_of_read_chars == count_of_allocated_chars)
				{
					safetyReallocMemToWStr(&uniq_symbols_string, &count_of_allocated_chars);
				}

				uniq_symbols_string[count_of_read_chars++] = text_string[i];
			}
		}
	}
	if (count_of_read_chars >= count_of_allocated_chars)
	{
		safetyReallocMemToWStr(&uniq_symbols_string, &count_of_allocated_chars);
	}
	uniq_symbols_string[count_of_read_chars] = L'\0';

	//wprintf(L"Unique Latin and Cyrillic characters:\n");

	if (count_of_read_chars == 0)
	{	
		wprintf(L"\033[33mWarning:\033[0m there are no unique Cyrillic or Latin characters in the text\n");
		count_of_allocated_chars = 0;
	}
	else
	{
		wprintf(L"%ls\n", uniq_symbols_string);
	}

	free(uniq_symbols_string);
	free(text_string);
}
