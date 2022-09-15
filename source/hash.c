
/**
 * @file hash.c
 *
 * @copyright This file is a part of the project hivelang and is distributed under MIT license that
 * should have been included with the project. If not, see https://choosealicense.com/licenses/mit/
 *
 * @author jorisb
 *
 * @date 2022-09-15
 */

#include <hash.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define HASH_LENGTH 64

char* hash(
	const char* input,
	const signed long long length)
{
	assert(input != NULL);
	assert(length > 0);

	char* output = (char*)malloc((HASH_LENGTH + 1) * sizeof(char));
	assert(output != NULL);

	if (length > HASH_LENGTH)
	{
	}
	else if (length < HASH_LENGTH)
	{
	}
	else
	{
	}

	output[HASH_LENGTH] = 0;
	return output;
}
