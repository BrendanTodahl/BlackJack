/*
	Author: Brendan Todahl
	Created on: 3/8/2016
	
	Card.cpp
	- Contains the class Card that defines a card
*/

#include <iostream>
#include "Card.h"
using namespace std;

Card::Card(string aSuite, int aNumber) {
	suite = aSuite;
	number = aNumber;
};
