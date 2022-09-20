
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

#include <hash256.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static inline void usage(
	FILE* stream,
	const char* arg0)
{
	assert(stream != NULL);
	fprintf(
		stream,
		"Usage: %s [Commands] <args>\n"
		"\n"
		"Commands:\n"
		"    [ --text | -t ] <string>       Provide a string to be hashed\n"
		"    [ --file | -f ] <path>         Provide file to be hashed\n",
		arg0
	);
}

static inline const char* shift(
	int* const argc,
	char*** const argv)
{
	const char* current = NULL;

	if (*argc > 0 && *argv != NULL)
	{
		current = **argv;
		*argc -= 1;
		*argv += 1;
	}

	return current;
}

static inline signed int hashAndPrint(
	const char* string,
	const signed long long length,
	const char* arg0)
{
	struct Hash256 hash = hash256(string, length);

	if (!hash.valid)
	{
		fprintf(stderr, "Error: `hash(...)` function failed!\n");
		usage(stderr, arg0);
		return -1;
	}

	fprintf(stdout, "%s\n", hash.stringified);
	return 0;
}

int main(
	int argc,
	char** argv)
{
	// Fetching program name from argc[0]
	const char* arg0 = shift(&argc, &argv);

	// Checking if user provided arguments to parse
	if (argc <= 0)
	{
		fprintf(stderr, "Error: no command-line arguments were provided!\n");
		usage(stderr, arg0);
		return -1;
	}

	// Setting up arguments and configs
	const char* text = NULL;
	const char* file = NULL;

	// Parsing command-line arguments
	while (argc > 0)
	{
		const char* flag = shift(&argc, &argv);

		if (flag == NULL)
		{
			fprintf(stderr, "Error: encountered undefined flag!\n");
			usage(stderr, arg0);
			return -1;
		}

		if (strcmp(flag, "--help") == 0 || strcmp(flag, "-h") == 0)
		{
			usage(stdout, arg0);
			return 0;
		}
		else if (strcmp(flag, "--text") == 0 || strcmp(flag, "-t") == 0)
		{
			if (argc <= 0)
			{
				fprintf(stderr, "Error: failed to find value for flag: %s!\n", flag);
				usage(stderr, arg0);
				return -1;
			}

			flag = shift(&argc, &argv);

			if (flag == NULL)
			{
				fprintf(stderr, "Error: encountered undefined flag!\n");
				usage(stderr, arg0);
				return -1;
			}

			text = flag;
			break;
		}
		else if (strcmp(flag, "--file") == 0 || strcmp(flag, "-f") == 0)
		{
			if (argc <= 0)
			{
				fprintf(stderr, "Error: failed to find value for flag: %s!\n", flag);
				usage(stderr, arg0);
				return -1;
			}

			flag = shift(&argc, &argv);

			if (flag == NULL)
			{
				fprintf(stderr, "Error: encountered undefined flag!\n");
				usage(stderr, arg0);
				return -1;
			}

			file = flag;
			break;
		}
	}

	if (text == NULL && file == NULL)
	{
		fprintf(stderr, "Error: neither text nor file was provided!\n");
		usage(stderr, arg0);
		return -1;
	}

	if (text != NULL)
	{
		return hashAndPrint(text, strlen(text), arg0);
	}
	else if (file != NULL)
	{
		FILE* stream = fopen(file, "r");

		if (stream == NULL)
		{
			fprintf(stderr, "Error: could not open the file %s!\n", file);
			usage(stderr, arg0);
			return -1;
		}

		fseek(stream, 0, SEEK_END);
		signed long fsize = ftell(stream);
		fseek(stream, 0, SEEK_SET);

		char* content = malloc(fsize + 1);
		fread(content, fsize, 1, stream);
		fclose(stream);

		content[fsize] = 0;
		signed int result = hashAndPrint(content, fsize, arg0);
		free(content);
		return result;
	}

	return 0;
}
