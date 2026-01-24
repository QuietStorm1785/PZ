cmake_minimum_required(VERSION 3.5)
project(AstarCpp)

set(ASTARCPP_SRC
    Astar.cpp
    AStar.cpp
    Node.h
    Grid.h
    ISearchNode.h
    IGoalNode.h
    ASearchNode.h
    ASearchNode.cpp
    IClosedSet.h
    IOpenSet.h
    ClosedSet.h
    ClosedSetHash.h
    OpenSet.h
    OpenSetHash.h
    HashPriorityQueue.h
    SearchNode2D.h
    SearchNode2D.cpp
    GoalNode2D.h
    GoalNode2D.cpp
    SearchNodeCity.h
    SearchNodeCity.cpp
    GoalNodeCity.h
    GoalNodeCity.cpp
)

add_library(astarcpp STATIC ${ASTARCPP_SRC})
target_include_directories(astarcpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
