// Assignment 5 for CS 2336.002
// Programmer: Tiffany Do
// Description: Header file for the functions in BinarySearchTree. Creates a BinarySearchTree
// where the larger items are the right link and the smaller items are the left link

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

// forward declaration of the template class BinarySearchTree
template<class DataType>
class BinarySearchTree;

// TreeNode
template <class DataType>
class TreeNode
{
	friend class BinarySearchTree<DataType>;
//member data to hold the left link, right link, and info
private:
	DataType info;
	TreeNode<DataType> *lLink;
	TreeNode<DataType> *rLink;
public:
	//default constructor, sets links to null
	TreeNode();
	//standalone friend function to display debug data
	template<typename t>
	friend void displayDebug(const TreeNode<t> *item, std::ostream &out);
	//standalone friend function that updates the vector of mapped words in Word
	template<typename t>
	friend void update(t &existingItem, const t &newItem);
};

//default constructor of TreeNode, sets links to null
template<class DataType>
TreeNode<DataType>::TreeNode()
{
	lLink = nullptr;
	rLink = nullptr;
}

//standalone helper function that prints the word
template<typename DataType>
void display(const DataType &item)
{
	std::cout << item << std::endl;
}

//standalone helper function to print debugging, friend function of TreeNode to access private members
template<typename t>
void displayDebug(const TreeNode<t> *item, std::ostream &out)
{
	const unsigned int ADDRWIDTH = 10;
	out << "node " << std::setw(2);
	out << "=" << std::setw(ADDRWIDTH) << item;
	out << ", leftLink=" << std::setw(ADDRWIDTH)
		<< item->lLink;
	out << ", rightlink=" << std::setw(ADDRWIDTH)
		<< item->rLink;
	out << ", value=" << item->info << std::endl;
}

// BinarySearchTree class
template <class DataType>
class BinarySearchTree
{
private:
	//member data contains the root node and the size of the tree
	TreeNode<DataType> *root;
	int numberNodes;
public:
	//default constructor, root is null and the size is 0
	BinarySearchTree()
	{
		numberNodes = 0;
		root = nullptr;
	}
	//copy constructor
	BinarySearchTree(const BinarySearchTree &otherItem);
	//destructor
	~BinarySearchTree();
	//returns true if empty
	bool empty() const
	{
		return (root == nullptr);
	}
	//returns the size
	std::size_t size() const
	{
		return numberNodes;
	}
	//prints the Tree in order of key
	void print() const;
	//debugging purposes, shows left and right pointers
	void debug(std::ostream &out) const;
	//returns true if the item is found and calls foundNode
	bool find(const DataType &searchItem, void (*foundNode)(const DataType&));
	//erases a Node by item
	bool erase(const DataType &deleteItem);
	//inserts a new Node into the Tree, replaces anything with the same key
	void insert(const DataType &newItem);
	//inserts a new Node into the Tree, updates an item if it has the same key
	void insert(const DataType &newItem, void (*duplicateItemFound)(DataType &existingItem, const DataType &newItem));
	//traverses the Tree inorder and calls the foundItem on every Node
	void traverse(void (*itemFound)(const DataType& foundItem)) const;

	//extra helper functions

	//recursive functions to traverse the tree and performs actions based on passed function
		//overloaded to provide support for ostream as well
	void inorder(TreeNode<DataType> *p, void (*visit)(const DataType &item)) const;
	void inorder(TreeNode<DataType> *p, std::ostream &out, void (*visit)(const TreeNode<DataType> *item, std::ostream &out)) const;
	//deletes a given Node from the tree
	bool deleteNode(TreeNode<DataType>* &p);
	//copies a Node
	void copyTree(TreeNode<DataType>* &copied, TreeNode<DataType>* otherRoot);
	//destroys all subtrees from given Node
	void destroyFromNode(TreeNode<DataType>* &p);
}
;

