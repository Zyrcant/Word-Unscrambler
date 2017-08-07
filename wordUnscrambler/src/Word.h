// Assignment 5 for CS 2336.002
// Programmer: Tiffany Do
// Description: Head file for the functions in Word. Words stores a folded key and
// a vector for all the words that map to the key

#include <string>
#include <vector>
#ifndef WORD_H_
#define WORD_H_

class Word
{
private:
	//member data for the key and the vector of words that map to the key
	std::string key;
	std::vector<std::string> words;
public:
	//default constructor, sets key to an empty string
	Word();

	//constructor given a string. Folds the string into lowercase alpha and maps the original string
	//to the string vector
	Word(std::string s);

	//finds the word that that the key maps to. Can map to multiple words.
	//outprints all the words in the vector
	void unscrambles() const;

	//updates the vector to add more words that map to the same key
	void update(const Word &otherWord);

	//overloaded relational operators that compare by key
	bool operator==(const Word &otherWord) const;
	bool operator<(const Word &otherWord) const;
	bool operator>(const Word &otherWord) const;

	//ostream operator that outputs everything in the vector
	friend std::ostream& operator<<(std::ostream &outputStream, const Word &word);
};

#endif /* WORD_H_ */
