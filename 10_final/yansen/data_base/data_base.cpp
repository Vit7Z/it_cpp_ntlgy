#include "data_base.h"

DataBase::DataBase(const std::string& idb) :conn_db_{ pqxx::connection(idb) }
{
	CreateDataBase();
	conn_db_.prepare("add_keyword", "INSERT INTO keywords (keyword) VALUES ( $1 )");
	conn_db_.prepare("add_url", "INSERT INTO urls (url) VALUES ( $1 )");
	conn_db_.prepare("add_qty", "INSERT INTO keyword_urs_qty (id_keyword, id_url, quantity) VALUES ("
		"(SELECT id FROM keywords WHERE keyword = $1),"
		"(SELECT id FROM urls WHERE url = $2), $3)");
}

void DataBase::AddKeywordLink(const std::map<std::string, unsigned int>& words, const std::string& link) {
	//повторное добавление ссылки
	if (CheckUrl(link)) {
		return; 
	}

	pqxx::work tx{ conn_db_ };
	tx.exec_prepared("add_url", link);
	tx.commit();

	for (const auto& [key, value] : words) {
		if (!CheckKeyword(key)) {
			tx.exec_prepared("add_keyword", key);
			tx.commit();
		}
		tx.exec_prepared("add_qty", key, link, std::to_string(value));
	}
	tx.commit();
}

bool DataBase::CheckUrl(const std::string& url) {
	pqxx::work tx{ conn_db_ };
	bool check_id = false;
	check_id = tx.query_value<bool>("SELECT EXISTS(SELECT id FROM urls WHERE url = \'" + url + "\');");
	return check_id;
}

bool DataBase::CheckKeyword(const std::string& keyword) {
	pqxx::work tx{ conn_db_ };
	bool check_id = false;
	check_id = tx.query_value<bool>("SELECT EXISTS(SELECT id FROM keywords WHERE keyword = \'" + keyword + "\');");
	return check_id;
}

std::map<std::string, int> DataBase::GetUrls(const std::string& keyword) {
	pqxx::work tx{ conn_db_};
	std::map<std::string, int> result;
	std::string key_esc = tx.esc(keyword);

	for (auto [url, qty] : tx.query<std::string, int>
		("SELECT u.url, kuq.quantity "
			"FROM urls u "
			"JOIN keyword_urs_qty kuq ON u.id = kuq.id_url "
			"JOIN keywords k ON kuq.id_keyword = k.id "
			"WHERE k.keyword = '" + key_esc + "' "))
	{
		result[url] = qty;
	};
	return result;
}

void DataBase::CreateDataBase() {
	pqxx::work tx{ conn_db_ };

	tx.exec("CREATE TABLE IF NOT EXISTS keywords( "
		"id SERIAL PRIMARY KEY, "
		"keyword TEXT NOT NULL UNIQUE)"
	);

	tx.exec("CREATE TABLE IF NOT EXISTS urls( "
		"id SERIAL PRIMARY KEY, "
		"url TEXT NOT NULL UNIQUE)"
	);

	tx.exec("CREATE TABLE IF NOT EXISTS keyword_urs_qty( "
		"id_keyword INTEGER REFERENCES keywords(id), "
		"id_url INTEGER REFERENCES urls(id), "
		"quantity INTEGER NOT NULL, "
		"CONSTRAINT k_u PRIMARY KEY(id_keyword, id_url))"
	);
	tx.commit();
}
