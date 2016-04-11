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
	User(string aUserName, string aPassword);
	bool getLoggedIn();
	void setLoggedIn(bool aLoggedIn);
	string getUserName();
	void setUserName(string aUserName);
	string getPassword();
	void setPassword(string aPassword);
private:
	string userName;
	string password;
	bool loggedIn;
};

#endif
