/*
	Author: Brendan Todahl
	Created on: 3/8/2016
	
	Game.cpp
	- Handles the game mechanics
*/

#include <iostream>
#include <vector>
#include <string>
#include "Card.h"
#include "CardDeck.h"
using namespace std;

// Starts the round by dealing two cards to both the player and dealer starting with the player
void initialDeal(CardDeck *deck, std::vector<Card> *dealerHand, std::vector<Card>  *playerHand);
// Plays the game for the dealer, completing theiry hand
void finishDealerHand(CardDeck *deck, std::vector<Card> *dealerhand);
// Takes the player and dealer's score and determines the outcome of the round
void determineWinner(int dealerScore, int playerScore, int dealerHandSize, int playerHandSize, bool *gameRunning, bool *round);
// Takes the hands of both the dealer and players and their respective scores and prints the information to the screen
void printHands(std::vector<Card> dealerHand, std::vector<Card> playerHand, int dealerScore, int playerScore, bool isRoundOver);
// Calculates the score of the given hand
int calculateScore(std::vector<Card> hand, bool isDealerHand, bool isRoundOver);

int main () 
{
	cout << "Welcome to BlackJack!" << endl << "1. Play game ... more soon! ";
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
			std::vector<Card> dealerHand;
			std::vector<Card> playerHand;
			
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
		cout << "Thanks for playing!" << endl;
	}
	return 0;
}

void initialDeal(CardDeck *deck, std::vector<Card> *dealerHand, std::vector<Card>  *playerHand)
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

void finishDealerHand(CardDeck *deck, std::vector<Card> *dealerHand)
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
	}
	else if (dealerScore > 21) // Dealer bust
	{
		cout << "Dealer bust! Player wins! Play again?" << endl;
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
		}
	}
	else if (dealerScore == 21 && dealerHandSize == 2)
	{
		cout << "BlackJack! Dealer wins! Play again?" << endl;
	}
	else if (playerScore > dealerScore) // Player win
	{
		cout << "Player wins! Play again?" << endl;
	}
	else if (dealerScore > playerScore) // Dealer win
	{
		cout << "Dealer wins! Play again?" << endl;
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

void printHands(std::vector<Card> dealerHand, std::vector<Card> playerHand, int dealerScore, int playerScore, bool isRoundOver) 
{
	int i;
	cout << endl << "Dealer: ";
	if (isRoundOver)
	{
		// Show all cards, round is over
		for (i = 0; i < dealerHand.size(); i++)
		{
			cout << " " << dealerHand[i].cardName << "-" << dealerHand[i].suite << " ";
		}
	}
	else
	{
		// Show all but one of the dealers cards
		for (i = 0; i < dealerHand.size() - 1; i++)
		{
			cout << " " << dealerHand[i].cardName << "-" << dealerHand[i].suite << " ";
		}
	}
	cout << endl;
	cout << "Dealer Score: " << dealerScore << endl;
	cout << "Player: "; // Replace this with user name
	for (i = 0; i < playerHand.size(); i++)
	{
		cout << " " << playerHand[i].cardName << "-" << playerHand[i].suite << " ";
	}
	cout << endl;
	cout << "Player Score: " << playerScore << endl;
}

int calculateScore(std::vector<Card> hand, bool isDealerHand, bool isRoundOver)
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
		string cardName = hand[i].cardName;
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
