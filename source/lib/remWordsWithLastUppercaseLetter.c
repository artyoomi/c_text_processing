#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>

#ifndef STRUCTS_H
	#define STRUCTS_H
	#include "../include/structs.h"
#endif

#ifndef REM_WORD_H
	#define REM_WORD_H
	#include "../include/remWord.h"
#endif

#ifndef REM_WORDS_WITH_UPPERCASE_LETTER_H
	#define REM_WORDS_WITH_UPPERCASE_LETTER_H
	#include "../include/remWordsWithLastUppercaseLetter.h"
#endif

#ifndef REM_SENTENCE_H
	#define REM_SENTENCE_H
	#include "../include/remSentence.h"
#endif

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