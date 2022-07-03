cmake_minimum_required(VERSION 3.10)

# Project name
project(httpParser VERSION 1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Cmake install path
set(CMAKE_INSTALL_PATH "$ORIGIN/../lib")

# Executable
add_executable(httpParser Source.cpp HttpRequest.cpp)

target_include_directories(httpParser PUBLIC
                    "$(PROJECT_BINARY_DIR)"
                    )


install(TARGETS httpParser DESTINATION bin)