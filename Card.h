/*
	Author: Brendan Todahl
	Created on: 3/8/2016
	
	Card.h
	- Contains the class Card that defines a card
*/

#ifndef CARD_H
#define CARD_H

#include <iostream>
using namespace std;

class Card {
	private:
	string suite;
	int number; // Jack = 11, Queen = 12, King = 13, A = 1
	
	public:
	Card(string aSuite, int aNumber);
};

#endif
