// Author: Ahmed Yousef
// Project 4 : Presedential Elections
// Submittion Date: 11/11/2024
// Project Description: The presienctial election program is a program that reads and analyzes voting data for a U.S. presedential election.
// It loads data from a file, which includes information on states, counties, candidates, parties, and vote counts.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Define a class to hold vote data for each record
class Votes {
public:
 string stateName;
 string countyName;
 string candidateName;
 string partyName;
 int numVotes;
// Constructor for full record (state, county, candidate, party, votes)
  Votes(string stateName, string countyName, string candidateName, string partyName, int numVotes )
 {
    this->stateName = stateName;
    this->countyName = countyName;
    this->candidateName = candidateName;
    this->partyName = partyName;
    this->numVotes = numVotes;
 }

 };
// List of all states;
const string STATES[] = { "ALABAMA", "ALASKA", "ARIZONA", "ARKANSAS", "CALIFORNIA", "COLORADO",
	"CONNECTICUT", "DELAWARE", "FLORIDA", "GEORGIA", "HAWAII", "IDAHO", "ILLINOIS",
	"INDIANA", "IOWA", "KANSAS", "KENTUCKY", "LOUISIANA", "MAINE", "MARYLAND", "MASSACHUSETTS", "MICHIGAN",
	"MINNESOTA", "MISSISSIPPI", "MISSOURI", "MONTANA", "NEBRASKA", "NEVADA", "NEW HAMPSHIRE", "NEW JERSEY",
	"NEW MEXICO", "NEW YORK", "NORTH CAROLINA", "NORTH DAKOTA", "OHIO", "OKLAHOMA", "OREGON", "PENNSYLVANIA",
	"RHODE ISLAND", "SOUTH CAROLINA", "SOUTH DAKOTA", "TENNESSEE", "TEXAS", "UTAH", "VERMONT", "VIRGINIA",
	"WASHINGTON", "WASHINGTON DC", "WEST VIRGINIA", "WISCONSIN", "WYOMING" };
 // number of states
 const int NUM_STATES = 51;
 
vector <Votes> voteObjects;
// displays the menu each time
void displayMenu(){
    cout << "Select a menu option:" << endl;
    cout << "  1. Data overview" << endl;
    cout << "  2. National results" << endl;
    cout << "  3. State results" << endl;
    cout << "  4. Candidate results" << endl;
    cout << "  5. County search" << endl;
    cout << "  6. Exit" << endl;
    cout << "Your choice: ";
     
}
// Function to show summary of the total records and votes in the election data
void dataOverview(){
    cout << "Number of election records: " << voteObjects.size()  << endl; 
  cout << "Total number of votes recorded: ";
  int voteNumber = 0;
    for (unsigned int i = 0; i < voteObjects.size() ; i++){
        voteNumber = voteObjects[i].numVotes + voteNumber;
    }
    cout << voteNumber << endl;
}
// displays national result and sort candidates by vote count
void nationalResult(){
    cout << endl;
vector<string> candidates;
vector <int> candidateVotes;
vector <string> candidateParty;


// Add up votes for each candidate
for (const auto&vote : voteObjects){
string candidate = vote.candidateName;
int votes = vote.numVotes;
string party = vote.partyName;

 bool founded = false;
for (size_t i = 0; i < candidates.size(); i++ ){
if (candidates[i] == candidate && candidateParty[i] == party ){
    candidateVotes[i] += votes;
    founded = true;
    break;
}
}  
// adds new entry if candidate is not founded
if (!founded){
    candidates.push_back(candidate);
    candidateVotes.push_back(votes);
    candidateParty.push_back(party);
}
}
// sort candidates
for (size_t i = 0; i < candidateVotes.size() - 1; i++){
    for (size_t j = 0; j < candidateVotes.size() -1; j++){
        if (candidateVotes[j] < candidateVotes[j+1]){
            swap(candidateVotes[j], candidateVotes[j+1] );
            swap(candidates[j], candidates[j+1] );
            swap(candidateParty[j], candidateParty[j+1] );
        }
    }
}





for (size_t i = 0; i < candidates.size(); i++ ){
cout << left << setw(20) <<  candidates[i];
cout << setw(15) <<  candidateParty[i]; 
cout << right << setw(10) << candidateVotes[i] << endl;
}
}

  void stateResults() {
 //   cout << endl;
cout << "Enter state: ";
string inputState;
cin.ignore();
getline(cin, inputState);
for (size_t i = 0; i < inputState.length(); i++){
    if (inputState[i] >= 'a' && inputState[i] <= 'z'){
        inputState[i] = inputState[i] - 'a' + 'A';
    }
}

vector <string> stateCandidates;
vector <int> stateVotes;

for (const auto& vote : voteObjects){
string state = vote.stateName;

for (size_t i = 0; i < state.length(); i++){
    if (state[i] >= 'a' && state[i] <= 'z'){
        state[i] = state[i] - 'a' + 'A';
    }
}

if (state == inputState){
bool found = false;
for (size_t i = 0; i < stateCandidates.size(); i++ ){
if (stateCandidates[i] == vote.candidateName ){
    stateVotes[i] += vote.numVotes;
    found = true;
    break;
}
}  

if (!found){
     stateCandidates.push_back(vote.candidateName);
    stateVotes.push_back(vote.numVotes);
}
}
}

  for (size_t i = 0; i < stateVotes.size() - 1; i++) {
        for (size_t j = 0; j < stateVotes.size() - i - 1; j++) {
            if (stateVotes[j] < stateVotes[j + 1]) {
                swap(stateVotes[j], stateVotes[j + 1]);
                swap(stateCandidates[j], stateCandidates[j + 1]);
            }
        }
    }

for (size_t i = 0; i < stateCandidates.size(); i++){
    cout << left << setw(20) << stateCandidates[i];
    int barLength = (stateVotes[i] + 75000) / 150000;
    cout << string(barLength, '|') << endl;
}
} 

