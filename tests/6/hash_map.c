
/**
 * @file hash_map.c
 *
 * @copyright This file is a part of the project hivelang and is distributed under MIT license that
 * should have been included with the project. If not, see https://choosealicense.com/licenses/mit/
 *
 * @author jorisb
 *
 * @date 2022-09-20
 */

#include "../include/hash256.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Word
{
	char buffer[1024];
};

struct Node
{
	struct Hash256 hash;
	struct Word word;
};

struct HashMap
{
	struct Node* nodes;
	signed long long capacity;
	signed long long count;
};

static inline struct HashMap HashMap_create(
	const signed long long capacity)
{
	assert(capacity >= 1);
	struct HashMap hashMap = {0};
	hashMap.nodes = (struct Node*)malloc(capacity * sizeof(struct Node));
	assert(hashMap.nodes != NULL);
	hashMap.capacity = capacity;
	hashMap.count = 0;
	return hashMap;
}

static inline void HashMap_grow(
	struct HashMap* const hashMap,
	const signed long long newCapacity)
{
	assert(hashMap != NULL);
	assert(newCapacity >= 1);

	struct Node* block = (struct Node*)malloc(newCapacity * sizeof(struct Node));
	memcpy(block, hashMap->nodes, hashMap->capacity * sizeof(struct Node));
	free(hashMap->nodes);

	hashMap->nodes = block;
	hashMap->capacity = newCapacity;
}

static inline const struct Node* HashMap_exists(
	struct HashMap* const hashMap,
	const struct Hash256* const hash)
{
	assert(hashMap != NULL);
	assert(hash != NULL);

	for (signed long long i = 0; i < hashMap->count; ++i)
	{
		if (strcmp(hashMap->nodes[i].hash.stringified, hash->stringified) == 0) return &hashMap->nodes[i];
	}

	return NULL;
}

static inline signed int HashMap_add(
	struct HashMap* const hashMap,
	const struct Node node)
{
	assert(hashMap != NULL);

	if (hashMap->count + 1 >= hashMap->capacity)
	{
		HashMap_grow(hashMap, (hashMap->capacity + 1) * 1.5);
	}

	const struct Node* existing = HashMap_exists(hashMap, &node.hash);

	if (existing != NULL)
	{
		// fprintf(stdout, "Collision happened between\n\tvalue: %s, hash: %s\n\tvalue: %s, hash: %s\n",
		// 	node.word.buffer, node.hash.stringified, existing->word.buffer, existing->hash.stringified);
		return 0;
	}
	else
	{
		hashMap->nodes[hashMap->count++] = node;
		return 1;
	}
}

static inline void HashMap_destroy(
	struct HashMap* const hashMap)
{
	assert(hashMap != NULL);
	assert(hashMap->nodes != NULL);
	free(hashMap->nodes);
	hashMap->capacity = 1;
	hashMap->count = 0;
}

int main(
	void)
{
	FILE* stream = fopen("./data.txt", "r");
	assert(stream != NULL);
	ssize_t read; char* line; size_t length = 0;
	struct HashMap hashMap = HashMap_create(200024);

	for (signed long long i = 0; (read = getline(&line, &length, stream)) != -1; ++i)
	{
		--read;
		struct Hash256 hash = hash256(line, read);
		struct Word word = { .buffer = {0} };
		memcpy(word.buffer, line, read);
		word.buffer[read] = 0;

		if (!HashMap_add(&hashMap, (struct Node) { .hash = hash, .word = word }))
		{
			fprintf(stdout, "Collision happened! Value: %s, hash: %s\n", word.buffer, hash.stringified);
		}

		if (i % 25000 == 0)
		{
			fprintf(stdout, "Already processed %lld lines...\n", i);
		}
	}

	fprintf(stdout, "Finished!\n");

	long double binaryPercentageAverage = 0;
	long double hexPercentageAverage = 0;

	for (signed long long i = 0; i < hashMap.count; ++i)
	{
		long double binaryPercentage = 0;
		long double hexPercentage = 0;

		for (signed long long j = 0; j < hashMap.count; ++j)
		{
			if (i == j)
			{
				continue;
			}

			double binP = 0;
			for (signed int k = 0; k < 8; ++k)
				if (hashMap.nodes[i].hash.blocks[k] == hashMap.nodes[j].hash.blocks[k])
					binP += 8;
			binP /= 8;
			binP *= 100.0;
			binaryPercentage += binP;

			double hexP = 0;
			for (signed long long k = 0; k < 60; ++k)
				if (hashMap.nodes[i].hash.stringified[k] == hashMap.nodes[j].hash.stringified[k])
					++hexP;
			hexP /= 60.0;
			hexP *= 100.0;
			hexPercentage += hexP;
		}

		binaryPercentage /= hashMap.count;
		hexPercentage /= hashMap.count;

		binaryPercentageAverage += binaryPercentage;
		hexPercentageAverage += hexPercentage;

		if (i % 5000 == 0)
		{
			fprintf(stdout, "Already processed %lld lines...\n", i);
		}
	}

	binaryPercentageAverage /= hashMap.count;
	hexPercentageAverage /= hashMap.count;
	fprintf(stdout, "Average binary percentage: %Lf\n", binaryPercentageAverage);
	fprintf(stdout, "Average hex percentage: %Lf\n", hexPercentageAverage);

	if (line)
	{
		free(line);
	}

	fclose(stream);
	HashMap_destroy(&hashMap);
	return 0;
}
