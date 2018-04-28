cmake_minimum_required(VERSION 3.5)
project(workerplex-demo)

add_subdirectory(library)

# If this is not a sub-project
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    set(CMAKE_CXX_STANDARD 11)

    set(SOURCE_FILES
            src/main.cpp
            src/workers/pingpong/PingPong.hpp
            src/workers/pingpong/PingPong.cpp
            src/workers/longtask/LongTask.cpp
            src/workers/longtask/LongTask.hpp)
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
    target_link_libraries(${PROJECT_NAME} workerplex)
endif()
