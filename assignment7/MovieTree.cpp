#include <iostream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;

LLMovieNode *getLLMovieNode(int r, std::string t, int y, float q)
{
	LLMovieNode *lmn = new LLMovieNode();
	lmn->ranking = r;
	lmn->title = t;
	lmn->year = y;
	lmn->rating = q;
	lmn->next = NULL;
	return lmn;
}
/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}
/* ------------------------------------------------------ */
void inorderTraversalHelper(TreeNode *root)
{
	if (root == NULL)
	{
		return;
	}
	inorderTraversalHelper(root->leftChild);
	cout << root->titleChar << " ";
	inorderTraversalHelper(root->rightChild);
}

void MovieTree::inorderTraversal()
{
	inorderTraversalHelper(root);
	cout << endl;
}
/* ------------------------------------------------------ */
void showMovieCollectionHelper(TreeNode *root)
{
	if (root == NULL)
	{
		return;
	}
	showMovieCollectionHelper(root->leftChild);
	if (root->head == nullptr)
	{
		// do nothing
	}
	else
	{
		cout << "Movies starting with letter: " << root->titleChar << endl;
		LLMovieNode *pointer = root->head;
		while (pointer != nullptr)
		{
			cout << " >> " << pointer->title << " " << pointer->rating << endl;
			if (pointer->next == nullptr)
			{
				break;
			}
			pointer = pointer->next;
		}
	}
	showMovieCollectionHelper(root->rightChild);
}

void MovieTree::showMovieCollection()
{
	showMovieCollectionHelper(root);
}
/* ------------------------------------------------------ */
TreeNode *searchCharHelper(TreeNode *curr, char key)
{
	if (curr == NULL)
		return curr;
	else if (curr->titleChar == key)
		return curr;
	else if (curr->titleChar > key)
		return searchCharHelper(curr->leftChild, key);
	else
		return searchCharHelper(curr->rightChild, key);
}

TreeNode *MovieTree::searchCharNode(char key)
{
	return searchCharHelper(root, key);
}

void insertTreeNode(TreeNode *&root, char newNodeChar, LLMovieNode *&newNode) // creates a new node in the BST
{
	// pass by reference or return something
	TreeNode *newTreeNode = new TreeNode; // instantiating a new node of TreeNode type on the heap
	newTreeNode->titleChar = newNodeChar;
	if (root == nullptr) // if the BST is empty
	{
		newTreeNode->parent = nullptr;
		newTreeNode->leftChild = nullptr;
		newTreeNode->rightChild = nullptr;
		newTreeNode->head = newNode;
		root = newTreeNode;
		return;
	}
	else
	{
		TreeNode *pointer = root;
		while (pointer != nullptr) // traverses the BST and places the newNode in its rightful spot
		{
			if (newNodeChar > pointer->titleChar) // if the char is larger than the current node, traverse to the right
			{
				if (pointer->rightChild == nullptr)
				{
					pointer->rightChild = newTreeNode;
					newTreeNode->parent = pointer;
					newTreeNode->rightChild = nullptr;
					newTreeNode->leftChild = nullptr;
					newTreeNode->head = newNode;
					return;
				}
				pointer = pointer->rightChild;
			}
			else if (newNodeChar < pointer->titleChar) // if the char is smaller than the current node, traverse to the left
			{
				if (pointer->leftChild == nullptr)
				{
					pointer->leftChild = newTreeNode;
					newTreeNode->parent = pointer;
					newTreeNode->rightChild = nullptr;
					newTreeNode->leftChild = nullptr;
					newTreeNode->head = newNode;
					return;
				}
				pointer = pointer->leftChild;
			}
		}
	}
}

