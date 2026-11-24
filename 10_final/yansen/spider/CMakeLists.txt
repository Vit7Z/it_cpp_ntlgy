cmake_minimum_required(VERSION 3.30.0)

add_executable(SpiderApp
	main.cpp
	http_utils.h
	http_utils.cpp
	link.h
	)

target_compile_features(SpiderApp PRIVATE cxx_std_20) 

target_link_libraries(SpiderApp pqxx)

target_include_directories(SpiderApp PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(SpiderApp ${Boost_LIBRARIES})

target_link_libraries(SpiderApp OpenSSL::SSL)

target_include_directories(parser_ini PUBLIC "../parser_ini")

target_link_libraries(SpiderApp parser_ini)

target_include_directories(data_base PUBLIC "../data_base")

target_link_libraries(SpiderApp data_base)
