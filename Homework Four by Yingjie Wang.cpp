/*
CMPSC201 Homework Four
objectives: Be able to create and call programmer-defined functions, use arrays in functions and use pass-by-reference arguments
Purpose: Create a console program to simulate the outcome of a card game for 2-6 players.The game consists of one or more rounds where each player plays one card. Each round also has a lead suit (card symbol). The winner of the round is the player with the highest rank (card number) in the same suit as the lead suit.
input:  rounds.txt
output: a visual representation of the round with the lead suit followed by the cards, a visual representation of the round with the lead suit followed by the cards and the winner of the game with total score
Date 7/27/2015
By Yingjie Wang
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

#define pMax 6
#define rMax 50

//declare ifstream and ofstream
ifstream fin;

// Function prototypes
void printRound(const int ranks[], const char suits[], int numPlayers, char lead);
int playRound(const int ranks[], const char suits[], int numPlayers, char lead, int &score);
void printScoreboard(const int winners[], const int scores[], const string names[], int numRounds);
int gameWinner(const int winners[], const int scores[], int numRounds, int &score);


int main(){

	//check whether a file was opened successfully
	fin.open("rounds.txt");
	if (fin.fail()){
		cout << "Input file opening failed" << endl;
		exit(1);
	}

	//geting the info
	int numPlayers, numRounds, ranks[pMax], winners[rMax], scores[rMax];
	string names[pMax];
	char lead, suits[pMax];

	fin >> numPlayers;
	for (int i = 0; i < numPlayers; i++){
		fin >> names[i];
	}

	//output
	fin >> numRounds;
	for (int i = 0; i < numRounds; i++){
		fin >> lead;
		for (int j = 0; j < numPlayers; j++){
			fin >> ranks[j] >> suits[j];
		}
		printRound(ranks, suits, numPlayers, lead);
		winners[i] = playRound(ranks, suits, numPlayers, lead, scores[i]);
		cout << names[winners[i]] << " wins the round for " << scores[i] << " points.\n";
	}
	fin.close();

	cout << endl;
	printScoreboard(winners, scores, names, numRounds);

	int score;
	int winner = gameWinner(winners, scores, numRounds, score);

	cout << names[winner] << " wins the game with " << score << " total points.\n";
	return 0;
}

//function definition
void printRound(const int ranks[], const char suits[], int numPlayers, char lead){
	cout << "(" << lead << ")";
	
	for (int k = 0; k < numPlayers; k++){
		if (ranks[k] == 11){
			cout << "\t|" << 'J' << suits[k] << "|";
		}
		else if (ranks[k] == 12){
			cout << "\t|" << 'Q' << suits[k] << "|";
		}
		else if (ranks[k] == 13){
			cout << "\t|" << 'K' << suits[k] << "|";
		}
		else if (ranks[k] == 1){
			cout << "\t|" << 'A' << suits[k] << "|";
		}
		else{
			cout << "\t|" << ranks[k] << suits[k] << "|";
		}
	}
	
	cout << endl;

	return;
}

int playRound(const int ranks[], const char suits[], int numPlayers, char lead, int &score){
	int winner = -1;
	score = 0;
	for (int i = 0; i < numPlayers; i++){
		if (suits[i] == lead){
			if (score == 0){
				winner = i;
			}
			else{
				winner = (ranks[i] == 1 || (ranks[i] > ranks[winner] && ranks[winner] != 1) ? i : winner);
			}
			score++;	
		}
	}
	return winner;
}

void printScoreboard(const int winners[], const int scores[], const string names[], int numRounds){
	cout << "Round\t| Winner\t| Score\n"
		"--------------------------------\n";
	for (int i = 0; i < numRounds; i++)
		cout << " " << i + 1 << "\t|  " << names[winners[i]] << "\t|  " << scores[i] << endl;
	cout << "--------------------------------\n";
	return;
}

int gameWinner(const int winners[], const int scores[], int numRounds, int &score){
	int total[pMax] = { 0 }, winner = -1;
	for (int i = 0; i < numRounds; i++){
		total[winners[i]] += scores[i];
		if (winner == -1)
			winner = winners[i];
		else if (total[winners[i]] > total[winner])
			winner = winners[i];
	}
	score = total[winner];
	return winner;
}
