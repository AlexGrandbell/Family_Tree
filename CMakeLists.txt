cmake_minimum_required(VERSION 3.25)
project(Family_Tree)

set(CMAKE_CXX_STANDARD 17)

add_executable(Family_Tree Main.cpp Exception.h Tool.cpp Tool.h BTree.h FamilyTreeSystem.cpp FamilyTreeSystem.h Menu.cpp Menu.h)
