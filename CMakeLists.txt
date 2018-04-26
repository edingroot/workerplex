cmake_minimum_required(VERSION 3.8)
project(workerplex-demo)

add_subdirectory(lib)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/workers/pingpong/PingPong.hpp
        src/workers/pingpong/PingPong.cpp
        src/workers/longtask/LongTask.cpp
        src/workers/longtask/LongTask.hpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE lib)
target_link_libraries(${PROJECT_NAME} workerplex)
