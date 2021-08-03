/*******************************************************************/
/*                CUBuildingNetwork Implementation                 */
/*******************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*       This class uses a linked-list of CUBuilding nodes to      */
/*       represent communication paths between buildings           */
/*******************************************************************/

#include "CUBuildingNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
CUBuildingNetwork::CUBuildingNetwork()
{
    /* finished. do not touch. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CUBuildingNetwork::isEmpty()
{
    /* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: Add a new building to the network
 *   between the CUBuilding *previous and the CUBuilding that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding *previous, string buildingName, int totalRoom)
{
    // TODO: Copy-paste your solution from Assignment 3
}

/*
 * Purpose: populates the network with the predetermined CUBuildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
    // TODO: Copy-paste your solution from Assignment 3
    // MODIFICATION: Use deleteEntireNetwork function before adding buildings
}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding *CUBuildingNetwork::searchForBuilding(string buildingName)
{
    // TODO: Copy-paste your solution from Assignment 3
}

/*
 * Purpose: Relay a message through the linked list until the specified CUBuilding
 * @param string receiver
 * @param string msg
 */
void CUBuildingNetwork::transmitRoomInfo(string receiver)
{
    // TODO: Copy-paste your solution from Assignment 3
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork()
{
    // TODO: Copy-paste your solution from Assignment 3
}

/****************************************************/
/*  ASSIGNMENT 4: Functions to be completed below.  */
/****************************************************/

/*
    QUESTION NUMBER 1
 * Purpose: Delete the CUBuilding in the network with the specified name.
 * @param buildingName name of the CUBuilding to delete in the network
 * @return none
 */
void CUBuildingNetwork::deleteCUBuilding(string buildingName)
{
    // TODO: Complete this function
    if (head->name == buildingName)
    {
        delete head;
        head = head->next;
        return;
    }
    CUBuilding * prev = head;
    CUBuilding * pres = head->next;
    while (pres != nullptr)
    {
        if (pres->name == buildingName)
        {
            prev->next = pres->next;
            delete pres;
            pres = nullptr;
            return;
        }
        else
        {
            prev = pres;
            pres = pres->next;
        }
    }
    cout << "Building does not exist." << endl;
}

/*
    QUESTION NUMBER 2
 * Purpose: deletes all CUBuildings in the network starting at the head CUBuilding.
 * @param: none
 * @return: none
 */
void CUBuildingNetwork::deleteEntireNetwork()
{
    // TODO: Complete this function
    if (head == nullptr)
    {
        return;
    }
    else
    {
        CUBuilding * prev = head;
        CUBuilding * pres = head->next;
        while (pres != nullptr)
        {
            cout << "deleting: " << prev->name << endl;
            delete prev;
            prev = pres;
            pres = pres->next;
        }
        cout << "deleting: " << prev->name << endl;
        delete prev;
        head = nullptr;
        cout << "Deleted network" << endl;
    }
}

/*
    QUESTION NUMBER 3
* Purpose: Creates a loop from last node to the CUBuilding specified.
* @param buildingName name of the CUBuilding to loop back
* returns the last node before loop creation (to break the loop)
*/
CUBuilding *CUBuildingNetwork::createLoop(string buildingName)
{
    // TODO: Complete this function
    CUBuilding * buildingNamePointer = searchForBuilding(buildingName);
    CUBuilding * lastElement = head;
    while (lastElement->next != nullptr)
    {
        lastElement = lastElement->next;
    }
    lastElement->next = buildingNamePointer;
}

/*
    QUESTION NUMBER 4
 * Purpose: to detect loop in the linked list
 * @return: true if loop is detected, else false
 */
bool CUBuildingNetwork::detectLoop()
{
    // TODO: Complete this function

    CUBuilding *slow = head;
    CUBuilding *fast = head;
    while (fast != nullptr || fast->next != nullptr)
    {
        if (fast->next == nullptr || fast->next->next == nullptr)
        {
            break;
        }
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
        {
            return true;
        }
    }
    return false;
}

/*
    QUESTION NUMBER 5
 * Purpose: Take the chunk of nodes from start index to end index
 *          Move that chunk to the end of the List
 * @param: start_index, end_index
 * @return: none
 */
void CUBuildingNetwork::readjustNetwork(int start_index, int end_index)
{
    // TODO: Complete this function
    // Function grabs the chunk of the linked list between start_index and end_index and sends it to the end of the linked list.
    if (head == nullptr) // if the linked list is empty
    {
        printf("Linked List is Empty");
        cout << endl;
    }
    else // if the linked list is not empty
    {
        // below code calculates the number of indexes in any given linked list
        int numIndex = 0;
        CUBuilding *crawler = head; // crawler starts at index zero
        while (crawler != nullptr)
        {
            if (crawler->next != nullptr)
            {
                crawler = crawler->next; // crawler is now at index one
                numIndex++;              // numIndex is incremented
            }
            else
            {
                numIndex++;
                break;
            }
        }

        // below code checks the two conditions states in the assignment
        if (end_index < 0 || end_index >= numIndex-1)
        {
            printf("Invalid end index");
            cout << endl;
            return;
        }
        if (start_index < 0 || start_index >= numIndex)
        {
            printf("Invalid start index");
            cout << endl;
            return;
        }
        if (start_index > end_index)
        {
            printf("Invalid indices");
            cout << endl;
            return;
        }

        // below code readjusts the linked list
        // there will always be an element at endPointer->next, but not always at head (if start_index is the head)
        CUBuilding *endPointer = head;
        CUBuilding *startPointer = head;
        for (int end = 0; end < end_index; end++)
        {
            endPointer = endPointer->next;
        }
        for (int start = 0; start < start_index; start++)
        {
            startPointer = startPointer->next;
        }

        // endPointer and startPointer now point to the respective elements placed in the indices

        if (start_index == 0) // if there are no elements before the chunk to be placed at the end
        {
            head = endPointer->next;
            crawler->next = startPointer;
            endPointer->next = nullptr;
        }
        else // if there are elements before the chunk to be placed at the end
        {
            CUBuilding *startPrevPointer = head;
            while (startPrevPointer->next != startPointer)
            {
                startPrevPointer = startPrevPointer->next;
            }
            startPrevPointer->next = endPointer->next;
            crawler->next = startPointer;
            endPointer->next = nullptr;
        }
    }
}

/*
 * Purpose: Destructor to delete the entire list on program termination
 * @param none
 * @return none
 */
CUBuildingNetwork::~CUBuildingNetwork()
{
    // TODO: Complete this function
}
