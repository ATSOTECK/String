cmake_minimum_required(VERSION 3.16)
project(String)

set(CMAKE_CXX_STANDARD 14)

include_directories(SkylerString)

add_executable(String
        SkylerString/main.cpp
        SkylerString/SkylerString.cpp
        SkylerString/SkylerString.hpp
        SkylerString/StringList.cpp
        SkylerString/StringList.hpp)
