# Each lesson has it's CMakeLists.txt to build .exe for each of lesson
# and to store source of each lesson
project(lesson1)
find_package(SDL2_image REQUIRED)


add_executable(lesson1 lesson1.cpp)
target_link_libraries(lesson1 PRIVATE SDL2 SDL2_image)

target_link_libraries(lesson1 PRIVATE ${SDL2_LIBRARY})