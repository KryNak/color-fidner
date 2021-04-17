cmake_minimum_required(VERSION 3.15)
project(ColorFinder)

set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR "D:/Narzedzia/SFML-2.5.0-windows-gcc-7.3.0-mingw-32-bit/SFML-2.5.0/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window network graphics audio)
add_executable(ColorFinder main.cpp)
target_link_libraries(ColorFinder sfml-window sfml-system sfml-graphics sfml-audio)
