// University of Illinois at Chicago
// Name: Ahmed Yousef
// Project 5: Countdown Math Undone
// Submission Date: 12/6/2024
// Project Description: This project is a math-based puzzle game inspired by the Countdown Game. 
// The main point of this project is the Undo feature, which allows the players to reverse their last move if they made a mistake.


#include <iostream>
#include <string>
#include <sstream>
#include "mersenne-twister.h"
#include "Game.h"
#include <vector>

using namespace std;

// int promptAndGetNumLarge();
// void processCalculation(string userInput, int& num1, char& operation, int& num2);
// bool solveGame(Game& game, vector<string>& solutionSteps);

// Display the greeting and the prompt for choosing big numbers
// Repeats until a valid big number is entered (must be 0-4)
// Returns a valid number of big numbers chosen by the user (0-4)
int promptAndGetNumLarge() {
	int numLarge;

	// Display prompt and get the input
	 cout << endl;
	cout << "Let's play Countdown!" << endl;
	cout << "How many big numbers would you like (0-4)? ";
	cin >> numLarge;


	// Repeat if the input isn't valid (valid is between 0 and 4, inclusive)
	while (numLarge < 0 || numLarge > 4) {
		cout << "That's not a valid number. You must choose between 0 and 4." << endl;
		cout << "How many large numbers would you like? ";
		cin >> numLarge;
	}

	// Return the number chosen
	return numLarge;
}

// Determines the pieces of a calculation from the user input
// Parameters:
// userInput is the string, for example "2+3"
// num1 is passed by reference to return the first number in the calculation (the 2 in the above example)
// operation is passed by reference to return the operation in the calculation ('+' in the above example)
// num2 is passed by reference to return the second number in the calculation (the 3 in the above example)
// Function doesn't return a value, it uses the reference variables to return the information
// Will cause an exception if userInput is anything but a valid operation
void processCalculation(string userInput, int& num1, char& operation, int& num2) {
	// Use a stringstream (essentially turning the given string into a stream)
	stringstream ss(userInput);

	// Input the first number, then the operation, and then the second number from that stream
	ss >> num1 >> operation >> num2;
   if (ss.fail() || (operation != '+' && operation != '-' && operation != '*' && operation != '/')){
	cout <<"Invalid" << endl;
   }

}




// Represents a single state in the undo stack
struct Node{
int numbers[Game::NUMBERS_COUNT];
Node* next;

Node(const int* nums, Node* nxt = nullptr){
	for(int i = 0; i < Game::NUMBERS_COUNT; ++i){
		numbers[i] = nums[i];
		next = nxt;
	}
}
};

// implements the undo functionality
// linked list (stack)
class UndoStack{
private:
Node* top;
// initializes empty stack
public:
UndoStack() : top(nullptr){}
//frees memory
~UndoStack(){
	while(top){
	Node* temp = top;
	top = top->next;
	delete temp;
	}
}
// pushes a new state in the stack
void push(const int* numbers){
	top = new Node(numbers, top);
}
//pops to the last state in the stack
bool pop(int* numbers, const int* currentNumbers){
	if(!top || !top->next){
		return false;
	}
     Node* current = top;
	  Node* previous = nullptr;

	 while(current){
     bool isDifferent = false;
	 for(int i = 0; i < Game::NUMBERS_COUNT; ++i){
		if(current->numbers[i] != currentNumbers[i]){
			isDifferent = true;
			break;
		}
	 }

     if (isDifferent){
		for(int i = 0; i < Game::NUMBERS_COUNT; ++i){
			numbers[i] = current->numbers[i];
	 }

	 while(top != current){
		Node* temp = top;
		top = top->next;
		delete temp;
		 
	 }
          return true;
	 }
     previous = current;
	 current = current->next;

	 }
   
	return false;
}



// bool isEmpty() const{
// return top == nullptr;
// }


}; // end of UndoStack class











 bool solveGame(Game& game, vector<string>& solutionSteps);
int promptAndGetNumLarge();
void processCalculation(string userInput, int& num1, char& operation, int& num2);




