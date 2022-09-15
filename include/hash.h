
/**
 * @file hash.h
 *
 * @copyright This file is a part of the project hivelang and is distributed under MIT license that
 * should have been included with the project. If not, see https://choosealicense.com/licenses/mit/
 *
 * @author jorisb
 *
 * @date 2022-09-15
 */

#ifndef _HASH_H_
#define _HASH_H_

/**
 * @addtogroup hash
 *
 * @{
 */

/**
 * Process input string and return hashed value.
 * 
 * How it works:
 *     1. Allocate output array, check for errors for input value and allocated array.
 *     2. Checks if the input is shorter or longer than 64 chars array.
 *         2.1. If it is shorter, it will append chars, that were generated randomly, using the
 *              existing input for deterministic results.
 *         2.2. If is is shorter, it will try to "compress" the input to fit into the 64 chars
 *              array and, if there will empty space left, will execute 1.1. step.
 *     3. Using some sort of algorithm (most likely xor and bits shifting) and build the output
 *        string using the modified (steps 1.1 / 1.2 ) input.
 *     4. Return the hashed value.
 */
char* hash(
	const char* input,
	const signed long long length);

/**
 * @}
 */

#endif
