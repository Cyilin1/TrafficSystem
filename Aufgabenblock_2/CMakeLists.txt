cmake_minimum_required(VERSION 3.14)
project(Block2)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/../Auf3)

file(GLOB Auf3_SRC ${CMAKE_SOURCE_DIR}/../Auf3/*.cpp)


# 设置 Boost 的路径
set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/../boost")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/../boost)

find_package(Boost 1.63.0 REQUIRED COMPONENTS system filesystem)  # 选择所需的Boost组件

if(Boost_FOUND)
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})  # 包含Boost头文件
    link_directories(${Boost_LIBRARY_DIRS})     # 链接Boost库文件
endif()

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
        Simulationsobject.h
        Simulationsobject.cpp
        Fahrzeugausnahme.h
        Fahrzeugausnahme.cpp
        Fahren.h
        Fahren.cpp
        Parken.h
        Parken.cpp
        vertagt_aktion.h
        vertagt_liste.h
        ${Auf3_SRC})
