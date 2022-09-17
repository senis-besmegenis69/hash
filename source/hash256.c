
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

	// Hashing
	struct Hash256 hash = INVALID_HASH256;
	const unsigned int primary1 = 31;
	const signed long long primary2 = 2747636419u;
	const signed long long primary3 = 2654435769u;

	unsigned int state = 0;
	for (signed int i = 0; i < length; ++i)
		state = primary1 * state + *(unsigned int*)(input + i);

	hash.blocks[0] = state;
	hash.blocks[0] ^= primary2;
	hash.blocks[0] *= primary3;
	hash.blocks[0] ^= hash.blocks[0] >> 16;
	hash.blocks[0] *= primary3;
	hash.blocks[0] ^= hash.blocks[0] >> 16;
	hash.blocks[0] *= primary3;

	for (signed int i = 1; i < HASH256_BLOCKS_COUNT; ++i)
	{
		hash.blocks[i] = (state >> i) ^ hash.blocks[i - 1];
		hash.blocks[i] ^= hash.blocks[i - 1];
		hash.blocks[i] ^= primary2;
		hash.blocks[i] *= primary3;
		hash.blocks[i] ^= hash.blocks[i] >> 16;
		hash.blocks[i] *= primary3;
		hash.blocks[i] ^= hash.blocks[i] >> 16;
		hash.blocks[i] *= primary3;
	}

	for (signed int i = 0; i < HASH256_BLOCKS_COUNT; ++i)
	{
		if (snprintf(hash.stringified + (i * HASH256_BLOCKS_COUNT), HASH256_BLOCKS_COUNT + 1, "%x", hash.blocks[i]) <= 0)
		{
			return INVALID_HASH256;
		}
	}

	hash.stringified[HASH256_STRING_LENGTH] = 0;
	hash.valid = 1;
	return hash;
}
