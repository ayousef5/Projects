// University of Illinois at Chicago
// Name: Ahmed Yousef
// Project 3:  Countdown Letters
// This project is a word game where players use 9 random letters,
// including 3 to 5 vowels, to form the longest valid word. The program checks the validity 
// of the words, which determines the winner, and allows players to play multiple rounds
#include <iostream>
#include <fstream>
#include "mersenne-twister.h"
#include <vector>
using namespace std;

int chooseRandomNumber(int min, int max) {
	return rand_u32() % (max + 1 - min) + min;
}

string fullSetOfVowels() {
	return 
		string(15, 'A') + 
		string(21, 'E') + 
		string(13, 'I') + 
		string(13, 'O') + 
		string(5, 'U');
}
// function to convert a word to upperCase
string upperCase(string word){
	for (size_t i = 0; i < word.size(); i++){
		word[i] = toupper(word[i]);
	}
	return word;
}

string fullSetOfConsonants() {
	return
		string(2, 'B') +
		string(3, 'C') +
		string(6, 'D') +
		string(2, 'F') +
		string(3, 'G') +
		string(2, 'H') +
		string(1, 'J') +
		string(1, 'K') +
		string(5, 'L') +
		string(4, 'M') +
		string(8, 'N') +
		string(4, 'P') +
		string(1, 'Q') +
		string(9, 'R') +
		string(9, 'S') +
		string(9, 'T') +
		string(1, 'V') +
		string(1, 'W') +
		string(1, 'X') +
		string(1, 'Y') +
		string(1, 'Z');
}

bool isValidNumberOfVowels(int num){
	return num >= 3 && num <= 5;
}
// check if a word in the list
bool checkWord (const vector<string>& wordList, string useWord){
	for (int i = 0; i < wordList.size(); i++ ){
		if (wordList[i] == useWord){
			return true;
		}
	}
	return false;
}
// Function to compare two words and determine the winner
void wordCompare(const string word1, string word2){
	if (word1.length() > word2.length()){
		cout << "Player 1 wins!" << endl;
	}
	else if (word1.length() < word2.length()){
       cout << "Player 2 wins!" << endl;
 	}
	else {
           cout << "Tie game." << endl;
	}
}
// checks if the word is valid
bool isValidWord(const string& word, const string& letters, const vector <string>& wordList)
{
	string  temp = letters;
	for (size_t j = 0; j < word.length(); j++){
		size_t pos = temp.find(word[j]);
		if (pos != std::string::npos){
			temp.replace(pos, 1, "");

		}
		else{
			return false;
		}
	}
	return true;
}
// find the longest woord that can be made from available letters
string findLongestWord(const vector <string>& wordList, const string& availableLetters){
	string longestWord = "";
	for (const string& word : wordList){
	
		if (isValidWord(word, availableLetters, wordList) && word.length() > longestWord.length()){
		longestWord = word;
	}
	}
	return longestWord;

}
// Main Function
int main() {
ifstream fileIn;
fileIn.open("words.txt");
vector <string> wordList;
string word;
char quit; 
// reads words from file and add them to the word list
while (fileIn >> word){
	wordList.push_back(word);
}
fileIn.close();
	int randSeed = 0;
    size_t numVowels = 0;
	string letter, word1, word2;
     cout << "Enter random seed: ";
	 	cin >> randSeed;
	cout << endl;
	seed(randSeed);
    cout << "Let's play Countdown!" << endl;
// Main game Loop
      while(true){
       do{
		cout << "How many vowels would you like (3-5)? " << endl;
        cin>> numVowels;
		if (numVowels < 3 || numVowels > 5){
    cout << "Invalid number of vowels." << endl;
		}
	} 
	while(numVowels < 3 || numVowels > 5);
	// clear previous letters
    letter.clear();
    cout << "The letters are: ";

// get vowel and consonants
	string vowel = fullSetOfVowels();
	string consonants = fullSetOfConsonants();
// Randomly select vowels
for (size_t i = 0; i < numVowels; i++){
	size_t num = chooseRandomNumber(0, vowel.size() - 1);
	char alpha = vowel.at(num);
	letter.append(1, alpha);
	vowel.replace(num, 1, "");
}
// Randomly select consonants
for (size_t j = 0; j < 9 - numVowels; j++){
size_t num1 = chooseRandomNumber(0, consonants.size() - 1);
char alpha1 = consonants.at(num1);
letter.append(1, alpha1);
consonants.replace(num1, 1, "");
}

string sameLetter = letter;

cout << letter << endl;
    cout << "Player 1, enter your word: ";
	cin >> word1;
	word1 = upperCase(word1);
    cout << "Player 2, enter your word: ";
	cin >> word2;
	word2 = upperCase(word2);
	//checks if both words are valid
	bool valid1 = isValidWord(word1, letter, wordList) && checkWord(wordList, word1);
	bool valid2 = isValidWord(word2, letter, wordList) && checkWord(wordList, word2);

	// compare words and determine the outcome of the game
 if (valid1 && valid2){
	wordCompare(word1, word2);
 }
 else if (!valid1 && valid2){
    cout << "Player 1's word is not valid." << endl;
	cout << "Player 2 wins!" << endl;
 }
 else if (!valid1 && !valid2){
	cout << "Player 1's word is not valid." << endl;
	cout << "Player 2's word is not valid." << endl;
	cout << "Tie game." << endl;
 }
 else if (valid1 && !valid2){
	cout << "Player 2's word is not valid." << endl;
	cout << "Player 1 wins!" << endl;
 }
cout << "The longest possible word is: ";
string longestWord = findLongestWord(wordList, sameLetter);
cout << longestWord << endl;
  cout << "Do you want to play again (y/n)? ";
  cin >> quit;
  if (quit == 'n'){
	break;
  }

	  } 
return 0;
}
