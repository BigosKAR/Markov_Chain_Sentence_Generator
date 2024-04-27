#include <stdio.h>
#include <string.h>
#include "functions.h"

// Moves non-null strings to the front of the array and sets the remaining strings to empty
void removeNulls(char ngram_array[][100], int array_length) {
    int index = 0;

    for (int i = 0; i < array_length; i++) {
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

// Counts the length of an array without nulls
int getTrueArrayLength(char ngram_array[][100], int array_length) {
    int count = 0;


    for (int i = 0; i < array_length; i++) {
        if (ngram_array[i][0] != '\0') {
            count++;
        }
    }

    return count;
}

// Returns the index of a given ngram in the ngram array
int getIndex(char ngram_array[][100], char ngram[ORDER+1], int array_length) {
    for (int i = 0; i < array_length; i++) {
        if (strcmp(ngram_array[i], ngram) == 0) {
            return i;
        }
    }

    return -1;
}

// Returns the number of non-null characters in a string array at a given index
int getNonNullCount(char array[][100], int outer_length, int index) {
    int count = 0;

    // Ensure the index is within the bounds of the outer array
    if (index < 0 || index >= outer_length) {
        if(VERBOSE)printf("Index out of bounds\n");
        return -1;
    }

    // Count non-NULL characters in the array at the specified index
    for (int i = 0; i < 100; i++) {
        if(array[index][i] != '\0')count++;
    }

    return count;
}

int countFileCharacters(char fileName[100]){
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        if(VERBOSE)printf("Error opening file\n");
        return -1;
    }

    int count = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {
        count++;
    }

    fclose(file);
    return count;
}