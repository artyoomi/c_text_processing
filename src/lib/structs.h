#ifndef STRUCTS_H
#define STRUCTS_H

#include <wchar.h>
#include <stdint.h>

struct Word
{
	wchar_t* word;
	wchar_t punct;
    uint32_t len;
    uint32_t allocated_size;
};

struct Sentence
{
	struct Word** words_array;
	uint8_t is_last;
	uint32_t len;
	uint32_t allocated_size;
};

struct Text
{
	struct Sentence** sentences_array;
	uint32_t len;
	uint32_t allocated_size;
};

#endif