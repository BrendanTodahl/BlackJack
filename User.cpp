/*
	Author: Brendan Todahl
	Created on: 4/7/2016
	
	User.cpp
	- Contains the class User that defines a User
*/

#include <iostream>
#include "User.h"
using namespace std;

User::User() {
	userName = "";
	password = "";
	name = "";
	loggedIn = false;
};

User::User(string aUserName, string aPassword, string aName) {
	userName = aUserName;
	password = aPassword;
	name = aName;
	loggedIn = false;
};

User::getLoggedIn() {
	return loggedIn;
};

User::setLoggedIn(bool aLoggedIn) {
	loggedIn = aLoggedIn;
};