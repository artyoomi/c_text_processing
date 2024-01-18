#include "./remDupFromText.h"

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
