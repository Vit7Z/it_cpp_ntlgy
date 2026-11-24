#pragma once
#include <pqxx/pqxx>
#include <string>
#include <map>

class DataBase {
public:
	DataBase(const std::string& idb);

	void AddKeywordLink(const std::map<std::string, unsigned int>& words, const std::string& link);
	bool CheckUrl(const std::string& url);
	bool CheckKeyword(const std::string& keyword);
	std::map<std::string, int> GetUrls(const std::string& keyword);

private:
	pqxx::connection conn_db_;
	void CreateDataBase();
};