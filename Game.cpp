/*
	Author: Brendan Todahl
	Created on: 3/8/2016
	
	Game.cpp
	- Handles the game mechanics

	TODO:
	- Add comments and cleanup code
	- Add high scores view
	- View high score for current player
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Card.h"
#include "CardDeck.h"
#include "User.h"
using namespace std;

// Handles signing a user in
void signIn(bool *inMainMenu);
// Handles account creation
void createAccount();
// Starts the round by dealing two cards to both the player and dealer starting with the player
void initialDeal(CardDeck *deck, vector<Card> *dealerHand, vector<Card>  *playerHand);
// Plays the game for the dealer, completing theiry hand
void finishDealerHand(CardDeck *deck, vector<Card> *dealerhand);
// Takes the player and dealer's score and determines the outcome of the round. Tie doesn't change stats.
void determineWinner(int dealerScore, int playerScore, int dealerHandSize, int playerHandSize, bool *gameRunning, bool *round);
// Takes the hands of both the dealer and players and their respective scores and prints the information to the screen
void printHands(vector<Card> dealerHand, vector<Card> playerHand, int dealerScore, int playerScore, bool isRoundOver);
// Calculates the score of the given hand
int calculateScore(vector<Card> hand, bool isDealerHand, bool isRoundOver);

User *currentUser = new User();

int main () 
{
	bool applicationRunning = true;
	while (applicationRunning)
	{
		bool inMainMenu = true;
		while (inMainMenu)
		{
			cout << endl << "Welcome to BlackJack! What would you like to do?" << endl;
			cout << "1. Sign In 2. Make Account 3. Quit ";
			int mainMenuInput;
			cin >> mainMenuInput;
			if (mainMenuInput == 1)
			{
				signIn(&inMainMenu);
			}
			else if (mainMenuInput == 2)
			{
				createAccount();
			}
			else if (mainMenuInput == 3)
			{
				inMainMenu = false;
				applicationRunning = false;
			}
		}
		if (currentUser->getLoggedIn()) // Check if user is logged in
		{
			while (currentUser->getLoggedIn())
			{
				cout << endl << "Welcome " << currentUser->getUserName() << "!" << endl;
				cout << "1. Play game 2. Stats 3. Logout ";
				int userInput;
				cin >> userInput;
				
				if (userInput == 1)
				{
					// Start game
					bool gameRunning = true;
					while (gameRunning)
					{
						CardDeck *deck = new CardDeck();
						deck->shuffle();
						vector<Card> dealerHand;
						vector<Card> playerHand;
						
						initialDeal(deck, &dealerHand, &playerHand);	
						bool round = true;
						bool userHandComplete = false;
						while (round)
						{
							int dealerScore = calculateScore(dealerHand, true, false);
							int playerScore = calculateScore(playerHand, false, false);
							if (!userHandComplete && playerScore < 21)
							{
								printHands(dealerHand, playerHand, dealerScore, playerScore, false);
								cout << "1. Hit 2. Stay ";
								int roundChoice;
								cin >> roundChoice;
								if (roundChoice == 1)
								{
									playerHand.push_back(deck->deck.back());
									deck->deck.pop_back();
								}
								else
								{
									userHandComplete = true;
								}
							}
							else // Finish the dealers hand and finish round
							{
								if (playerScore <= 21 && !(playerScore == 21 && playerHand.size() == 2)) // If player "busts", then dealer doesn't need to play
								{
									finishDealerHand(deck, &dealerHand);
								}
								dealerScore = calculateScore(dealerHand, true, true);
								printHands(dealerHand, playerHand, dealerScore, playerScore, true);
								determineWinner(dealerScore, playerScore, dealerHand.size(), playerHand.size(), &gameRunning, &round);
							}
						}
					}
				}
				else if (userInput == 2) // Check stats
				{
					cout << "Games Won: " << currentUser->getNumGamesWon() << " Games Played: " << currentUser->getNumGamesPlayed() << " Win Percentage: " << currentUser->getWinPercentage() << endl;
				}
				else if (userInput == 3) // logout
				{
					cout << "Thanks for playing!" << endl;
					currentUser = new User();
				}
			}
		}
	}
	return 0;
}

void signIn(bool *inMainMenu)
{
	// Attempt Login
	cout << "Enter Username: "; 
	string userName;
	cin >> userName;
	cout << "Enter password: ";
	string password;
	cin >> password;
	// Search in UserData.txt for user
	bool userFound = false;
	string line;
	ifstream userDataFile ("UserData.txt");
	if (userDataFile.is_open())
	{
		getline(userDataFile, line); // Clear the format line
		while (userFound == false && getline (userDataFile, line))
		{
			istringstream iss (line);
			string tempID, tempUserName, tempPassword;
			iss >> tempID;
			iss >> tempUserName;
			iss >> tempPassword;
			if (userName.compare(tempUserName) == 0 && password.compare(tempPassword) == 0)
			{
				userFound = true;
				*inMainMenu = false;
				currentUser = new User(atoi(tempID.c_str()), tempUserName, tempPassword);
				currentUser->setLoggedIn(true);
			}
		}
		userDataFile.close();
	}
	else
		cerr << "Error: Unable to open file." << endl;
	if (!currentUser->getLoggedIn())
		cout << "Error: Either your username or password is incorrect." << endl;
}

void createAccount()
{
	string userName;
	string possibleID;
	bool inAccountCreation = true;
	while (inAccountCreation)
	{
		// Account Creation
		cout << "Enter Desired Username: "; 
		cin >> userName;
		// Search in UserData.txt to see if name is available
		bool userFound = false;
		string line;
		ifstream userDataFile ("UserData.txt");
		if (userDataFile.is_open())
		{
			getline(userDataFile, line); // Clear the format line
			while (userFound == false && getline (userDataFile, line))
			{
				istringstream iss (line);
				string tempUserName, tempPassword;
				iss >> possibleID; // Need to clear the ID
				iss >> tempUserName;
				if (userName.compare(tempUserName) == 0)
				{
					userFound = true;
				}
			}
			userDataFile.close();
		}
		else
			cerr << "Error: Unable to open file." << endl;
		if (!userFound)
			inAccountCreation = false;
		else
			cout << "Username already taken. Try another..." << endl;
	}
	// Username is not taken so proceed with account creation
	cout << "Enter password: ";
	string password;
	cin >> password;
	int nextID = atoi(possibleID.c_str()) + 1;
	string ID;
	ostringstream convert;
	convert << nextID;
	ID = convert.str();
	ofstream userDataFile;
	userDataFile.open("UserData.txt", ios::app);
	// Write user account information
	if (userDataFile.is_open())
	{
		userDataFile << "\n" << ID << " " << userName << " " << password;
	}
	else
		cerr << "Error: unable to open file." << endl;
	ofstream userStatsFile;
	userStatsFile.open("Scores.txt", ios::app);
	// Initialize new user scores in Scores.txt
	if (userStatsFile.is_open())
	{
		userStatsFile << "\n" << ID << " 0" << " 0";
	}
}

void initialDeal(CardDeck *deck, vector<Card> *dealerHand, vector<Card>  *playerHand)
{
	// Deal the cards
	playerHand->push_back(deck->deck.back());
	deck->deck.pop_back();
	dealerHand->push_back(deck->deck.back());
	deck->deck.pop_back();
	playerHand->push_back(deck->deck.back());
	deck->deck.pop_back();
	dealerHand->push_back(deck->deck.back());
	deck->deck.pop_back();
}

void finishDealerHand(CardDeck *deck, vector<Card> *dealerHand)
{
	bool handFinished = false;
	while (!handFinished)
	{
		if (calculateScore(*dealerHand, true, true) < 17)
		{
			// Dealer has to hit
			dealerHand->push_back(deck->deck.back());
			deck->deck.pop_back();
		}
		else
		{
			handFinished = true;
		}
	}
}

void determineWinner(int dealerScore, int playerScore, int dealerHandSize, int playerHandSize, bool *gameRunning, bool *round)
{
	if (playerScore > 21) // Player bust
	{
		cout << "Player bust! Round over. Play again?" << endl;
		currentUser->updateStats(false);
	}
	else if (dealerScore > 21) // Dealer bust
	{
		cout << "Dealer bust! Player wins! Play again?" << endl;
		currentUser->updateStats(true);
	}
	else if (playerScore == 21 && playerHandSize == 2)
	{
		// Natural or BlackJack
		if (dealerScore == 21 && dealerHandSize == 2)
		{
			cout << "BlackJacks all around! Tie! Play again?" << endl;
		}
		else
		{
			cout << "BlackJack! Player wins! Play again?" << endl;
			currentUser->updateStats(true);
		}
	}
	else if (dealerScore == 21 && dealerHandSize == 2)
	{
		cout << "BlackJack! Dealer wins! Play again?" << endl;
		currentUser->updateStats(false);
	}
	else if (playerScore > dealerScore) // Player win
	{
		cout << "Player wins! Play again?" << endl;
		currentUser->updateStats(true);
	}
	else if (dealerScore > playerScore) // Dealer win
	{
		cout << "Dealer wins! Play again?" << endl;
		currentUser->updateStats(false);
	}
	else // Tie
	{
		cout << "Tie Play again?" << endl;
	}
	cout << "1. Yes 2. No ";
	int playAgain;
	cin >> playAgain;
	if (playAgain == 1)
	{
		*round = false; // To get out of inner loop
		cout << "Starting next round... " << endl;
	}
	else
	{
		*round = false;
		*gameRunning = false; // end game
	}
}

void printHands(vector<Card> dealerHand, vector<Card> playerHand, int dealerScore, int playerScore, bool isRoundOver) 
{
	int i;
	cout << endl << "Dealer: ";
	if (isRoundOver)
	{
		// Show all cards, round is over
		for (i = 0; i < dealerHand.size(); i++)
		{
			cout << " " << dealerHand[i].getCardName() << "-" << dealerHand[i].getSuite() << " ";
		}
	}
	else
	{
		// Show all but one of the dealers cards
		for (i = 0; i < dealerHand.size() - 1; i++)
		{
			cout << " " << dealerHand[i].getCardName() << "-" << dealerHand[i].getSuite() << " ";
		}
	}
	cout << endl;
	cout << "Dealer Score: " << dealerScore << endl;
	cout << "Player: "; // Replace this with user name
	for (i = 0; i < playerHand.size(); i++)
	{
		cout << " " << playerHand[i].getCardName() << "-" << playerHand[i].getSuite() << " ";
	}
	cout << endl;
	cout << "Player Score: " << playerScore << endl;
}

int calculateScore(vector<Card> hand, bool isDealerHand, bool isRoundOver)
{
	int i;
	int score = 0;
	int numOfAces = 0;
	if (isDealerHand && !isRoundOver)
	{
		hand.pop_back();
	}
	for (i = 0; i < hand.size(); i++)
	{
		string cardName = hand[i].getCardName();
		if (cardName.compare("2") == 0 || cardName.compare("3") == 0 || cardName.compare("4") == 0 || cardName.compare("5") == 0 || cardName.compare("6") == 0 || cardName.compare("7") == 0 || cardName.compare("8") == 0 || cardName.compare("9") == 0 || cardName.compare("10") == 0)
		{
			score += atoi(cardName.c_str());
		}
		else if (cardName.compare("Jack") == 0 || cardName.compare("Queen") == 0 || cardName.compare("King") == 0)
		{
			score += 10;
		}
		else if (cardName.compare("Ace") == 0)
		{
			numOfAces++;
		}
	}
	if (numOfAces != 0)
	{
		for (i = 0; i < numOfAces; i++)
		{
			if (score + 11 <= 21 && i == numOfAces - 1)
			{
				score += 11;
			}
			else
			{
				score += 1;
			}
		}
	}
	return score;
}
