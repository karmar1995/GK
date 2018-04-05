#pragma once
#include <string>
#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
class GameStatistics
{
public:
	void loadFromFile(std::string);
	void saveToFile(std::string);
	void updateStatistics(bool);

protected:
	int numberOfGames=0;
	int numberOfGamesWon=0;
	int numberOfGamesLost=0;


	
};

