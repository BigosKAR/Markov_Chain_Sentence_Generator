#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <stdbool.h>
#include "functions.h"

char fileName[100] = "text.txt";

int main(){
    struct MarkovChain m_chain;
    bool display_menu = 1;
    srand((unsigned int)time(NULL)); //did not work before adding unsigned int
    char* text = ReadFile(fileName);

    while(display_menu)
    {
        displayMenu();
        char choice[2];
        fgets(choice, 2, stdin);
        fflush(stdin);
        switch(choice[0])
        {
            case '1':
                addSampleText(fileName, text);
                break;
            case '2':
                displaySampleText(text);
                break;
            case '3':
                displayGeneratedText(text, &m_chain);
                break;
            case '0':
                display_menu = 0;
                break;  
            default:
                printf("Invalid choice\n");
                break;
        }
        printf("\n");
    }

    // free and close everything
    free(text);
    return 0;
}