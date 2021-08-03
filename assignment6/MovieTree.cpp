#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Helper function: Create new node using provided args
MovieNode *getMovieNode(int rank, string t, int y, float r)
{
  MovieNode *nn = new MovieNode;
  nn->title = t;
  nn->ranking = rank;
  nn->year = y;
  nn->rating = r;
  return nn;
}

MovieTree::MovieTree()
{
  root = nullptr;
}

void destructorHelper(MovieNode * node)
{
  if (node == nullptr)
  {
    return;
  }
  destructorHelper(node->left);
  destructorHelper(node->right);
  delete node;
}

MovieTree::~MovieTree() // postorder traversal to successfully delete all elements
{
  destructorHelper(root);
}

void printMovieInventoryHelper(MovieNode *node) // root is inserted into the helper
{
  if (node == nullptr)
  {
    return;
  }
  if (node->left != nullptr)
  {
    printMovieInventoryHelper(node->left);
  }

  cout << "Movie: " << node->title << " (" << node->rating << ")" << endl;

  if (node->right != nullptr)
  {
    printMovieInventoryHelper(node->right);
  }
}

void MovieTree::printMovieInventory()
{
  if (root == nullptr) // if the tree is empty
  {
    cout << "Tree is Empty. Cannot print." << endl;
    return;
  }
  printMovieInventoryHelper(root);
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating)
{
  MovieNode *pointer = root;
  MovieNode *newNode = new MovieNode; // declaring a new node on the heap and filling it with the input
  newNode->ranking = ranking;
  newNode->title = title;
  newNode->year = year;
  newNode->rating = rating;

  if (root == nullptr) // if the BST is empty, make the new node the root
  {
    root = newNode;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return;
  }

  while (pointer != nullptr) // traverses the BST and places the newNode in its rightful spot
  {
    if (newNode->title > pointer->title)
    {
      if (pointer->right == nullptr)
      {
        pointer->right = newNode;
        return;
      }
      pointer = pointer->right;
    }
    else if (newNode->title < pointer->title)
    {
      if (pointer->left == nullptr)
      {
        pointer->left = newNode;
        return;
      }
      pointer = pointer->left;
    }
  }
}

void MovieTree::findMovie(string title)
{
  if (root == nullptr) // in the case that the BST is empty
  {
    cout << "Movie not found." << endl;
    return;
  }

  MovieNode *pointer = root;
  while (pointer != nullptr) // traversing the BST to find the spot where the inserted title should be
  {
    if (pointer->title == title) // if the title is found
    {
      cout << "Movie Info:" << endl
           << "==================" << endl
           << "Ranking:" << pointer->ranking << endl
           << "Title  :" << pointer->title << endl
           << "Year   :" << pointer->year << endl
           << "Rating :" << pointer->rating << endl;
      return;
    }
    else // if the title is not found yet, traverse to the node where it should be
    {
      if (pointer->title > title)
      {
        if (pointer->left == nullptr)
        {
          cout << "Movie not found." << endl;
          return;
        }
        pointer = pointer->left;
      }
      else if (pointer->title < title)
      {
        if (pointer->right == nullptr)
        {
          cout << "Movie not found." << endl;
          return;
        }
        pointer = pointer->right;
      }
    }
  }
}

void preOrderTraversal(MovieNode *node, float rating, int year) // root is inserted into the function
{
  if (node == nullptr)
  {
    return;
  }
  if (node->rating >= rating && node->year > year)
  {
    cout << node->title << " (" << node->year << ") " << node->rating << endl;
  }
  preOrderTraversal(node->left, rating, year);
  preOrderTraversal(node->right, rating, year);
}

void MovieTree::queryMovies(float rating, int year)
{
  if (root == nullptr) // if the BST is empty
  {
    cout << "Tree is Empty. Cannot query Movies." << endl;
    return;
  }
  MovieNode *pointer = root;
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  preOrderTraversal(pointer, rating, year);
}

float findAvgNodes(MovieNode *node) // root is inserted into the function
{
  if (node == nullptr)
  {
    return 0;
  }
  return (1 + findAvgNodes(node->right) + findAvgNodes(node->left));
}

float findAvgFloat(MovieNode *node) // root is inserted into the function
{
  if (node == nullptr)
  {
    return 0;
  }
  return (node->rating + findAvgFloat(node->right) + findAvgFloat(node->left));
}

void MovieTree::averageRating()
{
  if (root == nullptr)
  {
    cout << "Average rating:0.0" << endl;
    return;
  }
  MovieNode *pointer = root;
  float totalSum = findAvgFloat(pointer);
  float totalNodes = findAvgNodes(pointer);
  float avgRating = (totalSum / totalNodes);
  cout << "Average rating:" << avgRating << endl;
}

void printDistanceNodes(MovieNode * node, int level)
{
  if (node == nullptr)
  {
    return;
  }
  if (level == 0)
  {
    cout << "Movie: " << node->title << " (" << node->rating << ") " << endl;
    return;
  }
  printDistanceNodes(node->left, level - 1);
  printDistanceNodes(node->right, level - 1);
}

void MovieTree::printLevelNodes(int level)
{
  if (root == nullptr)
  {
    return;
  }
  MovieNode * pointer = root;
  printDistanceNodes(pointer, level);
}