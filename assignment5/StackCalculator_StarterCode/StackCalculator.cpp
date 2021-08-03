#include <iostream>
#include "StackCalculator.hpp"

using namespace std;
/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
*/

// STACKS ARE LAST IN FIRST OUT DATA STRUCTURES

bool isNumber(string s)
{
  if (s.size() == 1 && s == "-")
  {
    return false;
  }
  else if (s.size() > 1 && s[0] == '-')
  {
    s = s.substr(1);
  }
  bool point = false;
  for (int i = 0; i < s.size(); i++)
  {
    if (!isdigit(s[i]) && s[i] != '.')
    {
      return false;
    }
    if (s[i] == '.' and !point)
    {
      point = true;
    }
    else if (s[i] == '.' and point)
    {
      return false;
    }
  }
  return true;
}

StackCalculator::StackCalculator()
{
  //TODO: Class constructor, sets the stackHead pointer to NULL
  stackHead = nullptr;
}

StackCalculator::~StackCalculator()
{
  //TODO: Destorys the stack, make sure there are no memory leaks
  if (stackHead == nullptr)
  {
    return;
  }
  else if (stackHead->next == nullptr)
  {
    delete stackHead;
    return;
  }
  else
  {
    while (stackHead->next != nullptr)
    {
      delete stackHead;
      stackHead = stackHead->next;
    }
    delete stackHead;
  }
}

bool StackCalculator::isEmpty()
{
  //TODO: Returns true if the stack is empty, false if not
  if (stackHead == nullptr)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void StackCalculator::push(float number)
{
  //TODO: Push a floating pointer element to the stack
  Operand *push = new Operand;
  Operand *lastElement = stackHead;
  push->number = number;
  if (isEmpty() == true) // the new element is now the stackHead
  {
    push->next = nullptr;
    stackHead = push;
    return;
  }
  else
  {
    Operand *nextElement = stackHead;
    stackHead = push;
    stackHead->next = nextElement;
  }
}

void StackCalculator::pop()
{
  //TODO: delete the element out of the stack, if empty print that the stack is empty.
  if (isEmpty() == true)
  {
    cout << "Stack empty, cannot pop an item." << endl;
    return;
  }
  else if (stackHead->next == nullptr) // the stackHead is the only element in the stack
  {
    delete stackHead;
    stackHead = nullptr;
    return;
  }
  else // delete the stackHead, set the stackHead to stackHead->next
  {
    Operand *oldStackHead = stackHead;
    stackHead = stackHead->next;
    delete oldStackHead;
  }
}

Operand *StackCalculator::peek()
{
  //TODO: returns the top of the stack, if empty print that the stack is empty.
  if (isEmpty() == true) // stack is empty
  {
    cout << "Stack empty, cannot peek." << endl;
    return nullptr;
  }
  return stackHead;
}

bool StackCalculator::evaluate(string *s, int size) // array of string and length of array
{
  /*TODO: 1.scan the array from the end
            2.Use isNumber function to check if the input is an operand
            3.push all operands to the stack
            4.If operator take two element of from the stack,
              compute and put the result back in stack
            5.Handle the boundery cases as required.
            6.Read the writeup for more details
    */

  int numOperators = 0;
  int numOperands = 0;
  float result = 0;
  float numberOne;
  float numberTwo;

  for (int i = size - 1; i > -1; i--)
  {
    if (isNumber(s[i]) == true) // if the element at the index is an operand
    {
      push(stof(s[i]));
      numOperands++;
    }
    else // if the element at the index is an operator
    {
      if (s[i] != "+" && s[i] != "*") // if the operator is not plus or multiply
      {
        cout << "err: invalid operation" << endl;
        return false;
      }

      numOperators++;

      if (isEmpty() == true)
      {
        cout << "err: not enough operands" << endl;
        return false;
      }
      else
      {
        numberOne = stackHead->number;
        pop();
        if (isEmpty() == true)
        {
          cout << "err: not enough operands" << endl;
          return false;
        }
        else
        {
          numberTwo = stackHead->number;
          pop();
          if (s[i] == "+") // if the operator is a plus
          {
            result = (numberOne + numberTwo);
          }
          else // if the operator is a multiply
          {
            result = (numberOne * numberTwo);
          }
          push(result);
        }
      }
    }
  }
  return true;
}