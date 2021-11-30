cmake_minimum_required(VERSION 3.20)
project(ECS)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        main.cpp
        EntityManager.cpp)

set(HEADER_FILES
        EntityManager.hpp)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})