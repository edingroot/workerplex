cmake_minimum_required(VERSION 3.8)
project(workerplex)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.58.0 REQUIRED COMPONENTS filesystem thread)

link_directories(${Boost_INCLUDE_DIRS})

add_library(workerplex INTERFACE)
target_include_directories(workerplex INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(SOURCE_FILES
        src/main.cpp
        lib/workerplex/Workerplex.hpp
        lib/workerplex/Workerplex.cpp
        lib/workerplex/Worker.hpp
        src/workers/pingpong/PingPong.hpp
        src/workers/pingpong/PingPong.cpp
        src/workers/longtask/LongTask.cpp
        src/workers/longtask/LongTask.hpp)
add_executable(workerplex-demo ${SOURCE_FILES})

target_link_libraries(workerplex-demo workerplex ${Boost_LIBRARIES})
