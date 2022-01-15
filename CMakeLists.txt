cmake_minimum_required(VERSION 3.20)
project(blob_dash)

set(CMAKE_CXX_STANDARD 14)

add_executable(blob_dash main.cpp src/map.cpp src/input.cpp src/player.cpp)

set(SFML_STATIC_LIBRARY TRUE)
set(SFML_DIR D:/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics REQUIRED)

include_directories(D:/SFML-2.5.1/include)
target_link_libraries(blob_dash sfml-system sfml-window sfml-graphics)