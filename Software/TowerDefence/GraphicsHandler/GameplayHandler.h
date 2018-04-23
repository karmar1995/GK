#pragma once
#ifndef WIN32
#include <SFML/Graphics.hpp>
#endif
#include <iostream>
#include <cstdlib>
#include "Scene.h"
#include "GraphicManager.h"
#include "EnemyDesigner.h"
#include "TowerManager.h"
#include "TowerGraphic.h"
#include "BulletDesigner.h"
#include "GameStatistics.h"
#include "ConfigurationManager.h"
#include <memory>

typedef std::vector<EnemyDesigner*> EnemyVector;

const std::vector<std::string> MapFiles = { "Testcases\\Map.txt"};

class GameplayHandler
{
	Map* m_Map;
	TowerManager* m_TowerManager;
	Scene* m_Scene;
	EnemyVector m_EnemyVector;
	GameStatistics m_GameStatistics;
	ConfigurationManager m_CfgMng;
	sf::RenderWindow m_Window;
	std::string m_CurrentMap;
	bool m_Valid;
public:
	explicit GameplayHandler();
	bool isValid() { return m_Valid; }
	void MainLoop();
	~GameplayHandler();
private:
	void ReleaseResources();
	bool ParseMap();
	void PushEnemies(); //this will be replaced when the parsing of config file will be done!
};

