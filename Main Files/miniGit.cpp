#include "miniGit.hpp"
using namespace std;

// implementation of the miniGit class and functions

// Purpose: Set the head of the doubly linked list as null
miniGit::miniGit()
{
    DLLhead = nullptr;
}

// Purpose: Copy files from the previous commit to the current commit
void miniGit::copyFiles(doublyNode *&currentCommit, singlyNode *&currentCommitHead, doublyNode *&nextCommit, singlyNode *&nextCommitHead)
{
    if (currentCommitHead == nullptr)
        return;
    singlyNode *copyFrom = currentCommitHead;
    singlyNode *copyToPrev = nullptr;
    singlyNode *copyTo = nextCommitHead;
    while (copyFrom != nullptr)
    {
        if (copyFrom->next == nullptr)
        {
            copyTo = newSinglyNode(copyFrom->fileName, copyFrom->fileVersion, copyFrom->fileNumber, nullptr, nextCommit);
            if (copyToPrev == nullptr)
            {
                nextCommit->head = copyTo;
                return;
            }
            copyToPrev->next = copyTo;
            return;
        }
        copyTo = newSinglyNode(copyFrom->fileName, copyFrom->fileVersion, copyFrom->fileNumber, nullptr, nextCommit);
        if (copyToPrev != nullptr)
        {
            copyToPrev->next = copyTo;
        }
        copyFrom = copyFrom->next;
        copyToPrev = copyTo;
        copyTo = copyTo->next;
    }
}

// Purpose: Split a given string and place into an array of strings
int miniGit::split(string phrase, char del, string words[], int size)
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

// Purpose: Find whether or not a file exists in the repository given the file version
bool miniGit::doesFileExist(string fileVersion)
{
    string path = ".minigit";
    string words[2];
    string lines;
    for (const auto &entry : fs::directory_iterator(path)) // iterates through all of the files in the given path
    {
        split(entry.path(), '/', words, 2);
        if (words[1] == fileVersion)
        {
            return true;
        }
    }
    return false;
}

// Purpose: Copy the contents of one file into another, specifically designed for the commit function
void miniGit::copyFile(string fileName, string fileVersion)
{
    ifstream inFile;
    ofstream outFile(".minigit/" + fileVersion);
    inFile.open(fileName);
    outFile.open(fileVersion);
    if (inFile.is_open() && outFile.is_open())
    {
        filebuf *inbuf = inFile.rdbuf();
        filebuf *outbuf = outFile.rdbuf();
        char currentChar = inbuf->sbumpc();
        while (currentChar != EOF)
        {
            outbuf->sputc(currentChar);
            currentChar = inbuf->sbumpc();
        }
        cout << "Success: File copied into .minigit" << endl;
    }
    else
    {
        cout << "Error: File(s) could not be opened" << endl;
    }
    inFile.close();
    outFile.close();
}

// Purpose: Determine whether or not a file has been changed since the last commit
bool miniGit::checkChanges(string currFile, string gitFile)
{
    ifstream curr, git;
    curr.open(currFile);
    git.open(gitFile);
    if (curr.is_open() && git.is_open())
    {
        filebuf *inbufCurr = curr.rdbuf();
        filebuf *inbufGit = git.rdbuf();
        char currChar = inbufCurr->sbumpc();
        char gitChar = inbufGit->sbumpc();
        if (currChar == EOF && gitChar == EOF)
        {
            return false;
        }
        while (currChar != EOF || gitChar != EOF)
        {
            if (currChar != gitChar)
            {
                return true;
            }
            currChar = inbufCurr->sbumpc();
            gitChar = inbufGit->sbumpc();
        }
        curr.close();
        git.close();
        return false;
    }
    else
    {
        cout << "Error: File(s) could not be opened" << endl;
        curr.close();
        git.close();
        return true;
    }
}