void MovieTree::insertMovie(int ranking, string title, int year, float rating)
{
	LLMovieNode * newNode = getLLMovieNode(ranking, title, year, rating);
	char newNodeChar = title[0];
	TreeNode *pointer = searchCharNode(newNodeChar);
	if (pointer == nullptr) // if the tree node does not exist for the given char, create a new node in the BST and insert the new LLMovieNode as its head
	{
		insertTreeNode(root, newNodeChar, newNode);
		return;
	}
	else
	{
		// CASES:
		// 1. newNode->title is greater than the head
		// 2. newNode->title is less than all elements
		// 3. newNode->title is somewhere in the middle
		LLMovieNode *compare = pointer->head;
		if (newNode->title < compare->title) // CASE 1
		{
			LLMovieNode *temp = compare; // temp is initialized to the head
			pointer->head = newNode;	 // head is assigned to newNode
			newNode->next = temp;		 // the next element is assigned to the old head
			return;
		}
		else
		{
			while (compare != nullptr)
			{
				if (compare->next == nullptr) // CASE 2
				{
					compare->next = newNode; // the new last element is assigned to the newNode
					newNode->next = nullptr; // the newNode->next points to a nullptr
					break;
				}
				else
				{
					if (newNode->title > compare->title && newNode->title < compare->next->title)
					{
						LLMovieNode *temp = compare->next;
						compare->next = newNode;
						newNode->next = temp;
						break;
					}
				}
				compare = compare->next;
			}
		}
	}
}

void MovieTree::removeMovieRecord(string title)
{
	TreeNode *charNode = searchCharNode(title[0]); // initialized to the corresponding treenode
	if (charNode == nullptr)
	{
		cout << "Movie not found." << endl;
		return;
	}
	LLMovieNode *findNode = charNode->head; // initialized to the head of the linked list
	if (findNode == nullptr)				// if there are no elements in the linked list
	{
		cout << "Movie not found." << endl;
		return;
	}
	else if (findNode->next == nullptr) // if there is only one element in the linked list
	{
		if (findNode->title == title)
		{
			delete findNode;
			findNode = nullptr;
			charNode->head = nullptr;
		}
		else
		{
			cout << "Movie not found." << endl;
		}
		return;
	}
	else // there are more elements in the linked list
	{
		LLMovieNode *prev = nullptr;
		LLMovieNode *pres = findNode; // head of the LL

		if (prev == nullptr && pres->title == title) // if the head is the title to be deleted (pres)
		{
			LLMovieNode *temp = pres;
			charNode->head = pres->next;
			delete temp;
			temp = nullptr;
			return;
		}
		else
		{
			while (pres != nullptr && pres->title != title)
			{
				prev = pres;
				pres = pres->next;
			}
			if (pres == nullptr) // the title was not found in the linked list
			{
				cout << "Movie not found." << endl;
				return;
			}
			prev->next = pres->next;
			delete pres;
		}
	}
}

void MovieTree::leftRotation(TreeNode *curr)
{
	TreeNode *parentOfCurr = curr->parent;					// xp in the example
	TreeNode *rightSubtreeOfCurr = curr->rightChild;		// y in the example
	// add boundary cases if parentOfCurr = nullptr or rightSubtreeOfCurr = nullptr
	if (curr == root) // if the root is null
	{
		root = rightSubtreeOfCurr;
		curr->rightChild = rightSubtreeOfCurr->leftChild;
		rightSubtreeOfCurr->leftChild = curr;
		rightSubtreeOfCurr->parent = curr->parent;
		curr->parent = rightSubtreeOfCurr;
		//rightSubtreeOfCurr->leftChild->parent = curr;
	}
	else if (!curr->rightChild) // if the right child of curr is null
	{
		return;
	}
	else
	{
		if (curr->parent->rightChild == curr) // rightSubtreeOfCurr on right side of parent
		{
			curr->parent->rightChild = rightSubtreeOfCurr;
		}
		else
		{
			curr->parent->leftChild = rightSubtreeOfCurr;
		}
		curr->rightChild = rightSubtreeOfCurr->leftChild;		   // right child of x set to yl
		rightSubtreeOfCurr->parent = parentOfCurr; // parent of y set to xp
		curr->parent = rightSubtreeOfCurr;		   // parent of x set to y
		rightSubtreeOfCurr->leftChild = curr;	   // left child of y set to x
	}
}

void destructorHelper(TreeNode * node)
{
	if (node->rightChild != nullptr) destructorHelper(node->rightChild);
	if (node->leftChild != nullptr) destructorHelper(node->leftChild);
	LLMovieNode * pres = node->head;
	while (pres != nullptr)
	{
		LLMovieNode * deletePointer = pres;
		pres = pres->next;
		delete deletePointer;
	}
	delete node;
}

MovieTree::~MovieTree()
{
	if(root) destructorHelper(root);
}