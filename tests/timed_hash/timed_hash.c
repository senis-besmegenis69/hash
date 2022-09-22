
/**
 * @file timed_hash.c
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
#include <time.h>

int main(
	void)
{
	FILE* output = fopen("./output.csv", "w");
	assert(output != NULL);
	fprintf(output, "length,lines,miliseconds\n");

	FILE* stream = fopen("./data.txt", "r");
	assert(stream != NULL);
	ssize_t read; char* line; size_t length = 0;

	signed int _end = 0;

	int avg_miliseconds = 0;

	for (signed long long i = 1; !_end; i *= 2)
	{
		signed long long len = 0;
		signed long long lines = 0;

		for (signed int k = 0; k < 5; ++k)
		{
			char* buffer = (char*)malloc((1204 * i + 1) * sizeof(char));
			assert(buffer != NULL);

			fseek(stream, 0, SEEK_SET);

			for (signed long long j = 0; j < i; ++j)
			{
				if ((read = getline(&line, &length, stream)) != -1)
				{
					memcpy(buffer + len, line, read);

					if (k == 0)
					{
						len += read;
						lines += 1;
					}
				}
				else
				{
					_end = 1;
					k = 5;
				}
			}

			buffer[len] = 0;

			int msec = 0;
			clock_t before = clock();
			struct Hash256 hash = hash256(buffer, len);
			clock_t difference = clock () - before;
			msec = difference * 1000 / CLOCKS_PER_SEC;
			avg_miliseconds += msec;

			free(buffer);
		}
		
		double avg_miliseconds_result = avg_miliseconds / 5.0;
		fprintf(output, "%d,%d,%f\n", len, lines, avg_miliseconds_result);
	}

	if (line)
	{
		free(line);
	}

	fclose(stream);
	return 0;
}