///////////////////// EXTRA HELPER FUNCTIONS ///////////////////////////////////////////////////////


//class helper function to recursively iterate through the tree inorder
template<class DataType>
void BinarySearchTree<DataType>::inorder(TreeNode<DataType> *p, void (*visit)(const DataType &item)) const
{
	//if p is not null, recursively iterates through left subtree, calls visit
	//continues with the process through right subtree
	if(p != nullptr)
	{
		inorder(p->lLink, *visit);
		(*visit)(p->info);
		inorder(p->rLink, *visit);
	}
}

//class helper function to recursively iterate through the tree inorder
//overloaded to pass in an ostream and TreeNode instead of a DataType, used in debug function
template<class DataType>
void BinarySearchTree<DataType>::inorder(TreeNode<DataType> *p, std::ostream &out, void (*visit)(const TreeNode<DataType> *item, std::ostream &out)) const
{
	//if p is not null, recursively iterates through left subtree, calls visit and passes ostream and the node pointer
	//continues with the process through right subtree
		//used for debug to output to a file and also to output the pointer value
	if(p != nullptr)
	{
		inorder(p->lLink, out, *visit);
		(*visit)(p, out);
		inorder(p->rLink, out, *visit);
	}
}

//helper function to delete a given node
template<class DataType>
bool BinarySearchTree<DataType>::deleteNode(TreeNode<DataType>* &p)
{
	//node to traverse through the tree
	TreeNode<DataType> *current;
	//node that is before the one traversing the tree
	TreeNode<DataType> *beforeCurrent;
	//node to be deleted
	TreeNode<DataType> *temp;

	//the given node does not exist, throws an error
	if(p == nullptr)
	{
		std::cout << "ERROR: Cannot delete a node that does not exist.";
		return false;
	}
	//the given node is a leaf; has no children
	else if(p->lLink == nullptr && p->rLink == nullptr)
	{
		//sets the temp variable to the given node
		temp = p;
		p = nullptr; //sets the given variable to a nullptr, the parent node will now point to null
		delete temp; //deletes the temporary variable
	}
	//given node only has a child on the right link
	else if(p->lLink == nullptr)
	{
		//sets temp variable to the given node
		temp = p;
		//advances the given node pointer to the right branch
		p = p->rLink;
		//deletes temp
		delete temp;
	}
	//given node only has a child on the left link
	else if(p->rLink == nullptr)
	{
		//sets temp variable to the given node
		temp = p;
		//advances the given node pointer to the right branch
		p = p->lLink;
		//deletes temp
		delete temp;
	}
	//given node has both and left and right subtree
	else
	{
		//current goes to its left link
		current = p->lLink;
		//node to keep track of the node before current
		beforeCurrent = nullptr;
		//keeps going down the left subtree until it reaches a node that does not have a right child
		while(current->rLink != nullptr)
		{
			beforeCurrent = current;
			current = current->rLink;
		}
		//changes the info of p to the current
		p->info = current->info;
		//if current did not move, then the left link of p is the left link
		if(beforeCurrent == nullptr)
		{
			p->lLink = current->lLink;
		}
		//current did move
		else
		{
			//changes the right subtree of the node before the one to be deleted to the left subtree
			beforeCurrent->rLink = current->lLink;
		}
		delete current;
	}
	numberNodes--;
	return true;
}

//copies the tree from the second node given
template<class DataType>
void BinarySearchTree<DataType>::copyTree(TreeNode<DataType>* &copy, TreeNode<DataType>* otherNode)
{
	//node to be copied is null, so the copy is null
	if(otherNode == nullptr)
	{
		copy = nullptr;
	}
	else
	{
		//allocates a new Node to the copy
		copy = new TreeNode<DataType>();
		//copies the info
		copy->info = otherNode->info;
		//copies the left subtree recursively
		copyTree(copy->lLink, otherNode->lLink);
		//copies the right subtree recursively
		copyTree(copy->rLink, otherNode->rLink);
	}
}

