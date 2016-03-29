/*
	Author: Brendan Todahl
	Created on: 3/8/2016
	
	Game.cpp
	- Handles the game mechanics
*/

#include <iostream>
#include "Card.h"
#include "CardDeck.h"
using namespace std;

int main () {
	CardDeck *deck = new CardDeck();
	std::list<Card>::const_iterator iterator;
	for (iterator = deck->deck.begin(); iterator != deck->deck.end(); ++iterator)
	{
		cout << "Suite: " << (*iterator).suite << " Card name: " << (*iterator).cardName << endl;
	}
	return 0;
}
