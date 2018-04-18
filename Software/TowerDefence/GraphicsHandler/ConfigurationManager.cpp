#include "ConfigurationManager.h"

ConfigurationManager::ConfigurationManager(std::string configFile) {
	this->configFile = configFile;
};


void ConfigurationManager::readConfiguration(std::string configFile) {

	
	std::fstream  myFile;
	myFile.open(configFile);
	std::string temp;
	Wave wave;
	std::vector<Wave> vectorOfWaves;
	Level level;
	if(myFile.good())
    	getline(myFile, temp);
	temporary = temp;

	
	while(getline(myFile, temp)){
		
			if (temp == "nlevels") {
				getline(myFile, temp);
				numberOfLevels = std::stoi(temp);
				
			}

			if (temp == "---") {
				vectorOfWaves.push_back(wave);
				wave.clearEnemies();
			}
			if (temp == "----") {
				levels.push_back(Level(vectorOfWaves, "abc"));
				vectorOfWaves.clear();
			}

			if (temp == "snake") {
				Snake* snake = nullptr;
				getline(myFile, temp);
				wave.addEnemy(std::stoi(temp), snake);
			}
			if (temp == "zombie") {
				Zombie* zombie = nullptr;
				getline(myFile, temp);
				wave.addEnemy(std::stoi(temp), zombie);
			}
			if (temp == "vampire") {
				Vampire* vampire = nullptr;
				getline(myFile, temp);
				wave.addEnemy(std::stoi(temp), vampire);
			}
		}
	
	myFile.close();
	}
	


	/*
	std::ifstream  myFile("config2.json");
	myFile.open(this->configFile);
	char text[] = R"(
    {
    "nlevels" : 2
     })";



	json j = json::parse(myFile);
	//myFile >> j;
	int nlevels;
	//nlevels = j.value("nlevels",0);
	nlevels = j["nlevels"];
	std::string n_level;
	int nwaves;
	std::string   n_wave;


	std::string mapName;
	std::vector<Wave> vectorOfWaves;

	for (int i = 1; i <= nlevels; i++) {
		std::stringstream ss;
		ss << "Level" << i;
		n_level = ss.str();
		nwaves = j["nwaves"];
		mapName = j["mapname"].dump();
		for (int k = 1; k <= nwaves; k++) {
			std::stringstream sx;
			sx << "Wave" << k;
			n_wave = sx.str();
			Wave wave;
			Zombie *zombie = nullptr;
			Vampire *vampire = nullptr;
			//Bat *bat = nullptr;
			wave.addEnemy(j[n_level][n_wave]["zombie"], zombie);
		//	wave.addEnemy(j[n_level][n_wave]["bat"], bat);
			wave.addEnemy(j[n_level][n_wave]["vampire"], vampire);
			vectorOfWaves.push_back(wave);
			sx.str(std::string());
		}
		this->levels.push_back(Level(vectorOfWaves, mapName));
		ss.str(std::string());
		vectorOfWaves.clear();
	}


	myFile.close();


}
	/*

	if (!myFile.good()) {
		throw std::runtime_error("Unable to open config file");
	}
	else {
		std::string temp;
		getline(myFile, temp);
		temp = temp.substr(15);
		
		
		while (myFile.good()) {
			getline(myFile, temp);
			if(temp=="Level")


			
			if (temp == "Rat") {
				rat *rat;
				wave.addEnemy(1, rat);			
			}
			if (temp == "Orc") {
				orc *orc;
				wave.addEnemy(1, orc);
			}
			
			if (temp == "Bat") {
				troll *troll;
				wave.addEnemy(1, troll);
			}




		}
		
		
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
			
		}
	}
	*/

