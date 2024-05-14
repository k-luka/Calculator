cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Calculator)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "Calculator/opt/homebrew/Cellar/sfml")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(Calculator main.cpp
        UserInterface.h
)
target_link_libraries(Calculator sfml-system sfml-window sfml-graphics sfml-audio)
