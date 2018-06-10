#pragma once
#include <string>
#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
///
///@brief Class representing game's property
///
class GameStatistics
{
public:
	void loadFromFile(std::string);
	void saveToFile(std::string);
	void updateStatistics(bool);

protected:
	int numberOfGames=0;  //total number of games
	int numberOfGamesWon=0;//total number of games won
	int numberOfGamesLost=0; //total number of games lost
};

