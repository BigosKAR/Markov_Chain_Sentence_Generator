#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include "functions.h"

// Displays the menu options
void displayMenu()
{
    printf("--------------------------------\n");;
    printf("1. Display current sample text\n");
    printf("2. Generate Text\n");
    printf("0. Exit\n");
    printf("--------------------------------\n");
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
