#pragma once
#include <stdexcept>

class ParserIniExeption: public std::runtime_error {
public :
	ParserIniExeption(const int number_line, const std::string& error);
	ParserIniExeption(const std::string& error);
};
