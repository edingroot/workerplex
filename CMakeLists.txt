cmake_minimum_required(VERSION 3.8)
project(workerplex)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.58.0 REQUIRED COMPONENTS filesystem thread)

link_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES
        src/main.cpp
        src/workerplex/Workerplex.hpp
        src/workerplex/Workerplex.cpp
        src/workerplex/workers/Worker.hpp
        src/workerplex/workers/PingPong.hpp
        src/workerplex/workers/PingPong.cpp)
add_executable(workerplex ${SOURCE_FILES})

target_link_libraries(workerplex ${Boost_LIBRARIES})
