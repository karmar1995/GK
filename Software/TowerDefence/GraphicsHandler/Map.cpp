#include "Map.hpp"
#include <iostream>

Map::Map(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	tab = std::vector <Point>();
	tab.reserve(width*height);
	InitializeEmptyMap();
}

Map::Map(int width, int height, const int* intMap)
{
	m_iWidth = width;
	m_iHeight = height;
	tab = std::vector <Point>();
	tab.reserve(width*height);
	InitializeMap(intMap);
}

void Map::InitializeMap(const int* intMap)
{
	for (int i = 0; i < m_iHeight; i++)
	{
		for (int j = 0; j < m_iWidth; j++)
		{
			tab.push_back(Point(j, i, intMap[CalculatePointIndex(j, i)]));
		}
	}
}

void Map::InitializeEmptyMap()
{
	for (int i = 0; i < m_iHeight; i++)
	{
		for (int j = 0; j < m_iWidth; j++)
			tab.push_back(Point(j, i));
	}
}

bool Map::SetPoint(int x, int y, int newValue)
{
	int index = CalculatePointIndex(x, y);
	if (IsInRange(index))
	{
		tab[index].SetTerrainType(newValue);
		return true;
	}
	return false;
}

bool Map::SetPoint(Point p, int newValue)
{
	return SetPoint(p.GetX(), p.GetY(), newValue);
}

bool Map::SetPoint(int x, int y, Point newPoint)
{
	int index = CalculatePointIndex(x, y);
	if (IsInRange(index))
	{
		tab[index] = newPoint;
		return true;
	}
	return false;
}

bool Map::ReplacePoint(Point oldPoint, Point newPoint)
{
	return SetPoint(oldPoint.GetX(), oldPoint.GetY(), newPoint);
}

//Important: In case of invalid coordinates, function returns point (x=-1, y=-1, value=-1) which is incorrect point in map. 
//Use IsInMap function before invoking this.
Point Map::GetPoint(int x, int y) const
{
	int index = CalculatePointIndex(x, y);
	if (IsInRange(index))
	{
		return tab[index];
	}
	return Point(-1, -1, -1);
}

Point Map::GetLastPoint() const
{
	return *(tab.end()-1);
}

int Map::GetWidth()
{
	return m_iWidth;
}

int Map::GetHeight()
{
	return m_iHeight;
}

bool Map::IsInMap(int x, int y) const
{
	if (x < 0 || y < 0)
		return false;
	return(IsInRange(CalculatePointIndex(x, y)));
}

bool Map::IsInMap(Point p) const
{
	return IsInMap(p.GetX(), p.GetY());
}


bool Map::IsInRange(int index) const
{
	return index >= 0 && index < tab.size();
}

int Map::CalculatePointIndex(Point p) const
{
	return CalculatePointIndex(p.GetX(), p.GetY());
}

int Map::CalculatePointIndex(int x, int y) const
{
	return y*m_iWidth + x;
}

void Map::Display() const
{
	for (int i = 0; i < m_iHeight; i++)
	{
		for (int j = 0; j < m_iWidth; j++)
		{
			std::cout << tab[i*m_iWidth + j].GetTerrainType();
		}
		std::cout << std::endl;
	}
}

Map::~Map()
{
}

Point::Point(int x, int y, int val)
{
	m_x = x;
	m_y = y;
	m_directions = { false, false, false, false };
	int terrainType = UpdateDirectionRestrictions(val);
	m_TerrainType = TerrainType(terrainType);
#ifdef _DEBUG
	std::cout << "x\ty\tup\tright\tdown\tleft" << std::endl;
	std::cout << m_x << "\t" << m_y <<"\t";
	for (bool flag : m_directions)
		std::cout << flag<<"\t";
	std::cout << std::endl << "end of point" << std::endl;
#endif
}
int Point::UpdateDirectionRestrictions(int value)
{
	if (value < 32)
		return value;
	int UpMask = 32;
	int RightMask = 64;
	int DownMask = 128;
	int LeftMask = 256;
	if (value & UpMask)
	{
		m_directions[Directions::Up] = static_cast<bool>(value & UpMask);
		value -= UpMask;
	}
	if (value & RightMask)
	{
		m_directions[Directions::Right] = static_cast<bool>(value & RightMask);
		value -= RightMask;
	}
	if (value & DownMask)
	{
		m_directions[Directions::Down] = static_cast<bool>(value & DownMask);
		value -= DownMask;
	}
	if (value & LeftMask)
	{
		m_directions[Directions::Left] = static_cast<bool>(value & LeftMask);
		value -= LeftMask;
	}
	return value;
}

int Point::GetX() const
{
	return m_x;
}

