#pragma once
#include<vector>
#include "Tower.h"
#include "Map.hpp"

class TowerGraphic;

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

	auto begin() const { return tab.begin(); };
	auto end() const { return tab.end(); };
	std::vector<Tower> tab;
private:
	bool modified;
	const Map &map;

	void add(Tower t);
	void remove(int x, int y);
	void clear();

};

