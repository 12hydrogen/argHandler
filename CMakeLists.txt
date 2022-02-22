cmake_minimum_required(VERSION 3.7)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

set(CMAKE_INSTALL_PREFIX "./")

project(argHandler)
include_directories(include)

aux_source_directory(. ROOT_DIR)
add_library(ArgHandler ${ROOT_DIR})

install(TARGETS ArgHandler DESTINATION "../")
install(FILES "./include/argHandler.hpp" DESTINATION "../include")
