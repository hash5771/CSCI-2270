#include "JobQueue.hpp"
#include <iostream>

using namespace std;

JobQueue::JobQueue()
{
    queueFront = 0; // index to be dequeued next
    queueEnd = 0;   // index that keeps track of available space
    counter = 0;    // how many element are currently in the queue
}
bool JobQueue::isEmpty()
{
    if (counter == 0)
    {
        return true;
    }
    return false;
}
bool JobQueue::isFull()
{
    if (counter == 20)
    {
        return true;
    }
    return false;
}
void JobQueue::enqueue(std::string job)
{
    if (isFull() == false)
    {
        counter++;
        queue[queueEnd] = job;
        queueEnd++;
        if (queueEnd == 20)
        {
            queueEnd = 0;
        }
    }
    else
    {
        cout << "Queue full, cannot add new job" << endl;
    }
}
void JobQueue::dequeue()
{
    if (isEmpty() == false)
    {
        for (int i = 0; i < queueEnd - 1; i++)
        {
            queue[i] = queue[i + 1];
        }
        counter--;
        if (queueFront == 19)
        {
            queueFront = 0;
        }
        else
        {
            queueFront++;
        }
    }
    else
    {
        cout << "Queue empty, cannot dequeue a job" << endl;
    }
}
std::string JobQueue::peek()
{
    if (isEmpty() == true)
    {
        cout << "Queue empty, cannot peek" << endl;
        return "";
    }
    else
    {
        return queue[queueFront];
    }
}
int JobQueue::queueSize()
{
    return counter;
}
int JobQueue::getQueueFront()
{
    return queueFront;
}
int JobQueue::getQueueEnd()
{
    return queueEnd;
}
std::string *JobQueue::getQueue()
{
    return queue;
}