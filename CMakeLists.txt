cmake_minimum_required(VERSION 3.15)
project(hyprTrader LANGUAGES CXX)

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

add_executable(hyprTrader ${SOURCES})

# Networking & Threads
find_package(Threads REQUIRED)
target_link_libraries(hyprTrader PRIVATE Threads::Threads)

# Benchmark config
find_package(benchmark REQUIRED)

add_executable(hyprTrader_bench benchmarks/MatchingEngineBenchmark.cpp)
target_link_libraries(hyprTrader_bench PRIVATE benchmark::benchmark)
