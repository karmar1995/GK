#include "Map.hpp"
#include <iostream>



///
///@brief constructor
///
///@params map's width
///@params  map's height
///
Map::Map(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	tab = std::vector <Point>();
	tab.reserve(width*height);
	InitializeEmptyMap();
}


///
///@brief constructor
///
///@param map's width
///@param  map's height
///@param pointer used for map initialization
///
Map::Map(int width, int height, const int* intMap)
{
	m_iWidth = width;
	m_iHeight = height;
	tab = std::vector <Point>();
	tab.reserve(width*height);
	InitializeMap(intMap);
}


///
///@brief map initialization
///Method iterates through width and height and add's points to the collection
///@params pointer used for map initialization
///
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


///
///@brief empty map initialization
///Method iterates through width and height and add's empty points to the collection
///
void Map::InitializeEmptyMap()
{
	for (int i = 0; i < m_iHeight; i++)
	{
		for (int j = 0; j < m_iWidth; j++)
			tab.push_back(Point(j, i));
	}
}

///
///@brief Method used for setting points with new value
///Method checks if index of point's is in range, if so-it set's terrain with new value and returns true
///@params x dimension
///@params y dimension
///@params new value
///@returns true if index is in range
///
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

///
///@brief Method used for setting points with new value
///Method sets map points with logical point x,y and new value
///@params point
///@params new value
///@returns true if point was in range
///
bool Map::SetPoint(Point p, int newValue)
{
	return SetPoint(p.GetX(), p.GetY(), newValue);
}


///
///@brief Method used for setting points with new value
///Method sets map points with new point. it calculates index from x and y and if it is in range-it returns true
///@params x
///@params y
///@params new point
///@returns true if index is in range
///
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

///
///@brief Method used for replacing old point with new point
///@params old point
///@params new point replacing old one
///@returns true if points was set successfully 
///
bool Map::ReplacePoint(Point oldPoint, Point newPoint)
{
	return SetPoint(oldPoint.GetX(), oldPoint.GetY(), newPoint);
}
///
///Important: In case of invalid coordinates, function returns point (x=-1, y=-1, value=-1) which is incorrect point in map. 
///Use IsInMap function before invoking this.
///
Point Map::GetPoint(int x, int y) const
{
	int index = CalculatePointIndex(x, y);
	if (IsInRange(index))
	{
		return tab[index];
	}
	return Point(-1, -1, -1);
}


///
///@brief getter for last point
///@returns last point in collection
///
Point Map::GetLastPoint() const
{
	return *(tab.end()-1);
}

///
///@brief getter for map's width
///@returns map's width
///
int Map::GetWidth()
{
	return m_iWidth;
}

///
///@brief getter for map's height
///@returns map's height
///
int Map::GetHeight()
{
	return m_iHeight;
}

///
///@brief Method used for checking if point is on the map
//@param x
//@param y
///@returns false if point(x,y) is not on the map
///
bool Map::IsInMap(int x, int y) const
{
	if (x < 0 || y < 0)
		return false;
	return(IsInRange(CalculatePointIndex(x, y)));
}


///
///@brief Method used for checking if point is on the map
//@param point
///@returns false if point(x,y) is not on the map
///
bool Map::IsInMap(Point p) const
{
	return IsInMap(p.GetX(), p.GetY());
}

///
///@brief Method used for checking if point is in range
///@param index
///@returns true if index is greater than 0 and lower than collection's size
///
bool Map::IsInRange(int index) const
{
	return index >= 0 && index < tab.size();
}

///
///@brief Method used for calculating point index according to x and y
///@param point
///@returns point's index
///
int Map::CalculatePointIndex(Point p) const
{
	return CalculatePointIndex(p.GetX(), p.GetY());
}

///
///@brief Method used for calculating point index
///@param x
///@param y
///@returns point's index
///
int Map::CalculatePointIndex(int x, int y) const
{
	return y*m_iWidth + x;
}

///
///@brief Method used for displaying information about point on std output
///
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


///
///@brief destructor
///
Map::~Map()
{
}


///
///@brief Point constructor
///@param x
///@param y
///@param value
///
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


///
///@brief Method used for updating directions
///@param x
///@param value
///
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


///
///@brief getter for point's x coordinate
///@returns x value
///
int Point::GetX() const
{
	return m_x;
}


///
///@brief getter for point's y coordinate
//@returns y value
///
int Point::GetY() const
{
	return m_y;
}


