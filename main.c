#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include "functions.h"

int main(){

    FILE *file = fopen("text.txt", "r");
    struct MarkovChain m_chain;

    srand((unsigned int)time(NULL)); //did not work before adding unsigned int

    char* text = ReadFile(file);

    changingTextToNGrams(text, &m_chain, (int)(strlen(text)));
    addingNextChar(text, &m_chain, (int)(strlen(text)));
    generateText(text, m_chain);

    // free and close everything
    free(text);
    fclose(file);
    return 0;
}