#include <iostream>
#include "miniGit.hpp"
using namespace std;
namespace fs = std::filesystem; // will compile with g++ -stdc++17
// fs::remove_all(".minigit") will remove a directory and its contents
// fs::create_directory(".minigit") will create a new directory

int main()
{
    miniGit miniGit;
    // THE CODE BELOW DEALS WITH THE INITIALIZATION OF A NEW REPOSITORY
    int initialize = 0;
    while (initialize != 2)
    {
        cout << "Choose an option:" << endl
             << "1. Initialize a new repository." << endl
             << "2. Quit program" << endl;
        cin >> initialize;
        if (initialize == 1) // Code will run if the user chooses to initialize a new repository
        {
            fs::create_directory(".minigit"); // new directory initialized
            cout << "Repository initialized." << endl;
            break;
        }
        else if (initialize == 2) // Code will run and return if the user chooses to quit
        {
            cout << "Goodbye!" << endl;
            return 0;
        }
        else // Code will run and begin the loop again if the user enters an invalid input
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input." << endl
                 << endl;
        }
    }

    int commitNumber = 0;
    cout << endl;
    doublyNode *headDLL = miniGit.newDoublyNode(commitNumber, nullptr, nullptr, nullptr);
    doublyNode *currentCommit = headDLL;
    doublyNode *recentCommit = currentCommit;

    // THE CODE BELOW DEALS WITH THE REST OF THE PROGRAM, WHERE THE USER CAN ADD, DELETE, COMMIT, AND CHECK STATUS BEFORE QUITTING
    int userChoice = 0;
    int fileNumber = 0;
    while (userChoice != 6)
    {
        if (currentCommit == recentCommit)
        {
            // Options list that will loop until the user decides to quit the program
            cout << "Choose an option:" << endl
                 << "1. Add a file to the current commit." << endl
                 << "2. Remove a file from the current commit." << endl
                 << "3. Commit changes." << endl
                 << "4. Check a specific version." << endl
                 << "5. Display entire data structure." << endl
                 << "6. Quit program" << endl;
            cin >> userChoice;
            if (userChoice >= 1 && userChoice <= 6)
            {
                switch (userChoice)
                {
                case 1: // add a file to the current commit
                {
                    // BELOW CODE PROMPTS THE USER TO ENTER A FILENAME AND CHECKS WHETHER THE FILE WITH THE GIVEN NAME EXISTS IN THE CURRENT DIRECTORY
                    bool fileExists = false;
                    string userInputFilename;
                    while (fileExists == false)
                    {
                        cout << "Enter a file name: ";
                        cin >> userInputFilename;
                        ifstream checkFile(userInputFilename.c_str());
                        fileExists = checkFile.good();
                        if (fileExists == false)
                        {
                            cout << "File does not exist!" << endl
                                 << endl;
                        }
                    }

                    // BELOW CODE CHECKS THE SINGLY LINKED LIST OF THE CURRENT COMMIT TO SEE WHETHER THE FILE HAS ALREADY BEEN ADDED
                    singlyNode *crawler = currentCommit->head;
                    string fileNumberString = to_string(fileNumber);
                    string fileVersion = userInputFilename + "_" + fileNumberString;
                    if (crawler == nullptr) // Case A: SLL is empty
                    {
                        currentCommit->head = miniGit.newSinglyNode(userInputFilename, fileVersion, fileNumber, nullptr, currentCommit);
                        cout << "Success: File added -> " << currentCommit->head->fileName << endl;
                    }
                    else // Case B: SLL is not empty
                    {
                        while (crawler != nullptr)
                        {
                            if (crawler->fileName == userInputFilename)
                            {
                                cout << "Error: File has already been added" << endl;
                                break;
                            }
                            if (crawler->next == nullptr)
                            {
                                crawler->next = miniGit.newSinglyNode(userInputFilename, fileVersion, fileNumber, nullptr, currentCommit);
                                cout << "Success: File added -> " << crawler->next->fileName << endl;
                                break;
                            }
                            crawler = crawler->next;
                        }
                    }
                    cout << endl;
                    break;
                }

                case 2: // remove a file from the current commit
                {
                    // BELOW CODE PROMPTS THE USER TO ENTER A FILENAME AND CHECKS WHETHER THE FILE WITH THE GIVEN NAME EXISTS IN THE CURRENT DIRECTORY
                    bool fileExists = false;
                    string userInputFilename;
                    while (fileExists == false)
                    {
                        cout << "Enter a file name: ";
                        cin >> userInputFilename;
                        ifstream checkFile(userInputFilename.c_str());
                        fileExists = checkFile.good();
                        if (fileExists == false)
                        {
                            cout << "File does not exist!" << endl
                                 << endl;
                        }
                    }

                    // BELOW CODE TRAVERSES THE SLL OF THE CURRENT COMMIT TO FIND WHETHER THE FILENAME EXISTS, IF SO IT'S DELETED
                    singlyNode *previous = nullptr;
                    singlyNode *current = currentCommit->head;
                    if (current == nullptr) // if there are no elements in the SLL
                    {
                        cout << "Error: File not found in the current version of the repository" << endl;
                    }
                    else
                    {
                        while (current != nullptr)
                        {
                            if (current->next == nullptr && current->fileName != userInputFilename) // file name does not exists in repo
                            {
                                cout << "Error: File not found in the current version of the repository" << endl;
                                break;
                            }
                            if (current->fileName == userInputFilename && currentCommit->head == current) // case 1: file is the head of SLL
                            {
                                previous = current->next;
                                currentCommit->head = previous;
                                cout << "Success: File deleted -> " << current->fileName << endl;
                                delete current;
                                current = nullptr;
                                break;
                            }
                            else if (current->fileName == userInputFilename && currentCommit->head != current)
                            {
                                previous->next = current->next;
                                cout << "Success: File deleted -> " << current->fileName << endl;
                                delete current;
                                current = nullptr;
                                break;
                            }
                            previous = current;
                            current = current->next;
                        }
                    }
                    cout << endl;
                    break;
                }

                case 3: // commit changes
                {
                    singlyNode *crawler = currentCommit->head;
                    while (crawler != nullptr) // iterates through all elements of the SLL and checks if that file exists in .minigit
                    {
                        bool fileExists = miniGit.doesFileExist(crawler->fileVersion);
                        if (fileExists == false) // FILE DOES NOT EXIST IN .MINIGIT, copy file from current directory into the .minigit directory
                        {
                            cout << "File version does not exist in .minigit" << endl;
                            miniGit.copyFile(crawler->fileName, crawler->fileVersion);
                            cout << "Success: File copied from current directory into .minigit -> " << crawler->fileName << " copied as " << crawler->fileVersion << endl
                                 << endl;
                        }
                        else // FILE DOES EXISTS IN .MINIGIT, additional checks required
                        {
                            cout << "File version does exist in .minigit" << endl;
                            bool changed = false;
                            changed = miniGit.checkChanges(crawler->fileName, ".minigit/" + crawler->fileVersion);
                            if (changed == true) // FILE HAS BEEN CHANGED, COPY FILE FROM CURR DIR TO MINIGIT DIR, GIVE NAME W/ INCREMENTED VERSION NUMBER, UPDATE SLL NODE
                            {
                                cout << "File has been changed since last commit." << endl;
                                crawler->fileNumber += 1;
                                crawler->fileVersion = crawler->fileName + "_" + to_string(crawler->fileNumber);
                                miniGit.copyFile(crawler->fileName, ".minigit/" + crawler->fileVersion);
                                cout << "Success: File copied from current directory into .minigit -> " << crawler->fileName << " copied as " << crawler->fileVersion << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "Error: File is unchanged since last commit -> " << crawler->fileName << endl
                                     << endl;
                            }
                        }
                        if (crawler->next == nullptr)
                        {
                            break;
                        }
                        crawler = crawler->next;
                    }

                    // BELOW CODE COPIES THE LINKED LIST FROM THE PREVIOUS COMMIT TO THE CURRENT COMMIT
                    commitNumber++;
                    doublyNode *nextCommit = miniGit.newDoublyNode(commitNumber, nullptr, currentCommit, nullptr);
                    currentCommit->next = nextCommit;
                    recentCommit = nextCommit;
                    miniGit.copyFiles(currentCommit, currentCommit->head, nextCommit, nextCommit->head);
                    currentCommit = currentCommit->next;
                    cout << endl;
                    break;
                }

                case 4: // check a specific version
                {
                    int userInputNumber = 0;
                    cout << "Please enter a commit number to checkout: ";
                    cin >> userInputNumber;
                    recentCommit = miniGit.checkVersion(userInputNumber, currentCommit, recentCommit);
                    break;
                }

                case 5: // display entire data structure
                {
                    miniGit.displayAllNodes();
                    break;
                }

                case 6: // quit program
                {
                    cout << "Goodbye!" << endl;
                    return 0;
                }
                }
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input." << endl
                     << endl;
            }
        }
        else
        {
            // Options list that will loop until the user decides to quit the program
            cout << "Choose an option:" << endl
                 << "1. Check a specific version." << endl
                 << "2. Display entire data structure." << endl
                 << "3. Quit program" << endl
                 << "Note: Cannot add, delete, or commit files until returning to most recent commit." << endl;
            cin >> userChoice;
            if (userChoice >= 1 && userChoice <= 3)
            {
                switch (userChoice)
                {
                case 1: // check a specific version
                {
                    int userInputNumber = 0;
                    cout << "Please enter a commit number to checkout: ";
                    cin >> userInputNumber;
                    recentCommit = miniGit.checkVersion(userInputNumber, currentCommit, recentCommit);
                    break;
                }

                case 2: // display entire data structure
                {
                    miniGit.displayAllNodes();
                    break;
                }

                case 3: // quit program
                {
                    cout << "Goodbye!" << endl;
                    return 0;
                }
                }
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input." << endl
                     << endl;
            }
        }
    }
}