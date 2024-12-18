// University of Illinois at Chicago
// Name: Ahmed Yousef
// Project 2: Countdown Math
// Project Description: This project involes creating a countdown math 
// game where players use randomely selected numbers to reach a target through calculations.


#include <iostream>
#include "mersenne-twister.h"

using namespace std;
// Global variables for numbers and target
int num1, num2, num3, num4, num5, num6;
int target;
// function to choose a random number within a specific range
int chooseRandomNumber(int min, int max) {
return rand_u32() % (max + 1 - min) + min;
}

// Function to display nonZero Numbers
void displayNumbers(){
if (num1 != 0){
  cout << num1 << " ";
}
 if (num2 != 0){
cout << num2 << " ";
}
 if (num3 != 0){
cout << num3 << " ";
}
if (num4 != 0){
cout << num4 << " ";
}
if (num5 != 0){
cout << num5 << " ";
}
if (num6 != 0){
cout << num6 << " ";
}
cout << endl;
}

// Function to store the result in the first empty number slot
void addResult  (int result){
  if (num1 == 0){
    num1 = result;
  }
  else if (num2 == 0){
    num2 = result;
  }
  else if (num3 == 0){
    num3 = result;
  }
  else if (num4 == 0){
    num4 = result;
  }
  else if (num5 == 0){
    num5 = result;
  }
  else if (num6 == 0){
    num6 = result;
  }
}


// Function to remove a number by setting it to zero
void removeNumber (int num){
  if (num1 == num){
    num1 = 0;
  }
  else if (num2 == num){
    num2 = 0;
  }
  else if (num3 == num){
    num3 = 0;
  }
  else if (num4 == num){
    num4 = 0;
  }
  else if (num5 == num){
    num5 = 0;
  }
  else if (num6 == num){
    num6 = 0;
  }
}

// Function to perform a calculation with two numbers and an operator
void doCalculation( int a, char oper, int b){
  int result = 0;
  switch(oper){
    case '+': result = a + b;
    break;
     case '-': result = a - b;
    break;
     case '/': result = a / b;
    break;
     case '*': result = a * b;
    break;
  }

  // Display Calculation result
  cout << a << " " << oper << " " << b << " = " << result << endl << endl;
  removeNumber(a);
  removeNumber(b);
  addResult(result);
  int countNoZero1 = (num1 != 0) + (num2 != 0) + (num3 != 0) + (num4 != 0) + (num5 != 0) + (num6 != 0);
  if (countNoZero1 == 1){
     cout << endl;
  }
  else if ((result != target) && (result != 0)){
    cout << "Your numbers are: ";
    displayNumbers();
    cout << "The target is: " << target << endl;
  }
}

// boolean to check for a winner or a loser
bool checkForWin() {
  if (num1 == target || num2 == target  || num3 == target  || num4 == target  || num5 == target  || num6 == target){
        cout << "You win!" << endl;
    return true;
  }
  int result;
  int countNoZero = (num1 != 0) + (num2 != 0) + (num3 != 0) + (num4 != 0) + (num5 != 0) + (num6 != 0);
if (( countNoZero == 1 && target != num1 && target != num2 && target != num3 && target != num4 && target != num5 && target != num6) || (result == 0)){
  cout << "You lose." << endl;
  return true;
}
return false;
}





int main() 
{
    int randSeed = 0;
    cout << "Enter random seed: " << endl;
    cin >> randSeed;
    seed(randSeed);
    
    cout << "Let's play Countdown!" << endl;
    int bigNumbers;
    cout << "How many big numbers would you like (0-4)? " << endl;
    cin >> bigNumbers;
    cout << endl;
 
    //generate big numebrs
    for(int i = 0; i < bigNumbers; i++){
    int number = chooseRandomNumber(1, 4) * 25;
    if (i == 0){
     num1 = number;
    }
    else if (i == 1){
      num2 = number;
    }
     else if (i == 2){
      num3 = number;
    }
    else if (i == 3){
      num4 = number;
    }
    }
    
    // generate little numbers
    for (int i = bigNumbers; i < 6; i++){
      int number = chooseRandomNumber(1, 10);
      if (i == 0){
     num1 = number;
    }
    else if (i == 1){
      num2 = number;
    }
     else if (i == 2){
      num3 = number;
    }
    else if (i == 3){
      num4 = number;
    }
    else if (i == 4){
      num5 = number;
    }
    else if (i == 5){
      num6 = number;
    }
    }
    
// setting target number
target = chooseRandomNumber(101, 999);
cout << "Your numbers are: ";
displayNumbers();
cout << "The target is: " << target << endl;
// Game loop
while(true){
int numA, numB;
char oper;
    cout << "Enter a calculation (or 0 to quit): " << endl;
    cin >> numA;
    if (numA == 0){
      break;
    }
    cin >> oper >> numB;
    doCalculation(numA, oper, numB);
// Check for win/loss after every calculation
    if (checkForWin()){
      // exit game once it ended (there is a win or lose)
  break;
}
}

    return 0;
}
