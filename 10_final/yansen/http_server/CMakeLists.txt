cmake_minimum_required(VERSION 3.30.0)

add_executable(HttpServerApp 
	main.cpp
	http_connection.h
	http_connection.cpp
	)

target_compile_features(HttpServerApp PRIVATE cxx_std_20) 

target_link_libraries(HttpServerApp pqxx)  

target_include_directories(HttpServerApp PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(HttpServerApp ${Boost_LIBRARIES})

target_link_libraries(HttpServerApp OpenSSL::SSL)

target_include_directories(parser_ini PUBLIC "../parser_ini")

target_link_libraries(HttpServerApp parser_ini)

target_include_directories(data_base PUBLIC "../data_base")

target_link_libraries(HttpServerApp data_base)
