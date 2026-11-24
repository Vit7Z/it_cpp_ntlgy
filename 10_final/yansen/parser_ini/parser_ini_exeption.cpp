#include "parser_ini_exeption.h"
#include <string>

ParserIniExeption::ParserIniExeption(const int number_line, const std::string& error)
	:runtime_error("Error format ini file from " + std::to_string(number_line) + " line. " + error)
{}

ParserIniExeption::ParserIniExeption(const std::string & error)
	:runtime_error("Error ini file: " + error)
{}

