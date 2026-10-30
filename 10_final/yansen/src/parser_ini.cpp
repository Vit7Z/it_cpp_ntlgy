#include <iostream>
#include <regex>

#include "parser_ini.h"
#include "parser_exeption.h"

#define ALLOWED_CHAR_NAME "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890_-"

ParserIni::ParserIni(const std::string& file_name) {
	file_.open(file_name);
	if (!file_.is_open()) {
		throw std::ios_base::failure("Ini file not open");
	}
	else {
		ReadFile();
	}
}

ParserIni::~ParserIni() {
  if (file_.is_open()) {
    file_.close();
  }
}

std::string ParserIni::GetValue(const std::string& key) {
	int position_dot = key.find('.');

	if(position_dot != std::string::npos) {
		std::string name_section = key.substr(0, position_dot);
		std::string name_value = key.substr(position_dot + 1, key.length());

		if(!value_[name_section][name_value].empty()) {
			return value_[name_section][name_value];
		}
		else {
			throw ParserIniExeption("ѕустое значение.");
		}
	}
	else {
		throw ParserIniExeption("Format key for get value don't have '.'.");
	}
}

void ParserIni::ReadFile() {
	std::string word_from_ini;
	bool next_read_not_error = true;

  do {
    do {       // чтение строки
      file_ >> word_from_ini;

      if (word_from_ini.at(0) == ';' ||
        word_from_ini.at(0) == '#') { //проверка на коментарий
        file_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        file_.unget();
      }
      else if (next_read_not_error) {
        if (word_from_ini.at(0) == '[') { //—екци€
          GetNameSection(word_from_ini);
          next_read_not_error = false;
        } 
				else if ((word_from_ini.at(0) >= 'A' && word_from_ini.at(0) <= 'Z') || 
					(word_from_ini.at(0) >= 'a' && word_from_ini.at(0) <= 'z')) { //значение
          GetValue(word_from_ini);
          next_read_not_error = false;
        }
      }
      else {
        throw ParserIniExeption(current_read_line_, "Format file error!");
      }
      IgnoreSpaceToWord();
    } while (file_.peek() != '\n' && !file_.eof());
    ++current_read_line_;
    next_read_not_error = true;
  } while (!file_.eof());
}

void ParserIni::GetNameSection(std::string& read_name) {
	int close_char = read_name.find(']');

//после закрыти€ скобки секции сразу может начинатьс€ коментарий без пробела
	if (close_char != std::string::npos) {
		if (close_char == (read_name.length() - 1) || 
			read_name.at(close_char + 1) == ';' || 
			read_name.at(close_char + 1) == '#') {
			read_name.erase(close_char);
			read_name.erase(0, 1);
			if (read_name.find_first_not_of(ALLOWED_CHAR_NAME) == std::string::npos) {
				current_section_ = read_name;
				value_[current_section_];
			}
			else {
				throw ParserIniExeption(current_read_line_, "Name section contains invalid characters.");
			}
		}
		else {
			throw ParserIniExeption(current_read_line_, "Format name section error.");
		}
	}
	else {
		throw ParserIniExeption(current_read_line_, "Section not close (not ']').");
	}
}

void ParserIni::GetValue(std::string& read_name) {
	std::string word_from_ini;
	int eq_position = read_name.find('=');

	if (eq_position == std::string::npos) {//знак '=' отделен пробелом от имени
		if (read_name.find_first_not_of(ALLOWED_CHAR_NAME) == 
			std::string::npos) {
			current_value_ = read_name;
			file_ >> word_from_ini;

			if (word_from_ini.at(0) == '=') {
				if(word_from_ini.length() == 1) { // после = есть пробел
				
					IgnoreSpaceToWord();
					if(file_.peek() != '\n' && !file_.eof()) {//знак = отделен пробелом от значени€
						file_ >> word_from_ini;
						value_[current_section_][current_value_] = word_from_ini;
					} 
					else {
						throw ParserIniExeption(current_read_line_, current_value_ + " have not value.");
					}
				}
				else {//знак = прилип к значению
					word_from_ini.erase(0,1);
					value_[current_section_][current_value_] = word_from_ini;
				}
			}
			else {
				throw ParserIniExeption(current_read_line_, "Format line value error (not '=').");
			}
		}
		else {
			throw ParserIniExeption(current_read_line_, "Name value contains invalid characters.");
		}
	}
	else {
		current_value_ = read_name.substr(0, eq_position);
		//знак '=' последний в значении
		if (read_name.length() == eq_position + 1) {
			file_ >> word_from_ini;
			value_[current_section_][current_value_] = word_from_ini;
		}
		//знак '=' посередине
		else {
			value_[current_section_][current_value_] = read_name.substr(eq_position + 1, read_name.length() - eq_position);
		}
	}
}

void ParserIni::IgnoreSpaceToWord() {
	while (file_.peek() == ' ' || file_.peek() == '\t') {
		file_.get();
	}
}