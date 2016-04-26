/*
	Author: Brendan Todahl
	Created on: 4/7/2016
	
	User.cpp
	- Contains the class User that defines a User
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include "User.h"
using namespace std;

User::User() {
	ID = 0;
	userName = "";
	password = "";
	loggedIn = false;
};

User::User(int aID, string aUserName, string aPassword) {
	ID = aID;
	userName = aUserName;
	password = aPassword;
	loggedIn = false;
	fetchGameStats();
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

string User::getUserPassword() {
	return password;
};

// Get a reference to the current stats of current user
void User::fetchGameStats() {
	string line;
	ifstream userStatsFile ("Scores.txt");
	if (userStatsFile.is_open())
	{
		bool userFound = false;
		getline(userStatsFile, line); // Clear the format line
		while (!userFound && getline (userStatsFile, line))
		{
			istringstream iss (line);
			string tempID;
			iss >> tempID;
			if (atoi(tempID.c_str()) == ID)
			{
				userFound = true;
			}
		}
		userStatsFile.close();
		istringstream iss (line);
		string tempID, tempNumGamesWon, tempNumGamesPlayed;
		iss >> tempID;
		iss >> tempNumGamesWon;
		iss >> tempNumGamesPlayed;
		numGamesWon = atoi(tempNumGamesWon.c_str());
		numGamesPlayed = atoi(tempNumGamesPlayed.c_str());
		if (numGamesPlayed == 0)
		{
			winPercentage = 0.0;
		}
		else
		{
			winPercentage = (float)numGamesWon/numGamesPlayed;
		}
	}
	else
		cerr << "Error: Unable to open file." << endl;
};

void User::updateStats(bool playerWon) {
	// read from file and update stats of current player object
	vector<string> lines;
	int lineNumberOfUser = 1;
	string line;
	ifstream userStatsFile ("Scores.txt");
	if (userStatsFile.is_open())
	{
		getline(userStatsFile, line); // Clear the format line
		lines.push_back(line);
		int counter = 1;
		while (getline (userStatsFile, line))
		{
			istringstream iss (line);
			string tempID;
			iss >> tempID;
			if (atoi(tempID.c_str()) == ID)
			{
				istringstream iss (line);
				string tempID, tempNumGamesWon, tempNumGamesPlayed;
				iss >> tempID;
				iss >> tempNumGamesWon;
				iss >> tempNumGamesPlayed;
				numGamesPlayed = atoi(tempNumGamesPlayed.c_str()) + 1;
				if (playerWon)
				{
					numGamesWon = atoi(tempNumGamesWon.c_str()) + 1;
				}
				winPercentage = (float)numGamesWon/numGamesPlayed;
				lineNumberOfUser = counter;
			}
			lines.push_back(line);
			counter++;
		}
		userStatsFile.close();
	}
	else
		cerr << "Error: Unable to open file." << endl;
	userStatsFile.close();
	
	// write back to the same file with the updated stats
	ofstream userStatsFileUpdate;
	userStatsFileUpdate.open("Scores.txt");
	if (userStatsFileUpdate.is_open())
	{
		int i;
		for (i = 0; i < lines.size(); i++)
		{
			if (i == lineNumberOfUser)
			{
				if (i == lines.size() - 1)
				{
					userStatsFileUpdate << ID << " " << numGamesWon << " " << numGamesPlayed;
				}
				else
				{
					userStatsFileUpdate << ID << " " << numGamesWon << " " << numGamesPlayed << "\n";
				}
			}
			else
			{
				if (i == lines.size() - 1)
				{
					userStatsFileUpdate << lines[i];
				}
				else
				{
					userStatsFileUpdate << lines[i] << "\n";
				}
			}
		}
	}
	else
		cerr << "Error: unable to open file." << endl;
	userStatsFileUpdate.close();
};

int User::getNumGamesWon() {
	return numGamesWon;
};

int User::getNumGamesPlayed() {
	return numGamesPlayed;
};

float User::getWinPercentage() {
	return winPercentage;
};