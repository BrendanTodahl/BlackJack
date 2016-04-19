/*
	Author: Brendan Todahl
	Created on: 3/8/2016
	
	CardDeck.cpp
	- Contains the class CardDeck that will be a collection of cards
*/

#include <iostream>
#include <algorithm>
#include "CardDeck.h"
#include "Card.h"
using namespace std;

CardDeck::CardDeck() {
	// Generate the card deck
	string suites[] = {"Hearts", "Diamonds", "Spades", "Clubs"};
	string cardNames[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			Card *card = new Card(suites[i], cardNames[j]);
			deck.push_back(*card);
		}
	}
};

void CardDeck::shuffle() {
	random_shuffle(deck.begin(), deck.end());
};