///
///@brief getter for point's  terrain type
///@returns terrain type
///
Point::TerrainType Point::GetTerrainType() const
{
	return m_TerrainType;
}

///
///@brief setter for point's  terrain type index
///@param terrain type number
///
void Point::SetTerrainType(int newValue)
{
	m_TerrainType = TerrainType(newValue);
}

///
///@brief setter for point's  terrain type
///@param terrain type 
///
void Point::SetTerrainType(TerrainType newValue)
{
	m_TerrainType = newValue;
}

///
///@brief checks if move in down direction is allowed
///@returns logical indicating whether move in down direction is allowed
///
bool Point::IsDownAllowed() const
{
	return m_directions[Directions::Down];
}

///
///@brief checks if move in up direction is allowed
///@returns logical indicating whether move in up direction is allowed
///
bool Point::IsUpAllowed() const
{
	return m_directions[Directions::Up];
}


///
///@brief checks if move in left direction is allowed
///@returns logical indicating whether move in left direction is allowed
///
bool Point::IsLeftAllowed() const
{
	return m_directions[Directions::Left];
}


///
///@brief checks if move in right direction is allowed
//@returns logical indicating whether move in right direction is allowed
//
bool Point::IsRightAllowed() const
{
	return m_directions[Directions::Right];
}


///
///@brief set possibility of move in chosen direction
///@returns logical whether move in chosen direction is allowed
///
bool Point::SetDirection(bool val, Directions direction)
{
	m_directions[direction] = val;
	return m_directions[direction];
}

///
///@brief set possibility of move in up direction
///@returns logical whether move in up direction was allowed
///
bool Point::AllowUp()
{
	return SetDirection(true, Directions::Up);
}

///
///@brief set possibility of move in down direction
//@returns logical whether move in down direction was allowed
//
bool Point::AllowDown()
{
	return SetDirection(true, Directions::Down);
}

///
///@brief set possibility of move in left direction
///@returns logical whether move in left direction was allowed
///
bool Point::AllowLeft()
{
	return SetDirection(true, Directions::Left);
}

///
///@brief set possibility of move in right direction
///@returns logical whether move in right direction was allowed
///
bool Point::AllowRight()
{
	return SetDirection(true, Directions::Right);
}


///
///@brief makes move in up direction impossible
///@returns logical whether move in up direction wasn't allowed
///
bool Point::DisallowUp()
{
	return SetDirection(false, Directions::Up);
}

///
///@brief makes move in down direction impossible
///@returns logical whether move in down direction wasn't  allowed
///
bool Point::DisallowDown()
{
	return SetDirection(false, Directions::Down);
}


///
///@brief makes move in left direction impossible
///@returns logical whether move in left direction wasn't  allowed
///
bool Point::DisallowLeft()
{
	return SetDirection(false, Directions::Left);
}

///
///@brief makes move in right direction impossible
///@returns logical whether move in right direction wasn't  allowed
///
bool Point::DisallowRight()
{
	return SetDirection(false, Directions::Right);
}


///
///@brief  Get next point 
///@returns point with specific coordinates and value
///
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


///
///@brief  overloaded comparison operator
///@returns logical indicating whether two points coordinates are equal
///
bool Point::operator==(const Point & rhv) const
{
	return this->m_x == rhv.m_x && this->m_y && rhv.m_y;
}

///
///@brief method used for releasing resources
///
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

///
///@brief constructor of file parser
///@param filename
///
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


///
///@brief getter for parsed map
///@returns Map
///@throws CustomException indicating that file wasn't successfully read
///
Map MapFileParser::parsedMap()
{
	if (!ParseFile())
	{
		ReleaseResources();
		throw CustomException(std::string("Unable to parse file"));
	}
	return Map(m_Width, m_Height, m_pMapBase);
}
///
///@brief destructor
///
MapFileParser::~MapFileParser()
{
	ReleaseResources();
}

///
///@brief method used for parsing file
///@returns logical indicating whether reading map and dimensions were succesfull
///
bool MapFileParser::ParseFile()
{
	if (!ReadDimension())
		return false;
	if (!ReadMap())
		return false;
	return true;
}

///
///@brief method used for reading the dimensions
///@returns logical indicating whether reading  dimensions was succesfull
///
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

///
///@brief method used for reading the map
///@returns logical indicating whether reading  map was succesfull
///
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