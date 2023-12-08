#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef SAFETY_REALLOC_MEM_TO_WSTR_H
	#define SAFETY_REALLOC_MEM_TO_WSTR_H
	#include "../../include/safety_realloc_functions/safetyReallocMemToWStr.h"
#endif

#ifndef MACRO_H
	#define MACRO_H
	#include "../../include/macro.h"
#endif

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
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		*count_of_allocated_chars += BLOCK_SIZE;
	}
}