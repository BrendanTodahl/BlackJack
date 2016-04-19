/*
	Author: Brendan Todahl
	Created on: 4/7/2016
	
	User.h
	- Contains the class User that defines a User
*/

#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <string>
using namespace std;

class User {
public:
	User();
	User(int aID, string aUserName, string aPassword);
	bool getLoggedIn();
	void setLoggedIn(bool aLoggedIn);
	string getUserName();
	void fetchGameStats();
	void updateStats(bool playerWon);
	int getNumGamesWon();
	int getNumGamesPlayed();
	double getWinPercentage();
private:
	int ID;
	string userName;
	string password;
	bool loggedIn;
	int numGamesWon;
	int numGamesPlayed;
	double winPercentage;
};

#endif
