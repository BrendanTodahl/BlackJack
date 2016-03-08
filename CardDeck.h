/*
	Author: Brendan Todahl
	Created on: 3/8/2016
	
	CardDeck.h
	- Contains the class CardDeck that will be a collection of cards
*/

#ifndef CARDDECK_H
#define CARDDECK_H

#include <iostream>
#include "Card.h"
using namespace std;


class CardDeck {

	private:
	queue<Card> deck; // doesn't like Card here
	
	public:
	CardDeck();
};

#endif
