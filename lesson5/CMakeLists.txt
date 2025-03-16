project(lesson5)
find_package(SDL2_image REQUIRED)


set(SOURCE_LIB ../lesson5/sdl_base_lesson5.cpp)
add_library(sdl_base_lesson5 STATIC ${SOURCE_LIB})

target_link_libraries(sdl_base_lesson5 PRIVATE SDL2 SDL2_image)
target_link_libraries(sdl_base_lesson5 PRIVATE ${SDL2_LIBRARY})

add_executable(lesson5 lesson5.cpp)

target_link_libraries(lesson5 PRIVATE sdl_base_lesson5)