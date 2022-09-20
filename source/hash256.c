
/**
 * @file hash256.c
 *
 * @copyright This file is a part of the project hivelang and is distributed under MIT license that
 * should have been included with the project. If not, see https://choosealicense.com/licenses/mit/
 *
 * @author jorisb
 *
 * @date 2022-09-15
 */

#include <hash256.h>

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define INVALID_HASH256 ((struct Hash256) {.blocks = {0}, .stringified = {0}, .valid = 0})

#define PRIMARY1 ((const unsigned int)31)
#define PRIMARY2 ((const signed long long)2747636419u)
#define PRIMARY3 ((const signed long long)2654435769u)

static inline void setBlock(
	const signed int index,
	const signed int state,
	const unsigned int previous,
	struct Hash256* const hash)
{
	assert(hash != NULL);
	hash->blocks[index] = (state >> index) ^ previous;
	hash->blocks[index] ^= previous;
	hash->blocks[index] ^= PRIMARY2;
	hash->blocks[index] *= PRIMARY3;
	hash->blocks[index] ^= hash->blocks[index] >> 16;
	hash->blocks[index] *= PRIMARY3;
	hash->blocks[index] ^= hash->blocks[index] >> 16;
	hash->blocks[index] *= PRIMARY3;
}

struct Hash256 hash256(
	const char* input,
	const signed long long length)
{
	// Input validation and error handling
	if (input == NULL)
	{
		return INVALID_HASH256;
	}

	if (length <= 0)
	{
		return INVALID_HASH256;
	}

	// Setting up hash blocks
	struct Hash256 hash = INVALID_HASH256;
	unsigned int state = 0;

	for (signed int i = 0; i < length; ++i)
	{
		const unsigned int value = *(unsigned int*)(input + i);
		state = PRIMARY1 * state + value;
	}

	for (signed int i = 0; i < HASH256_BLOCKS_COUNT; ++i)
	{
		setBlock(i, state, i == 0 ? 0 : hash.blocks[i - 1], &hash);
	}

	// Setting up stringified hash
	for (signed int i = 0; i < HASH256_BLOCKS_COUNT; ++i)
	{
		if (snprintf(hash.stringified + (i * HASH256_BLOCKS_COUNT), HASH256_BLOCKS_COUNT + 1, "%08x", hash.blocks[i]) <= 0)
		{
			return INVALID_HASH256;
		}
	}

	hash.stringified[HASH256_STRING_LENGTH] = 0;
	hash.valid = 1;
	return hash;
}
