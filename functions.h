#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define ORDER 3

struct MarkovChain
{
    char ngrams[1000][100];
    char next[1000][100];
};

//simple function to deal with arrays
void removeNulls(char ngram_array[][100], int array_length);
int getTrueArrayLength(char ngram_array[][100], int array_length);
int getIndex(char ngram_array[][100], char ngram[ORDER+1], int array_length);
int getNonNullCount(char array[][100], int outer_length, int index);

//functions that deal with the markov chain generation
char* ReadFile(FILE* file);
void changingTextToNGrams(char* text, struct MarkovChain* m_chain, int lenght);
void addingNextChar(char* text, struct MarkovChain* m_chain, int lenght);
void generateText(char* text, struct MarkovChain m_chain);


#endif 