// Hassan Shahzad
// CSCI 2270-200 | Professor Maciej Zagrodzki
// CSCI 2270-205 | TA Krishna Sai Chemudupati
// Assignment 1, Problem 1
// Due: January 31st, 2021

/*
Objectives:
1. Read-in command line arguments.
2. Read a file.
3. Loop through an array.
4. Split a string.
5. Create an array of struct types.
6. Read and write to a file.
*/

#include <iostream>
#include <fstream>
using namespace std;

// this function takes in floats and places them in ascending order into an array, it returns the current size of the array
int addToArrayAsc(float sortedArray[], int numElements, float newValue)
{
    sortedArray[numElements] = newValue; // the last element of the array, is set as the new value
    int arrayIndex = numElements - 1;    // arrayIndex is the current number of array elements from 0 to numElements - 1
    if (numElements == 0)
    {
        sortedArray[0] = newValue; // the value is the first one placed into the empty array
    }
    else
    {
        for (int i = 0; i < numElements; i++) // loop goes until the newValue finds the correct position
        {
            if (newValue > sortedArray[arrayIndex - i]) // if the new value is greater than the value stored at sortedArray[arrayIndex], break
            {
                break;
            }
            else if (newValue <= sortedArray[arrayIndex - i]) // if the new value is smaller than the value to the left, swap them
            {
                swap(sortedArray[arrayIndex - i], sortedArray[numElements - i]); // swaps the new value with the value to the left
            }
        }
    }
    return numElements + 1; // an element is added to array, so numElements + 1 is returned
}

// main takes in a cmd lines argument of a text file filled with floats, then sorts them based on ascending value and prints out the elements each time getline executes
int main(int argc, char * argv[]) // argc is the number of arguments added in the cmd line, * argv[] points to the cmd line arguments with argv[0] being the program invoked from the cmd line (./a.out)
{
    float arrayOfFloats[100];
    ifstream inStream;
    inStream.open(argv[1]);
    if (!inStream.is_open()) // if the file fails to open
    {
        cout << "Failed to open the file." << endl;
        return 0;
    }
    else
    {
        string lines = "";
        int i = 0; // i is equal to the numElements
        while (getline(inStream, lines))
        {
            arrayOfFloats[i] = stof(lines);
            addToArrayAsc(arrayOfFloats, i, arrayOfFloats[i]); 
            i++;
            for (int j = 0; j < i; j++) // j prints out all portions of the array
            {
                cout << arrayOfFloats[j];
                if (j < i-1)
                {
                    cout << ",";
                }
            }
            cout << endl;
        }
        inStream.close();
        return 0;
    }
}