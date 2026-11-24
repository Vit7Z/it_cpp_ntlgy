cmake_minimum_required(VERSION 3.30.0)

project(parser_ini)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_LIB "parser_ini.cpp" 
               "parser_ini.h" 
			         "parser_ini_exeption.h" 
			         "parser_ini_exeption.cpp")

add_library(parser_ini STATIC ${SOURCE_LIB})