int main() {
	// Input a random seed for the program, and call the seed function
	int randSeed;
	cout << "Enter random seed: ";
	cin >> randSeed;
	seed(randSeed);

	// userContinue is used to input whether the user wants to continue to play another game
	string userContinue;
	do {
		// Get the quantity of large numbers
		int numLarge = promptAndGetNumLarge();

		// Create the game variable, using that quantity of large numbers
		Game game(numLarge);
 
      //Undo stack
	      UndoStack undoStack;
		  undoStack.push(game.getNumbers());

		// Clear newline from previous input
		string userInput;
		getline(cin, userInput);

		// Repeat until the game is over
		while (!game.gameOver()) {
			// Display the available numbers and get the user's calculation input
			game.displayNumbers();
			cout << "Enter a calculation (or U to Undo, S to Solve, or Q to Quit): ";
			getline(cin, userInput);
             //test
			 cout << endl;
			// Quit this game if the user choses Q, but don't exit the program (the user might play another game)
			if (userInput == "q" || userInput == "Q") {
				cout << "Exiting this game." << endl;
				break;
			}


			//undo
            if (userInput == "u" || userInput == "U") {
              int tempNumbers[Game:: NUMBERS_COUNT];
			  if(!undoStack.pop(tempNumbers, game.getNumbers())){
				cout << "Cannot undo." << endl;
			  }
			  else{
				game.setNumbers(tempNumbers);
				// cout << "Undo successful." << endl;
			  }
			  continue;
			}
       
         // Solution
		 if(userInput == "S" || userInput == "s"){
			vector<string> solutionSteps;
			if(solveGame(game, solutionSteps)){
				cout << "Solution:" << endl;
				for(const string& step : solutionSteps){
					cout << step << endl;
				}
			}
			else{
				cout << "Unable to find a solution." << endl;
				//test endl
				cout << endl;
			}
			continue;
		 }













			// Get the numbers and operation from the user's input
			int num1;
			char operation;
			int num2;
			processCalculation(userInput, num1, operation, num2);

			// Make sure num1 and num2 are in the list of numbers
			if (!game.removeNumber(num1)) {
				// num1 was not found, display error message
				cout << num1 << " is not a valid number." << endl;
			}
			else if (!game.removeNumber(num2)) {
				// num2 was not found, display error message
				cout << num2 << " is not a valid number." << endl;
				// add num1 back into the list, since it was removed in the previous if condition
				game.addNumber(num1);
			}
			else {
				// num1 and num2 are in our list, perform the operation and display the equation
				int result = game.performOperation(num1, operation, num2);
				cout << num1 << " " << operation << " " << num2 << " = " << result << endl << endl;
               // test by me
                 game.addNumber(result);
				 undoStack.push(game.getNumbers());


			 
				// Add the result to the list of numbers
				 //game.addNumber(result);

				// Display win or lose messages if appropriate
				if (game.wonGame()) {
					cout << "You win!" << endl;
				} else if (game.lostGame()) {
					cout << "You lose." << endl;
				}
			}
		}

		// Ask user if they want to continue, do so if they type Y or y
		cout << endl;
		cout << "Would you like to play again (y/n)? ";
		getline(cin, userContinue);
	} while (userContinue == "y" || userContinue == "Y");
}

// solves the game recursively
bool solveGame(Game& game, vector <string>& solutionsSteps){
	const int* numbers = game.getNumbers();
	for(int i =0; i < Game::NUMBERS_COUNT; ++i){
    for (int j = 0; j < Game::NUMBERS_COUNT; ++j){
		if (i == j || numbers[i] == 0 || numbers[j] == 0){
			continue;
		}
		int tempNumbers[Game::NUMBERS_COUNT];
		for(int k = 0; k < Game:: NUMBERS_COUNT; ++k){
		tempNumbers[k] = numbers[k];
		}
		stringstream step;
		for (char op: {'+', '-', '*','/'}){
			tempNumbers[i] = game.performOperation(numbers[i], op, numbers[j]);
			tempNumbers[j] = 0;

			Game tempGame(tempNumbers, game.getTarget());
			if(tempNumbers[i] == game.getTarget()){
				step << numbers[i] << " " << op << " " << numbers[j] << " = " << tempNumbers[i];
				solutionsSteps.push_back(step.str());
				return true;
			}
			vector<string> subSteps;
			if (solveGame(tempGame, subSteps)){
				step << numbers[i] << " " << op << " " << numbers[j] << " = " << tempNumbers[i];
				solutionsSteps.push_back(step.str());
				solutionsSteps.insert(solutionsSteps.end(), subSteps.begin(), subSteps.end());
				return true;
			}

		}
	}



	}
	return false;
}
