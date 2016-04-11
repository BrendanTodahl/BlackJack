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
	loggedIn = false;
};

User::User(string aUserName, string aPassword) {
	userName = aUserName;
	password = aPassword;
	loggedIn = false;
};

bool User::getLoggedIn() {
	return loggedIn;
};

void User::setLoggedIn(bool aLoggedIn) {
	loggedIn = aLoggedIn;
};

string User::getUserName() {
	return userName;
};

void User::setUserName(string aUserName) {
	userName = aUserName;
};

string User::getPassword() {
	return password;
};

void User::setPassword(string aPassword) {
	password = aPassword;
};