//destroys the subtrees from the given node
template<class DataType>
void BinarySearchTree<DataType>::destroyFromNode(TreeNode<DataType>* &p)
{
	//if the node exists
	if(p != nullptr)
	{
		//recursively deletes the left and right subtrees by going down them until the node is null
		destroyFromNode(p->lLink);
		destroyFromNode(p->rLink);
		//deletes p when the left and right link are null
		delete p;
	}
}

//calls the unscramble function of the item
template<typename t>
void unscramble(const t &item)
{
	item.unscrambles();
}

//calls the update function of the item
template<typename t>
void update(t &existingItem, const t &newItem)
{
	existingItem.update(newItem);
}

///////////////////// ASSIGNED CLASS FUNCTIONS ///////////////////////////////////////////////////////

//copy constructor
template<class DataType>
BinarySearchTree<DataType>::BinarySearchTree(const BinarySearchTree &otherItem)
{
	//other tree is empty
	if(otherItem.root == nullptr)
	{
		//root is null and size is 0
		root = nullptr;
		numberNodes = 0;
	}
	//calls copyTree from the roots
	else
	{
		copyTree(root, otherItem.root);
		numberNodes = otherItem.numberNodes;
	}
}

//calls destroyFromNode to destroy from the root
template<class DataType>
BinarySearchTree<DataType>::~BinarySearchTree()
{
	destroyFromNode(root);
}

//passes display to traverse to print all nodes inorder
template<class DataType>
void BinarySearchTree<DataType>::print() const
{
	traverse(display);
}

//displays debug information to the ostream; left and right link pointers are shown
template<class DataType>
void BinarySearchTree<DataType>::debug(std::ostream &out) const
{
	//only displays if the root is not null; the tree exists
	if(root!= nullptr)
	{
		//formatting for the width
		const unsigned int ADDRWIDTH = 10;
		out << "START DEBUG" << std::endl;
		out << "Root  =" << std::setw(ADDRWIDTH) << root << " value : " << root->info;
		out << ", # nodes=" << size() << std::endl;
		//calls debug to display the debug inorder from the root
		inorder(root, out, displayDebug);
	}
	else
		std::cout << "Cannot display debug for empty tree.";
	out << "END DEBUG" << std::endl;
}

//returns true if the searchItem is in the tree and calls the foundNode function
template<class DataType>
bool BinarySearchTree<DataType>::find(const DataType &searchItem, void (*foundNode)(const DataType &item))
{
	//if the tree is empty, displays an error and returns false
	if(root == nullptr)
	{
		std::cout << "Cannot search empty tree.";
		return false;
	}
	//creates a Node pointer to traverse the tree
	TreeNode<DataType> *current;
	current = root;
	//while the current node is on a node that exists
	while(current != nullptr)
	{
		//if the item is bigger than the current, then goes to the right link
		if(searchItem > current->info)
			current = current->rLink;
		else if (searchItem < current->info) //searchItem is smaller, so goes to the left
			current= current->lLink;
		else if (searchItem == current->info) //the item is the same as the current node
		{
			//calls foundNode on the searchItem
			(*foundNode)(current->info);
			return true;
		}
	}
	return false;
}

