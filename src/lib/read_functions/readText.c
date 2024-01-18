#include "./readText.h"

struct Text* readText()
{
	// объявление результирующей структуры Text и иницализиация её значений
	struct Text *text = (struct Text *)malloc(sizeof(struct Text));
	text->sentences_array = NULL;
	text->len = 0;

	struct Sentence* curr_sentence = NULL;          // хранит считанное предложение

	uint32_t count_of_read_sentences = 0;           // хранит количество считанных предложений
	uint32_t count_of_allocated_sentences = 0;      // хранит количество предложений, под которые выделеан память

	while (1)
	{
		// проверяем, что всё ещё хватает памяти для сохранения предложений
		if (count_of_read_sentences >= count_of_allocated_sentences) {
			safetyReallocMemToSentenceStructsArray(&(text->sentences_array),
						                           &count_of_allocated_sentences);
		}

		curr_sentence = readSentence();

		// обрабатываем случай последнего предложения
		if (curr_sentence->is_last)
		{
			// если функция чтения предложения вернула пустой массив words_array, делаем break
			if (curr_sentence->words_array == NULL)
			{
				freeSentence(&curr_sentence);
				if (count_of_read_sentences >= 1)
				{
					text->sentences_array[count_of_read_sentences - 1]->is_last = 1;
				}
				break;
			}
			else
			{
				freeSentence(&(text->sentences_array[count_of_read_sentences]));
				text->sentences_array[count_of_read_sentences] = curr_sentence;
				count_of_read_sentences++;
				break;
			}
		}
		freeSentence(&(text->sentences_array[count_of_read_sentences]));
		text->sentences_array[count_of_read_sentences] = curr_sentence;
		count_of_read_sentences++;
	}

	text->len = count_of_read_sentences;
	text->allocated_size = count_of_allocated_sentences;
	//wprintf(L"D: a - %d, s - %d\n", text->allocated_size, text->len);

	return text;
}