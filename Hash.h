#ifndef HASH_H
#define HASH_H

#include "Bool.h"
#include <limits.h>
#include <stdlib.h>


#define ERROR_PRIME_NOT_FOUND -1

#define HASH_SIZE_FACTOR 1.4

#define HASH_INIT_VALUE INT_MIN

/**
 * @brief Determines if a given `number` is prime or not.
 *
 * @param number The number to determine if is prime or not.
 * @return `TRUE` if the given `number` is prime. Else, `FALSE`.
 */
BOOLEAN isPrime(const int number) {
    for (int i = 2; i <= number / 2; ++i) {

        // If `number` is divisible by `i`, then `number` is not prime.
        if (number % i == 0) { return FALSE; }
    }
    return TRUE;
}

/**
 * @brief Gets the closest prime number that is greater or equals to a given
 *        `lowerLimit` number.
 *
 * @attention This function searches for the primes within the `lowerLimit` and
 *            `2 * lowerLimit` range. So in case there was no prime number to be
 *            found in this range, this function will return
 *            `ERROR_PRIME_NOT_FOUND`.
 *
 * @param lowerLimit A number that represents a lower limit. So that this
 *                   function will return the closest prime number that is
 *                   greater or equals to it.
 * @return The closest prime number that is greater or equals to a given
 *         `lowerLimit` number. Returns `ERROR_PRIME_NOT_FOUND` in case there
 *         was no prime to be found in the searchable range.
 */
int getPrimeNumberGreaterOrEqualsToLowerLimit(const int lowerLimit) {
    for (int i = lowerLimit; i < 2 * lowerLimit; ++i) {
        if (isPrime(i)) { return i; }
    }
    return ERROR_PRIME_NOT_FOUND;
}

/**
 * @brief The so called MAD method (MAD = Multiply Add Divide).
 *
 * Where `k` is the key and m is the table size. If we choose the values of `a`
 * and `b` randomly, then each time we pick a different value of `a` and `b` we
 * get a different hash function. Note that the table size `m` must be a prime
 * number (m >= 2). Also, `1 ≤ a ≤ m − 1` and `0 ≤ b ≤ m − 1`. Thus, we need to be a bit
 * careful when we choose these parameters.
 *
 * @see https://userpages.umbc.edu/~chang/cs341.f17/projects/proj5.shtml
 * @see https://crypto.stackexchange.com/questions/72799/how-to-prove-if-a-hash-function-is-collision-resistant
 * @see https://cseweb.ucsd.edu/~kube/cls/100/Lectures/lec16/lec16-8.html
 * @see https://docs.oracle.com/javase/1.5.0/docs/api/java/util/Hashtable.html
 * @see https://en.wikipedia.org/wiki/Hash_table#Collision_resolution
 */
static int getMADHash(const int a, const int k, const int b, const int m) {
    return (a * k + b) % m;
}

static int getHash(const int key, const int hashArraySize) {

    /*
     * Set `a` to `1`, and `b` to `0`, to make sure there is no overflow from
     * the memory size of `int` when calculating the "hash".
     */
    return getMADHash(1, key, 0, hashArraySize);
}

/**
 * @brief Creates an "open hash table" with the constant size of
 *        `hashArraySizeOutputParam`, where each element is initialized with
 *        `HASH_INIT_VALUE`.
 *
 * @attention Remember to `free` the returned value of this function after use.
 */
int *createHashArray(const int sourceArraySize, int *hashArraySizeOutputParam) {
    const int hashArraySizeAfterFactor =
            (int) (HASH_SIZE_FACTOR * sourceArraySize);
    *hashArraySizeOutputParam =
            getPrimeNumberGreaterOrEqualsToLowerLimit(hashArraySizeAfterFactor);
    int *hashArray = malloc(sizeof(int) * *hashArraySizeOutputParam);

    // Init `hashArray` with a value that will probably will never be a "key".
    for (int i = 0; i < *hashArraySizeOutputParam; i++) {
        hashArray[i] = HASH_INIT_VALUE;
    }

    return hashArray;
}

/**
 * @brief Gets the index where the given `key` is presented in the `hashArray`.
 *        In case the `key` is not present in the `hashArray`, then this
 *        function returns the next available index in the array, where
 *        `hashArray[index] == HASH_INIT_VALUE`.
 *
 * Runs in Theta(1/`HASH_SIZE_FACTOR`) in the average case. That means Theta(1)
 * in the average case.
 *
 * @param key The "key" to find it's mapped `index` in the given `hashArray`.
 * @param hashArray The "hash" array to search the given `key` in.
 * @param hashArraySize The size of the given `hashArray`.
 * @return - In case the given `key` was found in the `hashArray`:
 *           Returns the `index` in the `hashArray` where the given `key` is
 *           found at `hashArray[index]`. i.e. it returns the `index` that
 *           maintains `hashArray[index] == key`.
 *         - In case the given `key` was NOT found in the `hashArray`:
 *           Returns the last location in the hash sequence of the given `key`,
 *           where the stored value there is `HASH_INIT_VALUE`. i.e. it returns
 *           the `index` that maintains `hashArray[index] == HASH_INIT_VALUE`.
 */
int findIndexOfKey(const int key, const int *hashArray,
                   const int hashArraySize) {
    int index = getHash(key, hashArraySize);
    while ((hashArray[index] != key) && (hashArray[index] != HASH_INIT_VALUE)) {
        index = (index + 1) % hashArraySize; // Linear probing.
    }
    return index;
}

#endif //HASH_H
