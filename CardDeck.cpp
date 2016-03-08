/*
	Author: Brendan Todahl
	Created on: 3/8/2016
	
	CardDeck.cpp
	- Contains the class CardDeck that will be a collection of cards
*/

#include <iostream>
#include "CardDeck.h"
using namespace std;

CardDeck::CardDeck() {
	// Generate the card deck
	string suites[] = {"Hearts", "Diamonds", "Spades", "Clubs"};
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j < 14; j++) {
			//Card *card = new Card("Hearts", 1);
		}
	}
};

