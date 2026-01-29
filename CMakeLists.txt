cmake_minimum_required(VERSION 3.15)
project(hyperTrader LANGUAGES CXX)

# Force C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optimizations
if(MSVC)
  add_compile_options(/W4 /O2)
else()
  add_compile_options(-O3 -march=native -Wall -Wextra -Werror)
endif()

#Testing
enable_testing()

# Project Structure
include_directories(src)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(hyperTrader ${SOURCES})

# Networking & Threads
find_package(Threads REQUIRED)
target_link_libraries(hyperTrader PRIVATE Threads::Threads)
