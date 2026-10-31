cmake_minimum_required(VERSION 4.3)
project(Zadanie_rekrutacyjne_SimBa_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Zadanie_rekrutacyjne_SimBa_main
        main.cpp
        Memory.cpp
        Memory.h
        TelemetryBlackBox.cpp
        TelemetryBlackBox.h)