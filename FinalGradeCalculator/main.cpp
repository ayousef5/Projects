#include <iostream>
using namespace std;
// This program will determine what grade (percentage) you need on your final exam in order to get a certain grade in a class.
int main()
{
    int currentGrade;  // Current grade in the class
    int gradeWant;     // Desired final grade
    int finalWorth;    // Final exam's weight as a percentage
    int gradeNeeded;   // Grade needed on the final

    // Get inputs from the user
    cout << "Your current grade is: ";
    cin >> currentGrade;

    cout << "You want at least what in the class: ";
    cin >> gradeWant;

    cout << "Your final exam grade is worth (as a percentage): ";
    cin >> finalWorth;

    // Calculate grade needed on the final
    gradeNeeded = ((gradeWant - (currentGrade * (100 - finalWorth) / 100.0)) * 100) / finalWorth;

    // Display the result
    cout << "You need at least " << gradeNeeded << " on the final." << endl;

    return 0;
}
