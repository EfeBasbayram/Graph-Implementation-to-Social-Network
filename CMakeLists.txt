cmake_minimum_required(VERSION 3.25)
project(211TermProject)

set(CMAKE_CXX_STANDARD 17)

# Add executable and specify source files
add_executable(untitled main.cpp utils.cpp Graph.cpp Person.cpp)

# Include directory for header files (adjust path as needed)
include_directories(include)

