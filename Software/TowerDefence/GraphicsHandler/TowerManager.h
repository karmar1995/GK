#pragma once
#include<list>
#include "Tower.h"
#include "Map.hpp"

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
	bool isTower(int x, int y) const;
	int getSize() const;

	auto begin() const { return tab.begin(); };
	auto end() const { return tab.end(); };

private:
	std::list<Tower> tab;
	const Map &map;

	void add(Tower t);
	void remove(int x, int y);
	void clear();

};

