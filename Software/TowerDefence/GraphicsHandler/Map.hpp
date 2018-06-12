#pragma once
#include "Utils.hpp"
#include <array>
#include <vector>
#define CATCH_ALL catch(std::exception& e) {\
							std::cerr << e.what() << std::endl;\
							ReleaseResources();\
							return false;\
							}

///
///@brief Class representing logical points of the map
///
class Point
{
public: enum TerrainType { TT_EMPTY, TT_PATH, TT_TOWER }; //possible terrain types
		enum Directions { Up, Right, Down, Left  //possible directions 
		};
		Directions operator++(int r) { return Directions(r + 1); }

private:
	int m_x;  //x coordinate
	int m_y;  //y coordinate
	int m_allowedDirections; //which directions are allowed
	TerrainType m_TerrainType; //type of terrain
	std::array<bool, 4> m_directions; //describes directions 
	int UpdateDirectionRestrictions(int value);
public:
	explicit Point(int x = 0, int y = 0, int val = 0);
	int GetX() const;
	int GetY() const;
	TerrainType GetTerrainType() const;
	void SetTerrainType(int newValue);
	void SetTerrainType(TerrainType newValue);
	bool IsUpAllowed() const;
	bool IsLeftAllowed() const;
	bool IsDownAllowed() const;
	bool IsRightAllowed() const;
	bool SetDirection(bool val, Directions direction);
	bool AllowUp();
	bool AllowDown();
	bool AllowLeft();
	bool AllowRight();
	bool DisallowUp();
	bool DisallowDown();
	bool DisallowLeft();
	bool DisallowRight();
	Point GetNext() const;
	bool operator== (const Point& rhv) const;
};


///
///@brief Class representing sets of points as a map
///
class Map
{ 
	int m_iWidth; //describes map's width 
	int m_iHeight; //describes map's height 
	std::vector<Point> tab; //container for points of the map
public:
	explicit Map(int width, int height);
	explicit Map(int width, int height, const int* intMap);
	bool SetPoint(int x, int y, int newValue);
	bool SetPoint(Point p, int newValue);
	bool SetPoint(int x, int y, Point newPoint);
	bool ReplacePoint(Point oldPoint, Point newPoint);
	Point GetPoint(int x, int y) const;
	Point GetLastPoint() const;
	int GetWidth();
	int GetHeight();
	bool IsInMap(Point p ) const;
	bool IsInMap(int x, int y) const;
	~Map();
	void Display() const;
private:
	void InitializeMap(const int* tab);
	void InitializeEmptyMap();
	int CalculatePointIndex(Point p) const;
	int CalculatePointIndex(int x, int y) const;
	bool IsInRange(int index) const;
};

///
///@brief Class used for parsing file containing map's settings
///
class MapFileParser
{
	std::string m_sFilePath; //describes map's file path 
	std::ifstream m_File; //describes file
	int* m_pMapBase; //pointer to array of integers used for map creation
	int m_Width; //describes map's width 
	int m_Height; //describes map's height 
	void ReleaseResources();
	bool ReadDimension();
	bool ReadMap();
public:
	bool ParseFile();
	explicit MapFileParser(std::string sFilePath);
	Map parsedMap();
	~MapFileParser();

};

///
///@brief Class used for parsing file containing rule's settings
///
class RulesFileParser
{
	std::string m_sFilePath; // file's path 
	std::ifstream m_File; 

};