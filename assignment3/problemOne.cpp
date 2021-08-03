// Hassan Shahzad
// CSCI 2270-200 | Professor Maciej Zagrodzki
// CSCI 2270-205 | TA Krishna Sai Chemudupati
// Assignment 3, Problem 1
// Due: February 14th, 2021

/*
Objectives:
1. Append to an array (array doubling).
2. Create, traverse, add nodes to a linked list.
3. Get practice implementing classes.
*/

#include <iostream>
using namespace std;

// this function emulates the push_back function from the vector class
// returns true if array doubling is performed, false if not
// str_arr is an array of string type in which elements will be inserted, a reference to this array pointer is what is passed
// s is a new string that is to be inserted into the string array
// numEntries keeps track of the number of elements that have been inserted in the array so far
// arraySize is the current size of the array
bool append (string *& str_arr, string s, int & numEntries, int & arraySize) // changes to the string array will persist even after the function returns
{
    bool returnValue = false;
    if (numEntries == arraySize) // if the array must double before the element is inserted
    {
        // the following code doubles the array:
        string * temp = new string[arraySize*2];
        for (int i = 0; i < arraySize; i++)
        {
            temp[i] = str_arr[i];
        }
        delete [] str_arr;
        str_arr = temp;
        arraySize = arraySize*2;
        returnValue = true;
    }
    if (numEntries < arraySize) // if the element can be inserted without array doubling
    {
        str_arr[numEntries] = s;
        numEntries++;
    }
    return returnValue;
}

int main()
{
    
}