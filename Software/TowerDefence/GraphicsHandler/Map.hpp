#pragma once
#include "Utils.hpp"
#include <array>
#include <vector>
#define CATCH_ALL catch(std::exception& e) {\
							std::cerr << e.what() << std::endl;\
							ReleaseResources();\
							return false;\
							}

class Point
{
public: enum TerrainType { TT_EMPTY, TT_PATH, TT_TOWER };
private:
	int m_x;
	int m_y;
	TerrainType m_TerrainType;
	std::array<bool, 4> m_directions;
	int UpdateDirectionRestrictions(int value);
public:
	explicit Point(int x = 0, int y = 0, int val = 0);
	enum Directions { Up, Right, Down, Left };
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
};

class Map
{
	int m_iWidth;
	int m_iHeight;
	std::vector<Point> tab;
public:
	explicit Map(int width, int height);
	explicit Map(int width, int height, const int* intMap);
	bool SetPoint(int x, int y, int newValue);
	bool SetPoint(Point p, int newValue);
	bool SetPoint(int x, int y, Point newPoint);
	bool ReplacePoint(Point oldPoint, Point newPoint);
	Point GetPoint(int x, int y) const;
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


class MapFileParser
{
	std::string m_sFilePath;
	std::ifstream m_File;
	int* m_pMapBase;
	int m_Width;
	int m_Height;
	void ReleaseResources();
	bool ReadDimension();
	bool ReadMap();
public:
	bool ParseFile();
	explicit MapFileParser(std::string sFilePath);
	Map parsedMap();
	~MapFileParser();

};

class RulesFileParser
{
	std::string m_sFilePath;
	std::ifstream m_File;

};