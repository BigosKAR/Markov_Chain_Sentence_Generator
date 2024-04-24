# Markov Chain Text Generator
This project is a simple implementation of a Markov Chain text generator. It reads text from a file, breaks it down into n-grams (sequences of n characters), and uses these n-grams to generate new text that mimics the style of the input text.

# Structure
The project is structured around the MarkovChain struct, which holds the n-grams and the characters that follow each n-gram in the input text.

# Functions
The project includes several functions:

* removeNulls: Removes null entries from an array of strings.
* getTrueArrayLength: Returns the number of non-null entries in an array of strings.
* getIndex: Returns the index of a given n-gram in an array of n-grams.
* getNonNullCount: Returns the number of non-null entries in a specific row of a 2D array.
* ReadFile: Reads text from a file and returns it as a string.
* changingTextToNGrams: Breaks down the input text into n-grams and stores them in the MarkovChain structure.
* addingNextChar: Adds the character that follows each n-gram in the input text to the MarkovChain structure.
* generateText: Generates new text based on the n-grams and following characters stored in the MarkovChain structure.

# Note
This project uses the Markov property, which states that the probability of each character depends only on the previous n characters (the n-gram). This allows it to generate text that is statistically similar to the input text, even though it doesn't understand the meaning of the text.
