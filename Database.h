/*
	Author: Brendan Todahl
	Created on: 4/19/2016
	
	Database.h
	- Contains the class Database that simply separates some code from Game.cpp for readability
*/

#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "User.h"
using namespace std;

class Database {
public:
	static User* signIn(bool *inMainMenu, User *currentUser);
	static void createAccount();
};

#endif
