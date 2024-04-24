#include <stdio.h>
#include <string.h>
#include "functions.h"

void removeNulls(char ngram_array[][100], int array_length) {
    int index = 0; // Initialize the index for non-null characters

    // Traverse the array of strings
    for (int i = 0; i < array_length; i++) {
        // If the current string is not empty
        if (ngram_array[i][0] != '\0') {
            // Move the non-null string to the front of the array
            strcpy(ngram_array[index++], ngram_array[i]);
        }
    }

    // Set remaining strings to empty
    for (int i = index; i < array_length; i++) {
        ngram_array[i][0] = '\0';
    }
}

int getTrueArrayLength(char ngram_array[][100], int array_length) {
    int count = 0;

    // Count non-empty strings in the array
    for (int i = 0; i < array_length; i++) {
        if (ngram_array[i][0] != '\0') {
            count++;
        }
    }

    return count;
}

int getIndex(char ngram_array[][100], char ngram[ORDER+1], int array_length) {
    for (int i = 0; i < array_length; i++) {
        if (strcmp(ngram_array[i], ngram) == 0) {
            return i;
        }
    }

    return -1;
}

int getNonNullCount(char array[][100], int outer_length, int index) {
    int count = 0;

    // Ensure the index is within the bounds of the outer array
    if (index < 0 || index >= outer_length) {
        printf("Index out of bounds\n");
        return -1;
    }

    // Count non-NULL characters in the array at the specified index
    for (int i = 0; i < 100; i++) {
        if(array[index][i] != '\0')count++;
    }

    return count;
}