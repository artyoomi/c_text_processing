#include <wchar.h>

#include "./include/printManual.h"

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