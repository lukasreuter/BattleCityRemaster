cmake_minimum_required(VERSION 2.8.12)
project(BattleCity2018)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/modules/")

add_subdirectory(corrade)
add_subdirectory(magnum)
add_subdirectory(src)