//deletes the node that contains the deleteItem as the info
template<class DataType>
bool  BinarySearchTree<DataType>::erase(const DataType &deleteItem)
{
	//creates a node pointer to traverse the tree
	TreeNode<DataType> *current;
	//bool to keep track if the node is found in the tree
	bool found = false;
	//if the root is null, tree is empty
	if(root == nullptr)
		std::cout << "ERROR: Cannot delete from an empty tree" << std::endl;
	else //tree is not empty
	{
		//sets current to the root
		current = root;
		//while the current is not null and while the item to be deleted is not founds
		while(current != nullptr && !found)
		{
			//the item is current, set found to true
			if(current->info == deleteItem)
			{
				found = true;
			}
			else //current is not the node
			{
				//current is bigger than the item, go to the left
				if(current->info > deleteItem)
					current = current->lLink;
				else //current is smaller, go to the right
					current = current->rLink;
			}
		}
		if(current == nullptr) //could not find the item, has reached nullptr
		{
			std::cout << "The item is not in the tree. Cannot remove.";
			return false;
		}
		else if(found) //the item has been found in the tree
		{
			if(current == root) //the item to be deleted is the root
				return deleteNode(root);
			return deleteNode(current); //deletes the current
		}
		else //if the current is not null and the item is not found, some error has occurred
			std::cout << "The item is not in the tree. Cannot remove.";
	}
	return false;
}

//inserts an item into the binary search tree
template<class DataType>
void BinarySearchTree<DataType>::insert(const DataType &newItem)
{
	//node to traverse the tree
	TreeNode<DataType> *current;
	//new Node to hold the item
	TreeNode<DataType> *newNode;
	//a node to store the node before the current one
	TreeNode<DataType> *beforeCurrent;
	//creates a new TreeNode for the item, assigns it it the newItem
	newNode = new TreeNode<DataType>;
	newNode->info = newItem;
	//links are null
	newNode->lLink = nullptr;
	newNode->rLink = nullptr;

	//tree is empty, so insert at root
	if(root == nullptr)
	{
		root = newNode;
		numberNodes++;
	}
	else //inserting at non-root position
	{
		current = root;
		while(current != nullptr)
		{
			//finds the spot to insert, goes down left or right links accordingly until null
			beforeCurrent = current; //stores the current node to prepare for iterating to the next node
			if(current->info == newItem)
			{
				//std::cout << "DUPLICATE ITEM : Replacing duplicate" << std::endl;
				current->info = newItem;
				numberNodes++;
				return;
			}
			else if (current->info > newItem)
			{
				current = current->lLink;
			}
			else
			{
				current = current->rLink;
			}
		}
		if(beforeCurrent->info > newItem)
			beforeCurrent->lLink = newNode;
		else
			beforeCurrent->rLink = newNode;
		numberNodes++;
	}
}

//inserts a new item into the binary search tree, also calls the duplicateItemFound
//duplicateItemFound is used as an update function where the new item and existing item are given
template<class DataType>
void BinarySearchTree<DataType>::insert(const DataType &newItem, void (*duplicateItemFound)(DataType &existingItem, const DataType &newItem))
{
	//node to traverse the tree, add to the tree, and a trailing node
	TreeNode<DataType> *current;
	TreeNode<DataType> *newNode;
	TreeNode<DataType> *beforeCurrent;
	newNode = new TreeNode<DataType>;
	newNode->info = newItem;
	newNode->lLink = nullptr;

	//the root is null, inserts new item as the root
	if(root == nullptr)
	{
		root = newNode;
		numberNodes++;
	}
	else //tree is not empty
	{
		current = root;
		//finds the correct spot to insert the item
		while(current != nullptr)
		{
			beforeCurrent = current; //stores the current node to prepare for iterating to the next node
			if(current->info == newItem)
			{
				//std::cout << "DUPLICATE KEY : Updating duplicate" << std::endl;
				(*duplicateItemFound)(current->info, newItem);
				return;
			}
			else if (current->info > newItem)
			{
				current = current->lLink;
			}
			else
			{
				current = current->rLink;
			}
		}
		if(beforeCurrent->info > newItem)
			beforeCurrent->lLink = newNode;
		else
			beforeCurrent->rLink = newNode;
		numberNodes++;
		}
}

//traverses the tree inorder using the inorder method
//calls the itemFound function on every element
template<class DataType>
void BinarySearchTree<DataType>::traverse(void (*itemFound)(const DataType &foundItem)) const
{
	inorder(root, *itemFound);
}


#endif /* BINARYSEARCHTREE_H_ */
