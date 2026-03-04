cmake_minimum_required(VERSION 3.20)
project(SnakeGame VERSION 1.0)

# SFML 3.0.0 requires modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Automatically fetch SFML 3.0.0 from GitHub
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0 # Points specifically to the 3.0.0 release
)
FetchContent_MakeAvailable(SFML)

# Tell CMake where our source files are
add_executable(SnakeGame src/main.cpp)

# Tell CMake where our header files are
target_include_directories(SnakeGame PRIVATE include)

# Link SFML libraries to our game
target_link_libraries(SnakeGame PRIVATE SFML::Graphics SFML::Window SFML::System)