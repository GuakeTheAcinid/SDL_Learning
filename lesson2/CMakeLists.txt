project(lesson2)
find_package(SDL2_image REQUIRED)


add_executable(lesson2 lesson2.cpp)
target_link_libraries(lesson2 PRIVATE SDL2 SDL2_image)

target_link_libraries(lesson2 PRIVATE ${SDL2_LIBRARY})