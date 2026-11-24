#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
//#include <Windows.h>
#include <map>

#include "http_connection.h"
#include "parser_ini.h"
#include "data_base.h"

// "Loop" forever accepting new connections.
void httpServer(tcp::acceptor& acceptor, tcp::socket& socket, DataBase& db) {
	acceptor.async_accept(socket,
		[&](beast::error_code ec) {
			if (!ec)
				std::make_shared<HttpConnection>(std::move(socket), &db)->start();
			httpServer(acceptor, socket, db);
		});
}

int main(int argc, char* argv[])
{
	//SetConsoleCP(CP_UTF8);
	//SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_ALL, "ru_RU.utf-8");

	try
	{
		ParserIni ini_file("d:/Documents/cpp_prj/yansen/config.ini");

		std::cout << "DataBase.bd_host: " << ini_file.GetValue("DataBase.bd_host") << std::endl;

		std::string initialize_connection_db(
			"host=" + ini_file.GetValue("DataBase.bd_host") +
			" port=" + ini_file.GetValue("DataBase.bd_port") +
			" dbname=" + ini_file.GetValue("DataBase.bd_name") +
			" user=" + ini_file.GetValue("DataBase.bd_user") +
			" password=" + ini_file.GetValue("DataBase.bd_pswd"));

		DataBase db(initialize_connection_db);

		unsigned short port = static_cast<unsigned short>(std::stoi(ini_file.GetValue("Server.server_port")));
		auto const address = net::ip::make_address("0.0.0.0");

		net::io_context ioc{1};

		tcp::acceptor acceptor{ioc, { address, port }};
		tcp::socket socket{ioc};
		httpServer(acceptor, socket, db);

		std::cout << "Open browser and connect to http://localhost:" <<  port << " to see the web server operating" << std::endl;

		ioc.run();
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}