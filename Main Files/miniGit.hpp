#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <limits>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

struct singlyNode
{
    string fileName;    // Name of local file
    string fileVersion; // Name of file in .minigit folder
    int fileNumber;
    singlyNode *next;
};

struct doublyNode
{
    int commitNumber; // first node will be zero
    singlyNode *head; // pointer to the SLL head
    doublyNode *previous;
    doublyNode *next;
};

class miniGit
{
private:
    doublyNode * DLLhead;
public:
    miniGit();
    void copyFiles(doublyNode *& currentCommit, singlyNode *& currentCommitHead, doublyNode *& nextCommit, singlyNode *& nextCommitHead); // option 3
    int split(string phrase, char del, string words[], int size); // option 3
    bool doesFileExist(string fileVersion); // option 3
    void copyFile(string fileName, string fileVersion); // option 3
    bool checkChanges(string currFile, string gitFile); // option 3
    string readFileIntoString(const string &path); // option 3
    void copyFileCheckout(string fileName, string fileVersion); // option 4
    doublyNode * checkVersion(int commitNumber, doublyNode *& currCommit, doublyNode *& recCommit); // option 4
    void displayAllNodes(); // option 5

    singlyNode * newSinglyNode(string fileName, string fileVersion, int fileNumber, singlyNode *next, doublyNode *currentCommit);
    doublyNode * newDoublyNode(int commitNumber, singlyNode *head, doublyNode *previous, doublyNode *next);
};