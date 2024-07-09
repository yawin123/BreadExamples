cmake_minimum_required(VERSION 2.8.0)
set(CMAKE_CXX_FLAGS "-O3 -std=c++20")
project(BreadTest)

file(GLOB game_SRC
    "main.cpp"
)

add_executable(DataStoreTest ${game_SRC})

add_definitions(-DGLFW_INCLUDE_NONE)
find_library(BREAD_LIB BreadEngine)

target_link_libraries(
  DataStoreTest
  PUBLIC
  ${BREAD_LIB}
)
