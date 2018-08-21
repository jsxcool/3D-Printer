cmake_minimum_required(VERSION 3.9)
project(improveVersion)

set(CMAKE_CXX_STANDARD 11)

add_executable(improveVersion main.cpp STL.hh Polyhedron.hh SliceAlgorithm.hh FillingAlgorithm.hh Gcode.hh)