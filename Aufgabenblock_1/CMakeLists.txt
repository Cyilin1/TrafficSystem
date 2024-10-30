cmake_minimum_required(VERSION 3.14)
project(untitled4)

set(CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(untitled4 main.cpp
        Fahrzeug.cpp
        Fahrzeug.h
        pkw.h
        pkw.cpp
        fahrrad.h
        fahrrad.cpp
        vertagt_aktion.h
        vertagt_liste.h)
