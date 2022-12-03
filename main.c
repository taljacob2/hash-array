#include "Hash.h"
#include <stdio.h>

#define SIZE 5

/**
 * @brief Prints an each element in an array only once.
 *
 * Runs in Theta(n) in the average case.
 *
 * @param sourceArray
 * @param sourceArraySize
 * @param hashArray
 * @param hashArraySize
 */
void privatePrintEachElementInArrayOnce(const int *sourceArray,
                                        const int  sourceArraySize,
                                        int *      hashArray,
                                        const int  hashArraySize) {
    for (int i = 0; i < sourceArraySize; i++) {
        const int index =
                findIndexOfKey(sourceArray[i], hashArray, hashArraySize);
        if (hashArray[index] == HASH_INIT_VALUE) {
            hashArray[index] = sourceArray[i]; // Insert to `hashArray`.
            printf("%d, ", sourceArray[i]);    // Do something.
        }
    }
}

/**
 * @brief Prints an each element in an array only once.
 *
 * Runs in O(n).
 *
 * @param sourceArray
 * @param sourceArraySize
 * @see privatePrintEachElementInArrayOnce(const int *, const int, int *, const int)
 */
void printEachElementInArrayOnce(const int *sourceArray,
                                 const int  sourceArraySize) {
    int  hashArraySize = 0;
    int *hashArray     = createHashArray(sourceArraySize, &hashArraySize);

    privatePrintEachElementInArrayOnce(sourceArray, sourceArraySize, hashArray,
                                       hashArraySize);

    free(hashArray);
}

int main() {
    int sourceArray[SIZE] = {1, 12, 1, 12, 1};

    //    // Init `sourceArray`.
    //    for (int i = 0; i < SIZE; i++) { sourceArray[i] = 0; }

    printEachElementInArrayOnce(sourceArray, SIZE);

    return 0;
}