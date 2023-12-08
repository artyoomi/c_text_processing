#include <wchar.h>
#include <stdint.h>

struct Word
{
	wchar_t* word;
	wchar_t punct;
    uint32_t len;
};

struct Sentence
{
	struct Word** words_array;
	uint16_t is_last;
	uint32_t len;
};

struct Text
{
	struct Sentence** sentences_array;
	uint32_t len;
};