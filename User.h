/*
	Author: Brendan Todahl
	Created on: 4/7/2016
	
	User.h
	- Contains the class User that defines a User
*/

#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

class User {
public:
	User();
	User(string aUserName, string aPassword, string aName);
	getLoggedIn();
	setLoggedIn(bool aLoggedIn);

	string userName;
	string password;
	string name;

private:
	bool loggedIn;
};

#endif
