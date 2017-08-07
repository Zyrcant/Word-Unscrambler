/*
 * test.cpp
 *
 *  Created on: Nov 25, 2016
 *      Author: Tiffany
 */

#include "BinarySearchTree.h"
#include "Word.h"
/*int main()
{
	/*BinarySearchTree<int> tree = BinarySearchTree<int>();
	tree.insert(19);
	tree.insert(5);
	tree.insert(6);
	tree.insert(4);
	tree.insert(21);
	tree.insert(25);
	tree.insert(3);
	tree.print();
	tree.debug(std::cout);
	tree.erase(5);
	tree.erase(11);
	tree.debug(std::cout);
	std::cout << "make a copy of the tree" << std::endl;
	{
		auto list2(tree);
		std::cout << "Original tree" << std::endl;
		tree.debug(std::cout);
		std::cout << "Copy of tree" << std::endl;
		list2.debug(std::cout);
	}

	BinarySearchTree<Word> tree = BinarySearchTree<Word>();

	Word add = Word("dinosaur");
	Word add2 = Word("apples");
	Word add3 = Word("dice");
	Word add4 = Word("cide");
	tree.insert(add, &update);
	tree.insert(add2, &update);
	tree.insert(add3, &update);
	tree.insert(add4, &update);
	Word uns = Word("omannic");
	Word uns2 = Word("edic");
	tree.debug(std::cout);
	tree.print();

	std::cout << "UNSCRAMBLING" << "\n";
	bool result = tree.find(uns, &unscramble);
	bool result2 = tree.find(uns2, &unscramble);
	return 0;
}/*


