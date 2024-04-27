#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define ORDER 3
#define VERBOSE 0

struct MarkovChain
{
    char ngrams[1000][100];
    char next[1000][100];
};

//functions that deal with the markov chain generation
char* ReadFile(char fileName[100]);
void changingTextToNGrams(char* text, struct MarkovChain* m_chain, int lenght);
void addingNextChar(char* text, struct MarkovChain* m_chain, int lenght);
void generateText(char* text, struct MarkovChain m_chain);

//functions that deal with the menu
void displayMenu();
void displaySampleText(char* text);
void displayGeneratedText(char* text, struct MarkovChain *m_chain);

//other functions
void removeNulls(char ngram_array[][100], int array_length);
int getTrueArrayLength(char ngram_array[][100], int array_length);
int getIndex(char ngram_array[][100], char ngram[ORDER+1], int array_length);
int getNonNullCount(char array[][100], int outer_length, int index);
int countFileCharacters(char fileName[100]);

#endif 