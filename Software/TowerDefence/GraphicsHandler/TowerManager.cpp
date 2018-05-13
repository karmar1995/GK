#include "TowerManager.h"
#include "TowerGraphic.h"



TowerManager::TowerManager(const Map &m): map(m), modified(false), m_iCash(1000)
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
		if(m_iCash-Tower::getPrice()>=0)
		{
			m_iCash -=Tower::getPrice();
			add(Tower(x, y));
			modified = true;
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
	modified = true;
	m_iCash +=Tower::getPrice();
}

bool TowerManager::upgrade(const Tower & t)
{
	return upgrade(t.getX(), t.getY());
}

bool TowerManager::upgrade(int x, int y)
{
	if (isTower(x, y)) 
	{
		if(get(x,y).getLevel() < Tower::getMaxLevel() && m_iCash- get(x, y).upgradePrice()>=0)
		{
			m_iCash -= get(x, y).upgradePrice();
			modified = true;
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

Tower & TowerManager::operator[](int i)
{
	return tab[i];
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

bool TowerManager::updateGraphic(TowerGraphic &tg)
{
	if (modified)
	{
		tg.load(*this);
		modified = false;
		return true;
	}
	return false;
}

void TowerManager::AddCash(uint v)
{
	m_iCash += v;
}

std::string TowerManager::GetCash() const
{
	return std::to_string(m_iCash);
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
