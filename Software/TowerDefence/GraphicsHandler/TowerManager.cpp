#include "TowerManager.h"



TowerManager::TowerManager(const Map &m): map(m)
{
}


TowerManager::~TowerManager()
{
}

bool TowerManager::buy(int x, int y)
{
	if (map.GetPoint(x,y).GetTerrainType() == Point::TerrainType::TT_EMPTY 
			&& !isTower(x, y)) 
	{
		//if(cash-Tower::getPrice()>=0)
		{
			//cash-=Tower::getPrice();
			add(Tower(x, y));
			return true;
		}
	}
	return false;
}

void TowerManager::sell(const Tower & t)
{
	sell(t.getX(), t.getY());
}

void TowerManager::sell(int x, int y)
{
	remove(x, y);
	//cash+=Tower::getPrice();
}

bool TowerManager::upgrade(const Tower & t)
{
	return upgrade(t.getX(), t.getY());
}

bool TowerManager::upgrade(int x, int y)
{
	if (isTower(x, y)) 
	{
		//if(cash-upgradePrice>=0)
		{
			//cash-=upgradePrice;
			return get(x, y).upgrade();
		}
	}
	return false;
}

Tower & TowerManager::get(int x, int y)
{
	for (auto it=tab.begin(); it != tab.end(); ++it)
	{
		if (it->getX() == x && it->getY() == y)
			return *it;
	}
	return Tower(-1, -1);
}

bool TowerManager::isTower(int x, int y) const
{
	for (Tower t : tab)
	{
		if (t.getX() == x && t.getY() == y)
			return true;
	}
	return false;
}

int TowerManager::getSize() const
{
	return tab.size();
}

void TowerManager::add(Tower t)
{
	tab.push_back(t);
}

void TowerManager::remove(int x, int y)
{
	if (isTower(x, y))
	{
		auto it = tab.begin();
		for (it; it != tab.end(); ++it)
		{
			if (it->getX() == x && it->getY() == y)
				break;
		}
		tab.erase(it);
	}
}

void TowerManager::clear()
{
	tab.clear();
}