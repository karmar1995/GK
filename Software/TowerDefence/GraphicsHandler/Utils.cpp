#include "Utils.hpp"
#include <sstream>

Utils::Utils()
{
}

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
