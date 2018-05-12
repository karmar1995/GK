#include "ConfigurationManager.h"
using namespace std;
ConfigurationManager::ConfigurationManager(std::string configFile) {
	this->configFile = configFile;
};
std::vector<Level> ConfigurationManager::getLevels() {
	return this->levels;
}

void ConfigurationManager::readConfiguration() {

	try{
		rapidxml::file<> xmlFile("abc.xml"); 
		xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		xml_node<> * root_node;
		root_node = doc.first_node("first");
		for (xml_node<> * level_node = root_node->first_node("level"); level_node; level_node = level_node->next_sibling())
		{
			Level level;
		
			for (xml_node<> * wave_node = level_node->first_node("wave"); wave_node; wave_node = wave_node->next_sibling())
			{
				Wave wave;
				EnemyDesigner *enemy = nullptr;
				xml_node<> * birdNode;
				xml_node<> * zombieNode;
				xml_node<> * snakeNode;
				xml_node<> * vampireNode;

				birdNode = wave_node->first_node("bird");
				zombieNode = wave_node->first_node("zombie");
				snakeNode = wave_node->first_node("snake");
				vampireNode = wave_node->first_node("vampire");
				wave.addEnemy(atoi(birdNode->value()), enemy,"bird");
				wave.addEnemy(atoi(zombieNode->value()), enemy,"zombie");
				wave.addEnemy(atoi(snakeNode->value()), enemy,"snake");
				wave.addEnemy(atoi(vampireNode->value()), enemy,"vampire");
				level.addWave(wave);

		}
		levels.push_back(level);
	 }
	}
	catch (exception e) {
		Level level;
		Wave wave;
		EnemyDesigner *enemy = nullptr;
		wave.addEnemy(1, enemy, "bird");
		wave.addEnemy(1, enemy, "zombie");
		wave.addEnemy(1, enemy, "snake");
		wave.addEnemy(1, enemy, "vampire");
		levels.push_back(level);

	}
}

	

