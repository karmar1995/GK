#include "TowerManager.h"
#include "TowerGraphic.h"

///
///@brief Constructor, creates manager object working at delivered map
///@param m logical map
///
TowerManager::TowerManager(const Map &m): map(m), modified(false), m_iCash(1000)
{
}

///
///@brief Destructor
///
TowerManager::~TowerManager()
{
}

///
///@brief Buys tower in indicated coords
///
///Tower can be bougth only if choosen square is of empty terrain type and there are sufficient amount of cash
///@param x x coordinate in squares
///@param y y coordinate in squares
///@returns true if operation succeed, false otherwise
///
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

///
///@brief Sells selected tower
///@param t reference of selected tower
///
void TowerManager::sell(const Tower & t)
{
	sell(t.getX(), t.getY());
}

///
///@brief Sells selected tower
///@param x x coordinate in squares
///@param y y coordinate in squares
///
void TowerManager::sell(int x, int y)
{
	remove(x, y);
	modified = true;
	m_iCash +=Tower::getPrice();
}

///
///@brief Upgrades selected tower
///
///Tower can be upgraded only if there are sufficient amount of cash
///@param t reference of selected tower
///@returns true if operation succeed, false otherwise
///
bool TowerManager::upgrade(const Tower & t)
{
	return upgrade(t.getX(), t.getY());
}

///
///@brief Upgrades selected tower
///
///Tower can be upgraded only if coordinates are proper and there are sufficient amount of cash
///@param x x coordinate in squares
///@param y y coordinate in squares
///@returns true if operation succeed, false otherwise
///
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

///
///@brief Gets tower from indicated location
///@param x x coordinate in squares
///@param y y coordinate in squares
///@returns tower reference
///@returns tower of (-1,-1) coords if found none in indicated location
///
Tower & TowerManager::get(int x, int y)
{
	for (auto it=tab.begin(); it != tab.end(); ++it)
	{
		if (it->getX() == x && it->getY() == y)
			return *it;
	}
	return Tower(-1, -1);
}

///
///@brief Gets tower of indicated index
///@param i tower index
///@returns tower reference
///
Tower & TowerManager::operator[](int i)
{
	return tab[i];
}

///
///@brief Checks if there is a tower in indicated coordinates
///@param x x coordinate in squares
///@param y y coordinate in squares
///@returns true if there is a tower in indicated location, false otherwise
///
bool TowerManager::isTower(int x, int y) const
{
	for (Tower t : tab)
	{
		if (t.getX() == x && t.getY() == y)
			return true;
	}
	return false;
}

///
///@brief Gets number of towers in collection
///@returns size of tower collection
///
int TowerManager::getSize() const
{
	return tab.size();
}

///
///@brief Updates TowerGraphic object with new towers state
///@param [in,out] tg reference to TowerGraphic object
///@returns true if there were new data to update, false otherwise
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

///
///@brief Increases cash amount
///@param v income
///
void TowerManager::AddCash(uint v)
{
	m_iCash += v;
}

///
///@brief Gets cash amount
///@returns cash amount
///
std::string TowerManager::GetCash() const
{
	return std::to_string(m_iCash);
}

///
///@brief Adds a tower to collection
///@param t tower
///
void TowerManager::add(Tower t)
{
	tab.push_back(t);
}

///
///@brief Removes tower from collection
///@param x x coordinate in squares
///@param y y coordinate in squares
///
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

///
///@brief Erases all towers from collection
///
void TowerManager::clear()
{
	tab.clear();
}