// Function to display candiate results across all states
void candidateResults() {
    cout << endl;
cout << "Enter candidate: ";
string inputCandidate;
cin.ignore();
getline(cin, inputCandidate);
cout << endl;
for(char& c : inputCandidate){
    c = toupper(c);
}

vector <string> statesWithVotes;
vector <int> votesForCandidate;
vector <int> totalVotesInState;

double bestPercentage = -1.0;
string bestState;
string fullCandidateName;

for (int i = 0; i < NUM_STATES; i++){
    string stateName = STATES[i];
    int candidateVotes = 0;
    int stateVotes = 0;

 for (const auto& vote : voteObjects){
    string candidate = vote.candidateName;
    for (char& c : candidate) {
                c = toupper(c);
            }

        if (candidate.find(inputCandidate) != string::npos && vote.stateName == stateName){
            candidateVotes += vote.numVotes;
            fullCandidateName = vote.candidateName;
        }
        if (vote.stateName == stateName){
            stateVotes += vote.numVotes;
        }
    }

      if (candidateVotes >= 0){
       double percentage = (static_cast<double>(candidateVotes) / stateVotes) * 100;

       statesWithVotes.push_back(stateName);
       votesForCandidate.push_back(candidateVotes);
       totalVotesInState.push_back(stateVotes);

       if (percentage > bestPercentage){
        bestPercentage = percentage;
        bestState = stateName;
       }

      }

}

  for (size_t i = 0; i < statesWithVotes.size(); ++i){
    string state = statesWithVotes[i];
    int candidateVotes = votesForCandidate[i];
    int totalVotes = totalVotesInState[i];
    double percentage = (static_cast<double>(candidateVotes) / totalVotes) * 100;

    cout << left << setw(20) << state << right << setw(10) << candidateVotes << right << setw(10) << totalVotes << right << setw(7) << fixed << setprecision(1) << percentage << "%" << endl;
  }


   cout << "The best state for " << fullCandidateName << " is " << bestState << endl;






}

// Function to search for votes by county
void countySearch(){
    cout << "Enter county: ";
    string inputCounty;
    cin.ignore();
    getline(cin, inputCounty);

    for (char& c: inputCounty){
        c = toupper(c);
    }
    bool founded = false;

    for (const auto&vote : voteObjects){
        string county = vote.countyName;
        for (char& c: county){
            c = toupper(c);
        }
       if (county.find(inputCounty) != string::npos){
         string countyState = vote.countyName + ", " + vote.stateName;
         cout << left << setw(40) << countyState << left << setw(20) << vote.candidateName << right << setw(10) << vote.numVotes << endl;
         founded = true;
       }

    }




}//end of countySearch




int main() {
    string filetoUse;
    cout << "Enter file to use: ";
    cin >> filetoUse;
  
    cout << endl;
 // displays the menu options to prompt the user
   displayMenu();
    ifstream fileIn;
    fileIn.open(filetoUse);

    while(!fileIn.eof()){
        string stateName;
        string countyName;
        string candidateName;
        string partyName;
        string stringNumVotes;
        
        getline(fileIn, stateName, ',');
        getline(fileIn, countyName, ',');
        getline(fileIn, candidateName, ',');
        getline(fileIn, partyName, ',');
        getline(fileIn, stringNumVotes);
        int numVotes = stoi(stringNumVotes);
        Votes objectV(stateName, countyName, candidateName, partyName, numVotes);
        voteObjects.push_back(objectV);
       
   
    }
while(true){
    int choice;
   cin >> choice;
   switch(choice){
    case 1:
    dataOverview();
    displayMenu();
    break;
    case 2:
    nationalResult();
    displayMenu();
    break;
    case 3:
     stateResults();
       displayMenu();
       break;
    case 4:
       candidateResults();
       displayMenu();
       break;
    case 5:
     countySearch();
       displayMenu();
       break;
    case 6:
    return 0;
    default:
    break;
   }
}

   
return 0;
}
