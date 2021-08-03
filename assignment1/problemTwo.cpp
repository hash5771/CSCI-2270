// Hassan Shahzad
// CSCI 2270-200 | Professor Maciej Zagrodzki
// CSCI 2270-205 | TA Krishna Sai Chemudupati
// Assignment 1, Problem 2
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
#include <string>
using namespace std;

struct studentData
{
    string studentName;
    int homework;
    int recitation;
    int quiz;
    int exam;
    double average;
};

// this function takes in inputted information and stores it into a struct array
// length is the number of items currently stored int the array
void addStudentData(studentData students[], string studentName, int homework, int recitation, int quiz, int exam, int length)
{
    students[length].studentName = studentName;
    students[length].homework = homework;
    students[length].recitation = recitation;
    students[length].quiz = quiz;
    students[length].exam = exam;
    students[length].average = ((homework + recitation + quiz + exam) / 4.00);
}

// this function takes in the average numerical grade and returns the corresponding letter grade
char calcLetter(double avg)
{
    if (avg >= 90)
    {
        return 'A';
    }
    else if (avg < 90 && avg >= 80)
    {
        return 'B';
    }
    else if (avg < 80 && avg >= 70)
    {
        return 'C';
    }
    else if (avg < 70 && avg >= 60)
    {
        return 'D';
    }
    else
    {
        return 'F';
    }
}

// this function prints out the array of student names, numerical averages, and letter grades
void printList(const studentData students[], int length)
{
    for (int i = 0; i < length; i++)
    {
        char letterGrade = calcLetter(students[i].average);
        cout << students[i].studentName << " earned " << students[i].average << " which is a(n) " << letterGrade << endl;
    }
}

// split function from CSCI 1300
int split(string phrase, char del, string words[], int size)
{
    if (phrase.length() == 0)
    {
        return 0;
    }

    string piece = "";
    int arrpos = 0;

    for (int pos = 0; pos < phrase.length(); pos++)
    {
        if (phrase[pos] != del)
        {
            piece = piece + phrase[pos];
        }
        else
        {
            if (pos != 0 && pos != (phrase.length() - 1))
            {
                words[arrpos] = piece;
                piece = "";
                arrpos++;

                int check = pos + 1;
                if (phrase[check] == del)
                {
                    pos++;
                }
            }
            else
            {
                if (pos == (phrase.length() - 1))
                {
                    pos++;
                }
            }
        }
    }
    words[arrpos] = piece;

    int count = arrpos + 1;
    if (count > size)
    {
        return -1;
    }
    return count;
}

int main(int argc, char * argv[])
{
    studentData students[100];
    string inputFile = argv[1];
    string outputFile = argv[2];
    string sortArray[5];
    ifstream csvFileIn;
    csvFileIn.open(argv[1]);
    if (!csvFileIn.is_open())
    {
        cout << "Failed to open the file." << endl;
    }
    else
    {
        int i = 0;
        string lines = "";
        while (getline(csvFileIn, lines))
        {
            split(lines, ',', sortArray, 5);
            addStudentData(students, sortArray[0], stoi(sortArray[1]), stoi(sortArray[2]), stoi(sortArray[3]), stoi(sortArray[4]), i);
            i++;
        }
        printList(students, i);
        ofstream csvFileOut;
        csvFileOut.open(outputFile);
        for (int j = 0; j < i; j++)
        {
            char letterGrade = calcLetter(students[j].average);
            if (letterGrade >= * argv[3] && letterGrade <= * argv[4])
            {
                csvFileOut << students[j].studentName << students[j].average << letterGrade << endl;
            }
        }
        csvFileOut.close();
    }
    return 0;
}