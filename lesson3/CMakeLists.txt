project(lesson3)
find_package(SDL2_image REQUIRED)


# now it sets source libs
set(SOURCE_LIB ../lesson3/sdl_base_lesson3.cpp)
add_library(sdl_base_lesson3 STATIC ${SOURCE_LIB})

target_link_libraries(sdl_base_lesson3 PRIVATE SDL2 SDL2_image)
target_link_libraries(sdl_base_lesson3 PRIVATE ${SDL2_LIBRARY})

add_executable(lesson3 lesson3.cpp)

target_link_libraries(lesson3 PRIVATE sdl_base_lesson3)