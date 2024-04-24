#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include "functions.h"

char* ReadFile(FILE *file){
    if(file == NULL){
        perror("Error opening file");
        exit(-1);
    } else {
        printf("File opened succesfully for reading \n");
    }

    char* f_text = (char*)malloc((1001) * sizeof(char)); //start with initial max size of 1000 characters
    f_text[0] = '\0'; //initialize the string to be empty
    char buffer[1000];
    while(fgets(buffer, sizeof(buffer), file) != NULL){
        int buffer_len = (int)(strlen(buffer));
        for(int i = 0; i < buffer_len; i++){
            if(buffer[i] == '\n'){ //CHANGE NEW LINE TO SPACE
                buffer[i] = ' ';
            }
        }
        strcat(f_text, buffer); //APPENDING BUFFER TO TEXT
    }
    f_text = realloc(f_text, strlen(f_text) + 1); //reallocating the memory to the exact size
    f_text[strlen(f_text)] = '\0'; //ensure the text is null-terminated
    return f_text;
}

void changingTextToNGrams(char* text, struct MarkovChain* m_chain, int lenght){
    for(int i = 0; i < lenght - ORDER + 1; i++){ // subtract 2 to prevent reading past the end of the string
        int check_var = 1;
        char ngram[ORDER+1];
        strncpy(ngram, text+i, ORDER);
        ngram[ORDER] = '\0';
        for (int j = 0; j < lenght; j++) {
            if (strcmp(m_chain->ngrams[j], ngram) == 0) {
                // N-gram already exists, no need to store it again
                check_var = 0;
                break;
            }
            else{
                continue;
            }
        }
        if(check_var == 1){
            strncpy(m_chain->ngrams[i], text+i, ORDER); //causes to add bro/row/own
            m_chain->ngrams[i][ORDER] = '\0'; // ensure the copied ngram is null-terminated
        }
    }
    removeNulls(m_chain->ngrams, 1000); //remove blank spaces made by duplicates
}

void addingNextChar(char* text, struct MarkovChain* m_chain, int lenght){
    int true_lenght = getTrueArrayLength(m_chain->ngrams, 1000); //gives length of the ngrams array without nulls
    //ADDING THE CHARACTER AFTER THE NGRAM TO NEXT ARRAY
    int next_index = 0;
    for(int i = 0; i < true_lenght; i++)
    {
        next_index = 0;
        char ngram[ORDER+1];
        strncpy(ngram, m_chain->ngrams[i], ORDER);
        ngram[ORDER] = '\0';
        for(int j = 0; j < lenght; j++){
            if(strncmp(ngram, text+j, ORDER) == 0){
                if (j+ORDER < lenght) {
                    char next_char = text[j+ORDER];
                    m_chain->next[i][next_index] = next_char;
                    next_index++;
                }
            }
        }
    }
}

void generateText(char* text, struct MarkovChain m_chain){
    //GENERATE NEW TEXT BASED ON NGRAMS
    char result[1000] = "";
    char temp_ngram[ORDER+1];
    strncpy(temp_ngram, text, ORDER);
    temp_ngram[ORDER] = '\0';
    strncat(result, temp_ngram, ORDER);
    for(int i=0; i<400; i++){
        char temp_string[2];
        int random_number_chars;
        int j = getIndex(m_chain.ngrams, temp_ngram, 1000);
        if(j == -1){
            printf("Ngram not found\n");
            break;
        }
        int nonNullCount = getNonNullCount(m_chain.next, 1000, j);
        if(nonNullCount > 1){
            random_number_chars = rand() % (nonNullCount - 1);
        }
        else if(nonNullCount == 1){ //if there is only one non-null character
            random_number_chars = 0;
        }
        else{
            printf("No non-null characters found\n");
            break;
}
        temp_string[0] = m_chain.next[j][random_number_chars];
        temp_string[1] = '\0'; //turning into a string
        strncat(result, temp_string, 1); //adding the random character to the result
        strncpy(temp_ngram, result + strlen(result) - ORDER, ORDER); //changing the ngram to the last n characters of the result
        temp_ngram[ORDER] = '\0'; //ensuring that the ngram is null-terminated
    }
    printf("Result: %s.\n", result);
}