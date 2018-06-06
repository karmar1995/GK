#pragma once
#include<vector>
#include "Tower.h"
#include "Map.hpp"

class TowerGraphic;

///
///@brief Class managing towers and theirs collection
///
///It provides methods to buying, upgrading and selling towers \n
///Also manages player cash
///
class TowerManager
{
public:
	TowerManager(const Map &m);
	virtual ~TowerManager();

	bool buy(int x, int y);
	void sell(const Tower &t);
	void sell(int x, int y);
	bool upgrade(const Tower &t);
	bool upgrade(int x, int y);
	Tower& get(int x, int y);
	Tower& operator[](int i);
	bool isTower(int x, int y) const;
	int getSize() const;
	bool updateGraphic(TowerGraphic &tg);
	void AddCash(uint v);
	std::string GetCash() const;

	///@brief Gets iterator set to begin of tower collection
	///@returns begin iterator
	auto begin() const { return tab.begin(); }; 
	///@brief Gets iterator set to end of tower collection
	///@returns end iterator
	auto end() const { return tab.end(); };
	std::vector<Tower> tab;						///<Collection of towers
private:
	bool modified;								///<Indicates if object was modified recently
	const Map &map;								///<Logic map
	int m_iCash;								///<Cash amount

	void add(Tower t);
	void remove(int x, int y);
	void clear();

};

