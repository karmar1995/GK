#include "Utils.hpp"
#include <sstream>

///
///@brief constructor
///
Utils::Utils()
{
}

///
///@brief method used for splitting string
///@param string to split
///@param string separator
///
std::vector<std::string> Utils::split(std::string toSplit, std::string Separator)
{
	std::vector<std::string> splitted;
	std::size_t pos = 0;
	std::size_t newPos = 0;
	while (true)
	{
		newPos = toSplit.find(Separator, pos);
		std::string tmp(toSplit, pos, (newPos - pos));
		splitted.push_back(tmp);
		if (newPos == std::string::npos) break;
		pos = ++newPos;
	}
	return splitted;
}
