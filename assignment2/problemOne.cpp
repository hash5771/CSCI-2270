// Hassan Shahzad
// CSCI 2270-200 | Professor Maciej Zagrodzki
// CSCI 2270-205 | TA Krishna Sai Chemudupati
// Assignment 2, Problem 1
// Due: February 7th, 2021

/*
Objectives:
1. Read a file with unknown size and store its contents in a dynamic array.
2. Store, search, and iterate through data in an array of structs.
3. Use array doubling via dynamic memory to increase the size of the array.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct wordRecord
{
    string word;
    int count;
};

// function will read the stop words from the file with the name stored ignoreWordFileName and store them in the ignoreWords array, assuming there is 50 stop words
void getIgnoreWords(const char *ignoreWordFileName, string ignoreWords[])
{
    // opening the ignoreWordFileName
    ifstream file;
    file.open(ignoreWordFileName);
    if (!file.is_open()) // if the file fails to open, print message
    {
        cout << "Failed to open " << ignoreWordFileName << endl;
    }
    else // if file opens, store contents into the ignoreWords array
    {
        int i = 0;
        string lines = "";
        while (getline(file, lines))
        {
            ignoreWords[i] = lines;
            i++;
        }
        file.close();
    }
}

// function will return whether word is in the ignoreWords array
bool isIgnoreWord(string word, string ignoreWords[])
{
    for (int i = 0; i < 50; i++) // looping through all of the elements of the ignoreWords array and comparing each to the inputted word
    {
        if (word == ignoreWords[i]) // checking to see if the word is in the array
        {
            return true;
        }
    }
    return false; // if not, return false
}

// function will compute the total number of words in the entire document by summing up all the counts of the individual unique words, function returns sum
int getTotalNumberNonIgnoreWords(wordRecord distinctWords[], int length)
{
    int totalNumberNonIgnoreWords = 0; // initializing a variable to keep in track of the total count of non ignore words
    for (int i = 0; i < length; i++)   // looping through the distinctWords array and adding each index's count to the variable
    {
        totalNumberNonIgnoreWords += distinctWords[i].count;
    }
    return totalNumberNonIgnoreWords;
}

// function will sort the distinctWords array by word count (descending order), no return value and no usage of the sort function
void sortArray(wordRecord distinctWords[], int length)
{
    for (int i = 0; i < length; i++) // implementation of bubble sort
    {
        for (int j = i + 1; j < length; j++)
        {
            if (distinctWords[j].count > distinctWords[i].count)
            {
                swap(distinctWords[j], distinctWords[i]);
            }
            else if (distinctWords[j].count == distinctWords[i].count)
            {
                if (distinctWords[j].word < distinctWords[i].word)
                {
                    swap(distinctWords[j], distinctWords[i]);
                }
            }
        }
    }
}

// function will print the next 10 words after the starting index N from the sorted array of distinct words. 10 words must be printed with their probability of occurence
// up to 5 decimal places. Probability of occurence of a word at positive ind in the array is computed using: probability-of-occurence = (float) uniqueWords[ind].count / totalNumWords
void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords)
{
    float probabilityOfOccurence = 0;
    for (int i = N; i < N + 10; i++)
    {
        probabilityOfOccurence = (float)(distinctWords[i].count) / (float)(totalNumWords); // casting type int variable to float
        printf("%.5f", probabilityOfOccurence);                                            // floating point rounder rounds the probability of occurence to 5 decimal places
        cout << " - " << distinctWords[i].word << endl;
    }
    return;
}

int main(int argc, char *argv[]) // takes in a number N, the filename of the text, and the filename of the ignore words text
{
    // argv[1] = N, argv[2] = mobydick.txt, argv[3] = ignoreWords.txt
    if (argc != 4) // if the number of command line arguments is incorrect
    {
        cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt" << endl;
        return 0;
    }
    else // if the number of command line arguments is correct
    {
        int numDistinctWords = 100;
        string ignoreWords[50];                                       // the words to be ignored while reading the text
        wordRecord *distinctWords = new wordRecord[numDistinctWords]; // this is a dynamic array that will double after filling up
        getIgnoreWords(argv[3], ignoreWords);

        ifstream file;
        file.open(argv[2]);
        string lines = "";
        bool ignoreThisWord = false;
        bool alreadyAllocated = false;
        int numWordsStored = 0;
        int numArrayDoubles = 0;
        while (file >> lines) // reading the file
        {
            if (numWordsStored == numDistinctWords) // dynamically sizing the array as needed | EXECUTING
            {
                wordRecord *temp = new wordRecord[2 * numDistinctWords]; // allocating memory for a new array that is 2 * numDistinctWords long
                for (int i = 0; i < numDistinctWords; i++)               // copying the elements from the old array to the new array
                {
                    temp[i] = distinctWords[i];
                }
                delete[] distinctWords;                  // returning memory to the heap
                distinctWords = temp;                    // assigning distinctWords to point to temp
                numDistinctWords = 2 * numDistinctWords; // doubling the size of numDistinctWords
                numArrayDoubles = numArrayDoubles + 1;
            }
            ignoreThisWord = isIgnoreWord(lines, ignoreWords);
            if (ignoreThisWord == true) // if the word being read is in the ignoreWords array, then ignore it | EXECUTING
            {
                ignoreThisWord = true;
            }
            else // if the word being read is unique, store it into an array of structs | EXECUTING
            {
                alreadyAllocated = false;
                for (int j = 0; j < numWordsStored; j++) // loop compares the word to the rest of the distinctWords array to see if it is already allocated
                {
                    if (distinctWords[j].word == lines) // if so add one to the count for the array
                    {
                        distinctWords[j].count += 1;
                        alreadyAllocated = true;
                    }
                }
                if (alreadyAllocated == false) // if not, store the element into the array of structs
                {
                    distinctWords[numWordsStored].word = lines;
                    distinctWords[numWordsStored].count = 1;
                    numWordsStored++;
                }
            }
        } // end of while loop
        file.close();
        int N = stoi(argv[1]);
        int totalNumberNonIgnoreWords = getTotalNumberNonIgnoreWords(distinctWords, numWordsStored);
        sortArray(distinctWords, numWordsStored);
        cout << "Array doubled: " << numArrayDoubles << endl
             << "Distinct non-common words: " << numWordsStored << endl
             << "Total non-common words: " << totalNumberNonIgnoreWords << endl
             << "Probability of next 10 words from rank " << N << endl
             << "---------------------------------------" << endl;
        printTenFromN(distinctWords, N, totalNumberNonIgnoreWords);
        return 0;
    }
}