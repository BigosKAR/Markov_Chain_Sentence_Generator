#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <stdbool.h>
#include "functions.h"

char default_fileName[] = "./sample_texts/default.txt";

int main(int argc, char *argv[]){
    
    char* text;

    if (argc >= 2) {
        if(strstr(argv[1], ".txt") != NULL){
            if(countFileCharacters(argv[1]) > 1000){
            printf("The text file is too long to generate text\n");
            return -1;
            }
            else if(countFileCharacters(argv[1]) < ORDER){
            printf("The text file is too short to generate text\n");
            return -1;
            }
            else{
                if(VERBOSE)("The text file is of the correct length\n");
                text = ReadFile(argv[1]);
                printf("Loaded sample text: %s\n", argv[1]);
            }
        }
        else{
            printf("Invalid file type\n");
            return -1;
        }
    }
    else if (argc == 1)
    {
        // Default case if no file is provided
        if(countFileCharacters(default_fileName) > 1000){
            printf("The default text file is too long!\n");
            return -1;
        }
        else if(countFileCharacters(default_fileName) < ORDER){
            printf("The default text file is too short!\n");
            return -1;
        }
        else{
            if(VERBOSE)printf("The default text files is of the correct length\n");
            text = ReadFile("./sample_texts/default.txt");
        }
        printf("Loaded sample text: %s\n", default_fileName);
    }
    else{
        if(VERBOSE)printf("Invalid number of arguments\n");
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