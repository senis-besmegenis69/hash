
/**
 * @file test_suite.c
 *
 * @copyright This file is a part of the project hivelang and is distributed under MIT license that
 * should have been included with the project. If not, see https://choosealicense.com/licenses/mit/
 *
 * @author jorisb
 *
 * @date 2022-09-15
 */

#include <hash256.h>

#include <inttypes.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

signed int equalHashes(struct Hash256* const a, struct Hash256* const b)
{
	return memcmp(a->blocks, b->blocks, sizeof(unsigned int[8])) == 0;
}

struct Word
{
	char buffer[128];
	signed long long length;
};

int main(
	void)
{
	// fprintf(stdout, "%s\n", hash256("n!ebeprisikiskiapusteliadama", 28).stringified);
	fprintf(stdout, "%s\n", hash256("Lietuva", 7).stringified);
	fprintf(stdout, "%s\n", hash256("lietuva", 7).stringified);
	return 0;

	FILE* stream = fopen("./30k.txt", "r");
	assert(stream != NULL);
	ssize_t read; char* line; size_t length = 0;

	#define wordsCap 1000000
	struct Word* words = malloc((wordsCap + 1) * sizeof(struct Word));
	assert(words != NULL);

	signed long long wordsCount = 0;
	while (wordsCount < wordsCap)
	{
		if (fgets(words[wordsCount].buffer, sizeof(words[wordsCount].buffer), stream) != NULL)
		{
			words[wordsCount].length = strlen(words[wordsCount].buffer);
			++wordsCount;
		}
		else
		{
			break;
		}
	}
	fclose(stream);

	fprintf(stdout, "Finished reading words (%lld)!\n", wordsCount);

	signed long long collided = 0;
	for (signed long long i = 0; i < wordsCount - 1; ++i)
	{
		struct Hash256 hashi = hash256(words[i].buffer, words[i].length);

		for (signed long long j = i; j < wordsCount; ++j)
		{
			if (i == j)
			{
				continue;
			}

			struct Hash256 hashj = hash256(words[j].buffer, words[j].length);

			if (equalHashes(&hashi, &hashj) == 1)
			{
				++collided;
				fprintf(stderr, "Collision between: %s and %s, with hashes: %s and %s\n", words[i].buffer, words[j].buffer, hashi.stringified, hashj.stringified);
			}
		}

		if (i % 1000 == 0)
		{
			fprintf(stdout, "Went over %lld words...\n", i);
		}
	}

	if (collided <= 0)
		fprintf(stderr, "No collisions detected!\n");
	else
		fprintf(stderr, "In total %lld collisions happened!\n", collided);

	free(words);
	return 0;
}