#pragma once
#include <exception>
#include <vector>
#include <string>
#include <fstream>
typedef unsigned int uint;

///
///@brief Class used for providing useful functionality
///
class Utils
{
	Utils();
public:
	static std::vector<std::string> split(std::string toSplit, std::string Separator= " ");
};

///
///@brief Class used for providing custom exceptions
///
class CustomException : public std::exception
{
	std::string message;
public:
	CustomException(std::string message)
	{
		this->message = message;
	}
	virtual const char* what() const throw()
	{
		return message.c_str();
	}
};
