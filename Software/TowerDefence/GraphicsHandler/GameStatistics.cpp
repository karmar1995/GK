#include "GameStatistics.h"


///
///@brief data loader
///Method for reading game's statistics
///
void GameStatistics::loadFromFile(std::string file) {
	std::fstream  myFile;
	myFile.open(file);
	if (!myFile.good()) {
		this->numberOfGames = 0;
		this->numberOfGamesLost = 0;
		this->numberOfGamesWon = 0;
	}
	else {
		std::string temp;
		getline(myFile, temp);
		temp = temp.substr(15);
		try {
			this->numberOfGames = std::stoi(temp);
			getline(myFile, temp);
			temp = temp.substr(19);
			this->numberOfGamesLost = std::stoi(temp);
			getline(myFile, temp);
			temp = temp.substr(18);
			this->numberOfGamesWon = std::stoi(temp);
			myFile.close();
		}
		catch (std::exception e) {
			this->numberOfGames = 0;
			this->numberOfGamesLost = 0;
			this->numberOfGamesWon = 0;
		}
	}
	
}
///
///@brief data loader
///Method for updating statistics
///@param parameter indicating whether game is won, if so-increment numberOfGames won
///
void GameStatistics::updateStatistics(bool isWinner) {
	
	if (isWinner) {
		this->numberOfGames++;
		this->numberOfGamesWon++;
	}
	else {
		this->numberOfGames++;
		this->numberOfGamesLost++;
	}
}

///
///@brief method used for saving resulting statistics
///@param file to which save statistics
///
void GameStatistics::saveToFile(std::string file) {

	std::ofstream  myFile(file);
	if (myFile.good()) {
		myFile.clear();
		myFile << "numberOfGames:";
		myFile << this->numberOfGames;
		myFile << "\n";
		myFile << "numberOfGamesLost:";
		myFile << this->numberOfGamesLost;
		myFile << "\n";
		myFile << "numberOfGamesWon:";
		myFile << this->numberOfGamesWon;
		myFile.close();
	}
	else {
		throw std::exception("invaild file or read only mode");
	}

}