/****************************************************************/
/*                   Assignment 4 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "CUBuildingNetwork.hpp"

using namespace std;

void displayMenu();
void handleUserInput(CUBuildingNetwork& CUBuildingNet);

int main(int argc, char* argv[])
{
    // Object representing our list of CUBuildings.
    CUBuildingNetwork CUBuildingNet;

    // This will loop until user selects quit option
    handleUserInput(CUBuildingNet);

    // quit: clean up!
    CUBuildingNet.printNetwork();

    return 0;
}

/*
 * Purpose: handle the interaction with the user
 * @param CUBuildingNet object for carrying out building network operations
 * @return none
 */
void handleUserInput(CUBuildingNetwork& CUBuildingNet)
{
    bool quit = false;
    string s_input;
    int input;

    // loop until the user quits
    while (!quit)
    {
        displayMenu();

        // read in input, assuming a number comes in
        getline(cin, s_input);
        try
        {
            input = stoi(s_input);
        }
        catch (exception& e)
        {
            // non-numeric input. trigger the default switch case.
            input = 10;
        }

        switch (input)
        {
            case 1: {
                //build network
                CUBuildingNet.loadDefaultSetup();
                CUBuildingNet.printNetwork();

                break;
            }

            case 2: {
                //print path
                CUBuildingNet.printNetwork();

                break;
            }

            case 3: {
                // add building
                string s1, roomNum, s2;

                cout << "Enter a new building name: " << endl;
                getline(cin, s1);

                cout << "Enter total room number: " << endl;
                getline(cin, roomNum);

                cout << "Enter the previous building name (or First): " << endl;
                getline(cin, s2);
                
                while(!(s2 == "First" || CUBuildingNet.searchForBuilding(s2))) 
                {
                    cout << "INVALID(previous building name)...Please enter a VALID building name!" << endl;
                    getline(cin, s2);
                }

                if(s2 == "First") {
                    CUBuildingNet.addBuildingInfo(NULL, s1, stoi(roomNum));
                }
                else {
                    CUBuildingNet.addBuildingInfo(CUBuildingNet.searchForBuilding(s2), s1, stoi(roomNum));
                }

                CUBuildingNet.printNetwork();

                break;
            }

            case 4: {
                // delete building
                string buildingName;
                cout << "Enter a building name: " << endl;
                getline(cin, buildingName);

                CUBuildingNet.deleteCUBuilding(buildingName);

                CUBuildingNet.printNetwork();

                break;
            }

            case 5: {
                // detect loop
                string building;
                cout << "Enter the building name to loop back: " <<endl;
                getline(cin, building);

                CUBuilding* lastnode = CUBuildingNet.createLoop(building);

                bool hasLoop = CUBuildingNet.detectLoop();

                if (hasLoop) {
                    cout << "Network contains a loop" << endl;
                    cout << "Breaking the loop"<< endl;
                    lastnode->next = NULL;
                } else {
                    cout << "Network does not contain a loop" << endl;
                }

                break;
            }

            case 6: {
                //re-adjust network
                string st, en;
                cout << "Enter the start index: " << endl;
                getline(cin, st);
                cout << "Enter the end index: " << endl;
                getline(cin, en);

                CUBuildingNet.readjustNetwork(stoi(st), stoi(en));

                CUBuildingNet.printNetwork();

                break;
            }

            case 7: {
                // delete entire network
                cout << "Network before deletion" << endl;
                CUBuildingNet.printNetwork();

                CUBuildingNet.deleteEntireNetwork();

                cout << "Network after deletion" <<endl;
                CUBuildingNet.printNetwork();

                break;
            }
            case 8: {
                // quit
                quit = true;
                cout << "Quitting... cleaning up path: " << endl;
                break;
            }

            default:     // invalid input
                cout << "Invalid Input" << endl;
                break;
        }
    }
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Add Building " << endl;
    cout << " 4. Delete Building " << endl;
    cout << " 5. Detect loop in Network" << endl;
    cout << " 6. Re-adjust Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
