#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <map>
#include <Windows.h>

#include "parser_ini.h"
#include "data_base.h"

int main(int argc, char* argv[])
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	try {
		ParserIni ini_file("../config.ini");

		std::cout << "DataBase.bd_host: " << ini_file.GetValue("DataBase.bd_host") << std::endl;
		std::cout << "DataBase.bd_host: " << ini_file.GetValue("DataBase.bd_port") << std::endl;
		std::cout << "DataBase.bd_host: " << ini_file.GetValue("DataBase.bd_name") << std::endl;
		std::cout << "DataBase.bd_host: " << ini_file.GetValue("DataBase.bd_user") << std::endl;
		std::cout << "DataBase.bd_host: " << ini_file.GetValue("DataBase.bd_pswd") << std::endl;

		 std::string initialize_connection_db("host=" + ini_file.GetValue("DataBase.bd_host") +
			 " port=" + ini_file.GetValue("DataBase.bd_port") +
			 " dbname=" + ini_file.GetValue("DataBase.bd_name") +
			 " user=" + ini_file.GetValue("DataBase.bd_user") +
			 " password=" + ini_file.GetValue("DataBase.bd_pswd"));

		 DataBase db(initialize_connection_db);

		
	}
	catch (std::exception const& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}