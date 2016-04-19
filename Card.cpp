/*
	Author: Brendan Todahl
	Created on: 3/8/2016
	
	Card.cpp
	- Contains the class Card that defines a card
*/

#include <iostream>
#include "Card.h"
using namespace std;

Card::Card(string aSuite, string aCardName) {
	suite = aSuite;
	cardName = aCardName;
};

string Card::getSuite() {
	return suite;
};

string Card::getCardName() {
	return cardName;
};