int Point::GetY() const
{
	return m_y;
}
Point::TerrainType Point::GetTerrainType() const
{
	return m_TerrainType;
}

void Point::SetTerrainType(int newValue)
{
	m_TerrainType = TerrainType(newValue);
}

void Point::SetTerrainType(TerrainType newValue)
{
	m_TerrainType = newValue;
}

bool Point::IsDownAllowed() const
{
	return m_directions[Directions::Down];
}

bool Point::IsUpAllowed() const
{
	return m_directions[Directions::Up];
}

bool Point::IsLeftAllowed() const
{
	return m_directions[Directions::Left];
}

bool Point::IsRightAllowed() const
{
	return m_directions[Directions::Right];
}

bool Point::SetDirection(bool val, Directions direction)
{
	m_directions[direction] = val;
	return m_directions[direction];
}

bool Point::AllowUp()
{
	return SetDirection(true, Directions::Up);
}
bool Point::AllowDown()
{
	return SetDirection(true, Directions::Down);
}
bool Point::AllowLeft()
{
	return SetDirection(true, Directions::Left);
}

bool Point::AllowRight()
{
	return SetDirection(true, Directions::Right);
}

bool Point::DisallowUp()
{
	return SetDirection(false, Directions::Up);
}

bool Point::DisallowDown()
{
	return SetDirection(false, Directions::Down);
}

bool Point::DisallowLeft()
{
	return SetDirection(false, Directions::Left);
}
bool Point::DisallowRight()
{
	return SetDirection(false, Directions::Right);
}

Point Point::GetNext() const
{
	int index = -1;
	for (int i = 0; i <= Directions::Left; i++)
	{
		if (m_directions[i])
			index < 0 ? index = i : index = (rand() % 2 == 0) ? i : index;
	}
	switch (index)
	{
	case Directions::Up:
		return Point(m_x, m_y - 1, 0);
	case Directions::Right:
		return Point(m_x + 1, m_y, 0);
	case Directions::Down:
		return Point(m_x, m_y+1, 0);
	case Directions::Left:
		return Point(m_x - 1, m_y, 0);
	default: break;
	}
	return Point(m_x, m_y, 0);
}

bool Point::operator==(const Point & rhv) const
{
	return this->m_x == rhv.m_x && this->m_y && rhv.m_y;
}

void MapFileParser::ReleaseResources()
{
	if (m_pMapBase != nullptr)
	{
		delete m_pMapBase;
		m_pMapBase = nullptr;
	}
	if (m_File.is_open())
		m_File.close();
}

MapFileParser::MapFileParser(std::string sFilePath)
{
	m_pMapBase = nullptr;
	m_File.open(sFilePath);
	if (!m_File.good())
	{
		ReleaseResources();
		throw CustomException(std::string("Unable to open file"));
	}
}

Map MapFileParser::parsedMap()
{
	if (!ParseFile())
	{
		ReleaseResources();
		throw CustomException(std::string("Unable to parse file"));
	}
	return Map(m_Width, m_Height, m_pMapBase);
}

MapFileParser::~MapFileParser()
{
	ReleaseResources();
}

bool MapFileParser::ParseFile()
{
	if (!ReadDimension())
		return false;
	if (!ReadMap())
		return false;
	return true;
}
bool MapFileParser::ReadDimension()
{
	std::string sLine;
	std::getline(m_File, sLine);
	std::vector<std::string> splitted = Utils::split(sLine);
	if (splitted.size() != 2)
		return false;
	try
	{
		m_Width = std::stoi(splitted[0]);
		m_Height = std::stoi(splitted[1]);
	}
	catch (std::invalid_argument)
	{
		std::cerr << "Invalid dimension" << std::endl;
		ReleaseResources();
		return false;
	}
	catch (std::out_of_range)
	{
		std::cerr << "Invalid dimension" << std::endl;
		ReleaseResources();
		return false;
	}
	CATCH_ALL
	return true;
}
bool MapFileParser::ReadMap()
{
	try
	{
		int count = m_Height * m_Width;
		m_pMapBase = new int[count];
		std::string tmp;
		int counter = 0;
		for (int i = 0; !(m_File.eof()); i++)
		{
			m_File >> tmp;
			counter++;
			if(i<count)
				m_pMapBase[i] = stoi(tmp);
			if (m_pMapBase[i] < 0)
				throw CustomException(std::string("Invalid element"));
		}
		if (counter != count)
			throw CustomException(std::string("Invalid map"));
	}
	catch (std::invalid_argument)
	{
		std::cerr << "Invalid map element" << std::endl;
		ReleaseResources();
		return false;
	}
	catch (std::out_of_range)
	{
		std::cerr << "Invalid map element" << std::endl;
		ReleaseResources();
		return false;
	}
	CATCH_ALL
	return true;
}