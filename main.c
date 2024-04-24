#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <stdbool.h>
#include "functions.h"

char fileName[100] = "text.txt";

int main(){

    FILE *file = fopen(fileName, "r");
    struct MarkovChain m_chain;
    bool display_menu = 1;
    srand((unsigned int)time(NULL)); //did not work before adding unsigned int
    char* text = ReadFile(file);

    while(display_menu)
    {
        //fflush(stdin);
        displayMenu();
        int choice;
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                addSampleText(fileName, text);
                break;
            case 2:
                displaySampleText(text);
                break;
            case 3:
                displayGeneratedText(text, &m_chain);
                break;
            case 0:
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
    fclose(file);
    return 0;
}