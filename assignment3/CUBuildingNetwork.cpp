/****************************************************************/
/*                CUBuildingNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*     This class uses a linked-list of CUBuilding structs to      */
/*     represet communication paths between buildings             */
/****************************************************************/

#include "CUBuildingNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;
/*
 * Purpose: Constructer for empty linked list
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
 *   between the building *previous and the Building that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding *previous, string buildingName, int numOfroom)
{
    if (previous == nullptr) // adding an element to the first node in the linked list (empty list)
    {
        CUBuilding *newBuilding = new CUBuilding;
        if (head == nullptr) // if there's nothing at the head of the linked list
        {
            head = newBuilding; // setting the head equal to the newBuilding
            head->name = buildingName; // setting the name to whatever is inputted
            head->totalRoom = numOfroom; // setting the room number to whatever is inputted
            head->next = nullptr; // setting the next node equal to a nullptr
        }
        else // if there is already an element in head and the new element needs to be the new head
        {
            newBuilding->next = head; // setting the element after the new node equal to head
            head = newBuilding; // setting the head equal to the new building
            head->name = buildingName; // setting the name of the head equal to the input
            head->totalRoom = numOfroom; // setting the number of rooms equal to the input
        }
        cout << "adding: " << buildingName << " (HEAD)" << endl; // printing the head
    }
    else // for all other elements of the linked list
    {
        CUBuilding *newBuilding = new CUBuilding;
        if (previous->next != nullptr) // if the previous element is pointing to another element
        {
            newBuilding->next = previous->next;
        }
        // if the previous element is not pointing to another element
        previous->next = newBuilding;
        newBuilding->name = buildingName;
        newBuilding->totalRoom = numOfroom;
        cout << "adding: " << buildingName << " (prev: " << previous->name << ")" << endl;
    }
}

/*
 * Purpose: populates the network with the predetermined buildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
    addBuildingInfo(NULL, "FLMG", 2);
    addBuildingInfo(head, "DLC", 10);
    addBuildingInfo(head->next, "ECOT", 6);
    addBuildingInfo(head->next->next, "CASE", 5);
    addBuildingInfo(head->next->next->next, "AERO", 4);
    addBuildingInfo(head->next->next->next->next, "RGNT", 9);
}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding *CUBuildingNetwork::searchForBuilding(string buildingName)
{
    if (head->name == buildingName)
    {
        return head;
    }
    else
    {
        CUBuilding *crawler;
        crawler = head;
        bool buildingFound = false;
        while (buildingFound == false)
        {
            if (crawler->name == buildingName)
            {
                buildingFound = true;
                return crawler;
            }
            if (crawler->next == nullptr)
            {
                return nullptr;
            }
            else
            {
                crawler = crawler->next;
            }
        }
    }
}

/*
 * Purpose:
 * @param string receiver
 * @param string msg
 */
void CUBuildingNetwork::transmitRoomInfo(string receiver)
{
    if (isEmpty() == true)
    {
        cout << "Empty list" << endl;
    }
    else
    {
        CUBuilding *crawler = head;

        bool isIn = false;
        bool buildingFound = false;

        while (buildingFound == false)
        {
            if (crawler->name == receiver)
            {
                buildingFound = true;
            }
            else if (crawler->next == nullptr && buildingFound == false)
            {
                cout << "Building not found" << endl;
            }
            if (crawler->next == nullptr)
            {
                break;
            }
            crawler = crawler->next;
        }
        CUBuilding *crawlerTwo = head;
        if (buildingFound == true)
        {
            while (isIn == false)
            {
                if (crawlerTwo->name == receiver)
                {
                    isIn = true;
                }
                string str = to_string(crawlerTwo->totalRoom);
                crawlerTwo->message = "available room at " + crawlerTwo->name + " is " + str;
                crawlerTwo->numberMessages++;
                cout << crawlerTwo->name << " [# messages received: " << crawlerTwo->numberMessages << "] received: " << crawlerTwo->message << endl;
                crawlerTwo = crawlerTwo->next;
            }
        }
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork()
{
    if (head == nullptr)
    {
        cout << "nothing in path" << endl;
    }
    else
    {
        while (head->next != nullptr)
        {
            cout << head->name << "(" << head->totalRoom << ")" << " -> ";
        }
        cout << "NULL";
    }
}