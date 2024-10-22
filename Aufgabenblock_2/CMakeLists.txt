cmake_minimum_required(VERSION 3.14)
project(Block2)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/../Auf3)

file(GLOB Auf3_SRC ${CMAKE_SOURCE_DIR}/../Auf3/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(Block2 main.cpp
        Fahrzeug.cpp
        Fahrzeug.h
        pkw.h
        pkw.cpp
        Weg.h
        Weg.cpp
        Verhalten.h
        Verhalten.cpp
        fahrrad.h
        fahrrad.cpp
        Simulationsobjekt.h
        Simulationsobjekt.cpp
        Fahrzeugausnahme.h
        Fahrzeugausnahme.cpp
        Fahren.h
        Fahren.cpp
        Parken.h
        Parken.cpp
        ${Auf3_SRC})
