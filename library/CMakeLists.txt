cmake_minimum_required(VERSION 3.5)
project(workerplex)

set(CMAKE_CXX_STANDARD 14)

add_library(${PROJECT_NAME}
        workerplex/Workerplex.hpp
        workerplex/Workerplex.cpp
        workerplex/Worker.hpp
        workerplex/Exceptions.hpp
        workerplex/Exceptions.cpp)

# Boost library
find_package(Boost 1.58.0 REQUIRED COMPONENTS thread)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
