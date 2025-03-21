# don't fucking know how to make CMakeLists.txt
# But what I know is that the program may be built by executing this:

# v v v v v
# g++ -Isrc/include/SDL2 -Lsrc/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
# ^ ^ ^ ^ ^
# g++ -o main main.cpp -lmingw32 -lSDL2main -lSDL2

# What it does:
#
# runs g++
# -Includes src/include/SDL2
# says -Library is in src/lib
# and -output file is named main, taken from main.cpp
# and we especially search for -libraries like:
# mingw32
# SDL2main
# SDL2

# ALSO important. There are x64 SDL in this project. Due to using mingw x64
# cuz I'm very tired to fix it yet.
# if we put x32 SDL into project, it won't build of course.

# So. Knowing CMake it's most probably easy to make CMakeLists.txt out of given flags

cmake_minimum_required(VERSION 3.10)
project(SDLLearning)

set(SDL2_PATH "C:\\msys64\\mingw64") # ПУТЬ К ВАШЕЙ SDL БИБЛИОТЕКЕ
#set(SDL2_image_PATH "C:\\msys64\\mingw64")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SDLLearning_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

#target_link_libraries(SDLLearning ${SDL2_LIBRARY})
add_subdirectory(lesson0)
add_subdirectory(lesson2)
add_subdirectory(lesson3)
add_subdirectory(lesson4)
add_subdirectory(lesson5)
add_subdirectory(lesson6)
add_subdirectory(lesson7)
add_subdirectory(lesson8)
add_subdirectory(lesson9)
add_subdirectory(lesson10)
add_subdirectory(lesson11)
add_subdirectory(lesson12)