/*
	Author: Brendan Todahl
	Created on: 4/19/2016
	
	DataBase.cpp
	- Contains the class Database that simply separates some code from Game.cpp for readability
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "User.h"
#include "Database.h"
using namespace std;

User* Database::signIn(bool *inMainMenu, User *currentUser) {
	// Attempt Login
	cout << "Enter Username: "; 
	string userName;
	cin >> userName;
	cout << "Enter password: ";
	string password;
	cin >> password;
	// Search in UserData.txt for user
	bool userFound = false;
	string line;
	ifstream userDataFile ("UserData.txt");
	if (userDataFile.is_open())
	{
		getline(userDataFile, line); // Clear the format line
		while (userFound == false && getline (userDataFile, line))
		{
			istringstream iss (line);
			string tempID, tempUserName, tempPassword;
			iss >> tempID;
			iss >> tempUserName;
			iss >> tempPassword;
			if (userName.compare(tempUserName) == 0 && password.compare(tempPassword) == 0)
			{
				userFound = true;
				*inMainMenu = false;
				currentUser = new User(atoi(tempID.c_str()), tempUserName, tempPassword);
				currentUser->setLoggedIn(true);
			}
		}
		userDataFile.close();
	}
	else
		cerr << "Error: Unable to open file." << endl;
	if (!currentUser->getLoggedIn())
		cout << "Error: Either your username or password is incorrect." << endl;

	return currentUser;
};

void Database::createAccount() {
	string userName;
	string possibleID;
	bool inAccountCreation = true;
	while (inAccountCreation)
	{
		// Account Creation
		cout << "Enter Desired Username: "; 
		cin >> userName;
		// Search in UserData.txt to see if name is available
		bool userFound = false;
		string line;
		ifstream userDataFile ("UserData.txt");
		if (userDataFile.is_open())
		{
			getline(userDataFile, line); // Clear the format line
			while (userFound == false && getline (userDataFile, line))
			{
				istringstream iss (line);
				string tempUserName, tempPassword;
				iss >> possibleID; // Need to clear the ID
				iss >> tempUserName;
				if (userName.compare(tempUserName) == 0)
				{
					userFound = true;
				}
			}
			userDataFile.close();
		}
		else
			cerr << "Error: Unable to open file." << endl;
		if (!userFound)
			inAccountCreation = false;
		else
			cout << "Username already taken. Try another..." << endl;
	}
	// Username is not taken so proceed with account creation
	cout << "Enter password: ";
	string password;
	cin >> password;
	int nextID = atoi(possibleID.c_str()) + 1;
	string ID;
	ostringstream convert;
	convert << nextID;
	ID = convert.str();
	ofstream userDataFile;
	userDataFile.open("UserData.txt", ios::app);
	// Write user account information
	if (userDataFile.is_open())
	{
		userDataFile << "\n" << ID << " " << userName << " " << password;
	}
	else
		cerr << "Error: unable to open file." << endl;
	ofstream userStatsFile;
	userStatsFile.open("Scores.txt", ios::app);
	// Initialize new user scores in Scores.txt
	if (userStatsFile.is_open())
	{
		userStatsFile << "\n" << ID << " 0" << " 0";
	}
};