#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <stdbool.h>
#include "functions.h"

int main(int argc, char *argv[]){
    
    char* text;

    if (argc >= 2) {
        text = ReadFile(argv[1]);
        printf("Loaded sample text: %s\n", argv[1]);
    }
    else if (argc == 1)
    {
        // Default case if no file is provided
        text = ReadFile("./sample_texts/default.txt");
        printf("Loaded sample text: default.txt\n");
    }
    else{
        printf("Invalid number of arguments\n");
        return -1;
    }

    struct MarkovChain m_chain;
    bool display_menu = 1;
    srand((unsigned int)time(NULL)); //did not work before adding unsigned int

    while(display_menu)
    {
        displayMenu();
        char choice[2];
        fgets(choice, 2, stdin);
        fflush(stdin);
        switch(choice[0])
        {
            case '1':
                displaySampleText(text);
                break;
            case '2':
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