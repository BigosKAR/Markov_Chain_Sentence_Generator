#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include "functions.h"

void displayMenu()
{
    printf("--------------------------------\n");
    printf("1. Enter sample text\n");
    printf("2. Display current sample text\n");
    printf("3. Generate Text\n");
    printf("0. Exit\n");
    printf("--------------------------------\n");
}

void addSampleText(char fileName[100], char* text)
{
    char* new_text = (char*)malloc(1000*sizeof(char));
    text = realloc(text, 1000*sizeof(char));
    printf("Enter the sample text [Max 1000 characters]: \n");
    scanf(" %[^\n]", new_text); 
    fflush(stdin);
    size_t new_text_length = strlen(new_text);
    new_text[new_text_length] = '\0';
    writeToFile(fileName, new_text);
    strcpy(text, new_text);
    text = realloc(text, new_text_length*sizeof(char));
    free(new_text);
}

void displaySampleText(char* text)
{
    printf("--------------------------------\n");
    printf("The current sample text is: %s\n", text);
    printf("--------------------------------\n");
}

void displayGeneratedText(char* text, struct MarkovChain *m_chain)
{
    printf("The current ngram order is: %d\n", ORDER);
    changingTextToNGrams(text, m_chain, (int)(strlen(text)));
    addingNextChar(text, m_chain, (int)(strlen(text)));
    generateText(text, *m_chain);
}
