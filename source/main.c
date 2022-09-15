
/**
 * @file main.c
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
#include <stdio.h>

#define SAMPLE(str) \
	{ \
		char* hashed = hash(str, sizeof(str) - 1); \
		fprintf(stdout, "value: %s, hash: %s\n", str, hashed); \
		free(hashed); \
	}

int main(
	int argc,
	const char** argv)
{
	assert(argc >= 2);
	const char* arg0 = argv[0];
	(void)arg0;

	for (const char** iterator = argv + 1; *iterator != NULL; ++iterator)
	{
		SAMPLE(*iterator);
	}

	/*
	SAMPLE("testas");
	SAMPLE("kazkas");
	SAMPLE("tests");
	SAMPLE("laba diena mokytojau uzzzkniso mane sita uzduotis nes niekas neveikia!");
	*/

	return 0;
}
