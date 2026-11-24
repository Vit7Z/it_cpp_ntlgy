cmake_minimum_required(VERSION 3.30.0)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(yansen LANGUAGES CXX)

set(OPENSSL_ROOT_DIR "C:/dev/OpenSSL-Win64")
set(BOOST_ROOT "C:/dev/boost_1_92_0")
set(libpqxx_DIR "C:/dev/libpqxx-7.10.3")

add_compile_definitions(_WIN32_WINNT=0x0A01)

# Boost:
find_package(Boost 1.92.0 REQUIRED COMPONENTS system thread locale)

# PQXX
set(PostgreSQL_ADDITIONAL_VERSIONS "18")
add_subdirectory(${libpqxx_DIR} libpqxx-build) 

# OpenSSL
find_package(OpenSSL REQUIRED)

add_subdirectory(data_base)
add_subdirectory(parser_ini)
add_subdirectory(spider)
add_subdirectory(http_server)





# Исполняемый файл
#add_executable(${PROJECT_NAME} ${SOURCES})

#target_link_libraries(${PROJECT_NAME} pqxx)

#target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")