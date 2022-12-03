#include "Hash.h"
#include <stdio.h>
#include <time.h>

#define SIZE 10

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

void printFirstHashes(const int *sourceArray, const int sourceArraySize) {
    int  hashArraySize = 0;
    int *hashArray     = createHashArray(sourceArraySize, &hashArraySize);

    // Print first hash.
    for (int i = 0; i < sourceArraySize; i++) {
        printf("%d, ", getHash(sourceArray[i], hashArraySize));
    }

    free(hashArray);
}

void initProgram() { srand(time(NULL)); }

int main() {
    initProgram();

    int sourceArray[SIZE];

    // Init `sourceArray`.
    for (int i = 0; i < SIZE; i++) { sourceArray[i] = rand(); }


    // Print `sourceArray`.
    for (int i = 0; i < SIZE; i++) { printf("%d, ", sourceArray[i]); }
    printf("\n");


    printFirstHashes(sourceArray, SIZE);
    //    printEachElementInArrayOnce(sourceArray, SIZE);
    printf("\n");

    return 0;
}