// Purpose: Read an entire file into a single string, used to compare two files and if they have been changed or not
string miniGit::readFileIntoString(const string &path)
{
    ifstream input_file(path);
    if (!input_file.is_open())
    {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

// Purpose: Copy the contents of one file into another, specifically designed for the checkout function
void miniGit::copyFileCheckout(string fileName, string fileVersion)
{
    ifstream inFile;
    ofstream outFile(fileName);
    inFile.open(".minigit/" + fileVersion);
    outFile.open(fileName, std::ofstream::out | std::ofstream::trunc);
    if (inFile.is_open() && outFile.is_open())
    {
        filebuf *inbuf = inFile.rdbuf();
        filebuf *outbuf = outFile.rdbuf();
        char currentChar = inbuf->sbumpc();
        while (currentChar != EOF)
        {
            outbuf->sputc(currentChar);
            currentChar = inbuf->sbumpc();
        }
        cout << "Success: File overwritten into current directory" << endl;
    }
    else
    {
        cout << "Error: File(s) could not be opened" << endl;
    }
    inFile.close();
    outFile.close();
}

// Purpose: Allow user to check a passed version
doublyNode *miniGit::checkVersion(int commitNumber, doublyNode *&currCommit, doublyNode *&recCommit)
{
    if (DLLhead == nullptr) // considering that there are no elements in the DLL
    {
        cout << "Invalid commit number" << endl;
        return currCommit;
    }
    doublyNode *crawler = DLLhead;
    singlyNode *crawlerS = DLLhead->head;
    int userChoice = 0;
    while (crawler != nullptr)
    {
        if (crawler->commitNumber == commitNumber)
        {
            while (userChoice != 2)
            {
                cout << "Valid commit number (WARNING: LOCAL CHANGES WILL BE LOST IF NOT COMMITTED BEFORE CHECKOUT)" << endl
                     << "Would you like to continue with the checkout?" << endl
                     << "1. Yes, continue to checkout." << endl
                     << "2. No, return to main menu." << endl;
                cin >> userChoice;
                if (userChoice == 1)
                {
                    cout << "Check out on Commit Number " << crawler->commitNumber << endl;
                    recCommit = crawler;
                    if (crawlerS == nullptr)
                    {
                        cout << "Error: No files in commit" << endl;
                        return currCommit;
                    }
                    while (crawlerS != nullptr)
                    {
                        bool fileExist = false;
                        fileExist = doesFileExist(crawlerS->fileVersion);
                        if (fileExist == false)
                        {
                            cout << "Error: Files do not exist in repo" << endl;
                            return currCommit;
                        }
                        copyFileCheckout(crawlerS->fileName, crawlerS->fileVersion);
                        cout << "Success: File " << crawlerS->fileName << " overwritten by " << crawlerS->fileVersion << " from .minigit repo" << endl;
                        if (crawlerS->next == nullptr)
                        {
                            return recCommit;
                        }
                        crawlerS = crawlerS->next;
                    }
                }
                else if (userChoice == 2)
                {
                    return currCommit;
                }
                else
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid option" << endl << endl;
                }
            }
        }
        if (crawler->next == nullptr)
        {
            cout << "Invalid commit number" << endl;
            return currCommit;
        }
        crawler = crawler->next;
        crawlerS = crawler->head;
    }
    return currCommit;
}

// Purpose: Display all nodes in the data structure
void miniGit::displayAllNodes()
{
    doublyNode *crawlerDLL = DLLhead;
    if (crawlerDLL == nullptr)
    {
        cout << "No elements in linked list" << endl
             << endl;
        return;
    }
    while (crawlerDLL != nullptr)
    {
        singlyNode *crawlerSLL = crawlerDLL->head;
        cout << "Commit Number " << crawlerDLL->commitNumber << " -> ";
        if (crawlerSLL == nullptr)
        {
            cout << "nullptr" << endl;
        }
        else
        {
            while (crawlerSLL != nullptr)
            {
                cout << crawlerSLL->fileName << ", " << crawlerSLL->fileVersion << ", " << crawlerSLL->fileNumber << " -> ";
                if (crawlerSLL->next == nullptr)
                {
                    cout << "nullptr" << endl;
                    break;
                }
                crawlerSLL = crawlerSLL->next;
            }
        }
        if (crawlerDLL->next == nullptr)
        {
            cout << endl;
            return;
        }
        crawlerDLL = crawlerDLL->next;
    }
}

// Purpose: Create a new singly linked list node
singlyNode *miniGit::newSinglyNode(string fileName, string fileVersion, int fileNumber, singlyNode *next, doublyNode *currentCommit)
{
    singlyNode *newSLLN = new singlyNode;
    newSLLN->fileName = fileName;
    newSLLN->fileVersion = fileVersion;
    newSLLN->fileNumber = fileNumber;
    newSLLN->next = next;
    if (currentCommit->head == nullptr)
        currentCommit->head = newSLLN;
    return newSLLN;
}

// Purpose: Create a new doubly linked list node
doublyNode *miniGit::newDoublyNode(int commitNumber, singlyNode *head, doublyNode *previous, doublyNode *next)
{
    doublyNode *newDLLN = new doublyNode;
    newDLLN->commitNumber = commitNumber;
    newDLLN->head = head;
    newDLLN->previous = previous;
    newDLLN->next = next;
    if (previous != nullptr)
        previous->next = newDLLN;
    if (DLLhead == nullptr)
        DLLhead = newDLLN;
    return newDLLN;
}