#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include "functions.h"

// Reads the file and returns the content as a string
char* ReadFile(char fileName[100]){
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        if(VERBOSE)perror("Error opening file");
        exit(-1);
    } else {
        if(VERBOSE)printf("File opened succesfully for reading \n");
    }

    char* f_text = (char*)malloc((1001) * sizeof(char)); //start with initial max size of 1000 characters
    f_text[0] = '\0'; //initialize the string to be empty
    char buffer[1001];
    while(fgets(buffer, sizeof(buffer), file) != NULL){
        int buffer_len = (int)(strlen(buffer));
        for(int i = 0; i < buffer_len; i++){
            if(buffer[i] == '\n'){  //replace newline characters with spaces
                buffer[i] = ' ';
            }
        }
        strcat(f_text, buffer); // appending the buffer to the f_text
    }
    f_text = realloc(f_text, strlen(f_text) + 1); //reallocating the memory to the exact size
    f_text[strlen(f_text)] = '\0'; //ensure the text is null-terminated
    fclose(file);
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
    char result[1001] = "";
    char temp_ngram[ORDER+1];
    strncpy(temp_ngram, text, ORDER);
    temp_ngram[ORDER] = '\0';
    strncat(result, temp_ngram, ORDER);
    for(int i=0; i<400; i++){
        char temp_string[2];
        int random_number_chars;
        int j = getIndex(m_chain.ngrams, temp_ngram, 1000);
        if(j == -1){
            if(VERBOSE)printf("Ngram not found\n");
            break;
        }
        int nonNullCount = getNonNullCount(m_chain.next, 1000, j);
        if(nonNullCount > 1){
            random_number_chars = rand() % nonNullCount;
        }
        else if(nonNullCount == 1){ //if there is only one non-null character
            random_number_chars = 0;
        }
        else{
            // If the ngram is the last one (no character in m_chain.next), start over with first ngram
            strncat(result, " ", 1); // Adding a space to separate the words in this case
            strncat(result, m_chain.ngrams[0], ORDER);
            strncpy(temp_ngram, m_chain.ngrams[0], ORDER);
            temp_ngram[ORDER] = '\0';
            continue;
        }
        temp_string[0] = m_chain.next[j][random_number_chars];
        temp_string[1] = '\0'; //turning into a string
        strncat(result, temp_string, 1); //adding the random character to the result
        strncpy(temp_ngram, result + strlen(result) - ORDER, ORDER); //changing the ngram to the last n characters of the result
        temp_ngram[ORDER] = '\0'; //ensuring that the ngram is null-terminated
    }
    result[strlen(result)] = '\0';
    printf("\nThe current ngram order is: %d\n", ORDER);
    printf("------------NEW TEXT------------\n");
    printf("%s.\n", result);
}