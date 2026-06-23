cmake_minimum_required(VERSION 4.2)
project(SpaceGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SpaceGame main.cpp)
target_link_libraries(SpaceGame SplashKit)