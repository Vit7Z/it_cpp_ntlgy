#pragma once
#include<fstream>
#include<map>

class ParserIni {
public:
  ParserIni() = delete;
  ParserIni(const std::string& file_name);
  ~ParserIni();

  std::string GetValue(const std::string& key);

private:
  std::ifstream file_;
  int current_read_line_ = 1;
  std::string current_section_ = "";
  std::string current_value_ = "";
  std::map<std::string, std::map<std::string, std::string>> value_;

  void ReadFile();
  void GetNameSection(std::string& read_name);
  void GetValue(std::string& read_name);
  void IgnoreSpaceToWord();
};