#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include "functions.h"

// Displays the menu options
void displayMenu()
{
    printf("--------------------------------\n");
    printf("1. Enter sample text\n");
    printf("2. Display current sample text\n");
    printf("3. Generate Text\n");
    printf("0. Exit\n");
    printf("--------------------------------\n");
}

// Adds sample text to the file and updates the text variable
void addSampleText(char fileName[100], char* text)
{
    FILE *file = fopen(fileName, "w");
    if(file == NULL){
        //perror("Error opening file");
        exit(-1);
    } else {
        //printf("File opened succesfully for writing \n");
    }
    char* new_text = (char*)malloc(1001*sizeof(char));
    text = realloc(text, 1001*sizeof(char));
    printf("Enter the sample text [Max 1000 characters]: \n");
    fgets(new_text, 1001, stdin); // Reads up to 999 characters and adds a null terminator
    fflush(stdin);
    size_t new_text_length = strlen(new_text);
    new_text[new_text_length] = '\0';
    writeToFile(fileName, new_text);
    strcpy(text, new_text);
    text = realloc(text, new_text_length*sizeof(char));
    free(new_text);
}

// Displays the current sample text
void displaySampleText(char* text)
{
    printf("--------------------------------\n");
    printf("The current sample text is: %s\n", text);
    printf("--------------------------------\n");
}

// Creates and displays the generated text
void displayGeneratedText(char* text, struct MarkovChain *m_chain)
{
    changingTextToNGrams(text, m_chain, (int)(strlen(text)));
    addingNextChar(text, m_chain, (int)(strlen(text)));
    generateText(text, *m_chain);
}
