// Assignment 5 for CS 2336.002
// Programmer: Tiffany Do
// Description: Implementation file for the functions in Word. Words stores a folded key and
// a vector for all the words that map to the key

#include "Word.h"
#include <algorithm>
#include <iostream>

//default constructor, sets key to an empty string
Word::Word()
{
	key = "";
}

//constructor given a string. Folds the string into lowercase alpha and maps the original string
//to the string vector
Word::Word(std::string s)
{
	//creates a temporary string to hold the word
	std::string temp = s;
	//transforms the word to lowercase
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	//pushes the original word to the vector
	words.push_back(s);
	//folds the temporary string by alpha
	std::sort(temp.begin(), temp.end());
	key = temp;
}

//finds the word that that the key maps to. Can map to multiple words.
//outprints all the words in the vector
void Word::unscrambles() const
{
	int size = words.size();
	std::cout << "The scrambled word maps to : ";
	for(int i = 0; i < size; i++)
	{
		std::cout << words[i] << " ";
	}
	std::cout << "\n\n";
}

//updates the vector to add more words that map to the same key
void Word::update(const Word &otherWord)
{
	//makes sure that it is not adding the exact same word

	//if the word to be added to the vector is not already in the vector
	if(std::find(words.begin(), words.end(), otherWord.words[0]) == words.end())
		words.push_back(otherWord.words[0]); //adds the word
}

//overloaded relational operators that compare by key
bool Word::operator==(const Word &otherWord) const
{
	return key == otherWord.key;
}

bool Word::operator<(const Word &otherWord) const
{
	return key < otherWord.key;
}

bool Word::operator>(const Word &otherWord) const
{
	return key > otherWord.key;
}

//outstream operator for debugging or future purposes
std::ostream& operator<<(std::ostream &outputStream, const Word &word)
{
	int size = word.words.size();
	for(int i = 0; i < size; i++)
	{
		outputStream << word.words[i] << " ";
	}
	outputStream << std::endl;
	//outputStream << word.key;
	return outputStream;
}
