/****************************************************************/
/*                Job Queue Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "JobQueue.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
	cout << "1. Add jobs into the queue" << endl;
	cout << "2. Dispatch jobs from the queue" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}
// Use getline for reading
int main(int argc, char const *argv[])
{
	JobQueue jobs;
	int menuOption = 0;
	while (menuOption != 3)
	{
		menu();
		cin >> menuOption;
		if (menuOption == 1)
		{
			cout << "Enter the number of jobs to be created:" << endl;
			int numJobs;
			cin >> numJobs;

			string job;
			for (int i = 0; i < numJobs; i++)
			{
				if (jobs.isFull())
				{
					cout << "Queue full, cannot add new job";
					break;
				}
				else
				{
					cout << "job" << i + 1 << ":" << endl;
					cin >> job;
					jobs.enqueue(job);
				}
			}
		}
		else if (menuOption == 2)
		{
			cout << "Enter the number of jobs to be dispatched:" << endl;
			int numDispatched;
			cin >> numDispatched;

			for (int j = 0; j < numDispatched; j++)
			{
				if (jobs.isEmpty())
				{
					cout << "No more jobs to be dispatched from queue" << endl;
				}
				else
				{
					cout << "Dispatched: " << jobs.peek() << endl;
					jobs.dequeue();
				}
			}
		}
		else if (menuOption == 3)
		{
			cout << "Number of jobs in the queue:" << jobs.queueSize();
		}
	}
}