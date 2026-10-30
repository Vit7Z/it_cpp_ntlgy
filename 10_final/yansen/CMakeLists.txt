cmake_minimum_required(VERSION 3.30.0)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(yansen LANGUAGES CXX)

# Определяем пути к исходникам
file(GLOB SOURCES "src/*.cpp")
set(libpqxx_DIR "C:/dev/libpqxx-7.10.3")

# PQXX
set(PostgreSQL_ADDITIONAL_VERSIONS "18")

add_subdirectory(${libpqxx_DIR} pqxx-build) 


# Исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} pqxx)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")