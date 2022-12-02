#ifndef HASH_H
#define HASH_H

#include "Bool.h"
#include <limits.h>
#include <stdlib.h>


#define ERROR_PRIME_NOT_FOUND -1

#define HASH_INIT_VALUE INT_MIN

BOOLEAN isPrime(int number) {
    for (int i = 2; i <= number / 2; ++i) {

        // If `number` is divisible by `i`, then `number` is not prime.
        if (number % i == 0) { return FALSE; }
    }
    return TRUE;
}

int getPrimeNumberGreaterOrEqualsToLMT(const int LMT) {
    for (int i = LMT; i < 2 * LMT; ++i) {
        if (isPrime(i)) { return i; }
    }
    return ERROR_PRIME_NOT_FOUND;
}

/**
 * @brief The so called MAD method (MAD = Multiply Add Divide).
 *
 * Where k is the key and m is the table size. If we choose the values of a and
 * b randomly, then each time we pick a different value of a and b we get a
 * different hash function. Note that the table size m must be a prime number.
 * Also, 1 ≤ a ≤ m − 1 and 0 ≤ b ≤ m − 1. Thus, we need to be a bit careful
 * when we choose these parameters.
 *
 * @param a
 * @param k
 * @param b
 * @param m NOTE: Must be at least "2".
 * @return
 *
 * @see https://userpages.umbc.edu/~chang/cs341.f17/projects/proj5.shtml
 */
int getMADHash(const int a, const int k, const int b, const int m) {
    return (a * k + b) % m;
}

int getHash(const int number, const int hashArraySize) {
    return getMADHash(1, number, 1, hashArraySize);
}

/**
 * @brief Creates a "hash" array with the size of `hashArraySizeOutputParam`,
 *        where each element is initialized with `HASH_INIT_VALUE`.
 *
 * @attention Remember to `free` the returned value of this function after use.
 *
 * @param sourceArraySize
 * @param hashArraySizeOutputParam
 * @return
 */
int *createHashArray(const int sourceArraySize, int *hashArraySizeOutputParam) {

    // `LMT` must be at least 2 times `sourceArraySize`.
    *hashArraySizeOutputParam =
            getPrimeNumberGreaterOrEqualsToLMT(2 * sourceArraySize);
    int *hashArray = malloc(sizeof(int) * *hashArraySizeOutputParam);

    // Init `hashArray` with a value that will probably will never be a "key".
    for (int i = 0; i < *hashArraySizeOutputParam; i++) {
        hashArray[i] = HASH_INIT_VALUE;
    }

    return hashArray;
}

#endif //HASH_H
