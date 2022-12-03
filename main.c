#include "Hash.h"
#include <stdio.h>
#include <time.h>

#define SIZE 1000

/**
 * @brief Prints an each element in an array only once.
 *
 * Runs in Theta(n) in the average case.
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
 * Runs in Theta(n) in the average case.
 *
 * @see privatePrintEachElementInArrayOnce(const int *, const int, int *, const int)
 */
void printEachElementInArrayOnce(const int *sourceArray,
                                 const int  sourceArraySize) {
    int  hashArraySize = 0;
    int *hashArray     = createHashArray(sourceArraySize, &hashArraySize);

    privatePrintEachElementInArrayOnce(sourceArray, sourceArraySize, hashArray,
                                       hashArraySize);
    printf("\n");

    free(hashArray);
}

// For debug prints only.
void printFirstHashes(const int *sourceArray, const int sourceArraySize) {
    int  hashArraySize = 0;
    int *hashArray     = createHashArray(sourceArraySize, &hashArraySize);

    // Print first hash.
    for (int i = 0; i < sourceArraySize; i++) {
        printf("%d, ", getHash(sourceArray[i], hashArraySize));
    }
    printf("\n");

    free(hashArray);
}

void initProgram() { srand(time(NULL)); }

int main() {
    initProgram();

    int sourceArray[SIZE];

    // Init `sourceArray`.
    for (int i = 0; i < SIZE; i++) { sourceArray[i] = rand() % 20; }

    printf("Print `sourceArray`: \n");
    for (int i = 0; i < SIZE; i++) { printf("%d, ", sourceArray[i]); }
    printf("\n");

    printf("\n");

    printf("printEachElementInArrayOnce: \n");
    printEachElementInArrayOnce(sourceArray, SIZE);
    return 0;
}