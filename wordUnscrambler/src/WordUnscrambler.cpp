// Assignment 5 for CS 2336.002
// Programmer: Tiffany Do
// Description: Word Unscrambler Program. Reads in a dictionary of words and asks for
// user input of a scrambled word. Outputs the unscrambled word using a BinarySearchTree.
// Also maps to multiple words **EXTRA CREDIT VERSION**

#include <fstream>
#include "BinarySearchTree.h"
#include "Word.h"
int main()
{
	//files to be read
	std::ifstream inFile;
	std::ofstream oFile;
	inFile.open("english_words.txt");
	oFile.open("debug.txt");

	//creates the dictionary to add words to, adds all the words in the file
	BinarySearchTree<Word> dictionary = BinarySearchTree<Word>();
	std::string added;
	while(inFile >> added)
	{
		Word add = Word(added);
		dictionary.insert(add, update);
	}

	//outprints the debug to a separate file
	dictionary.debug(oFile);

	//runs the program and asks for input until the user inputs "0"
	bool run = true;
	std::string input;
	while(run)
	{
		std::cout << "Enter a word to unscramble(Enter 0 to stop) : ";
		std::cin >> input;
		if(input == "0")
		{
			run = false;
			break;
		}
		//makes a new word to be unscrambled
		Word scrambled = Word(input);

		//unscrambles word; finds key
		bool result = dictionary.find(scrambled, unscramble);
		if(!result)
			std::cout << "Word not found. Cannot unscramble." << std::endl;
		std::cout << std::endl;
	}
	return 0;
}


