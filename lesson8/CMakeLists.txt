project(lesson8)
find_package(SDL2_image REQUIRED)


set(SOURCE_LIB ../lesson8/sdl_base_lesson8.cpp)
add_library(sdl_base_lesson8 STATIC ${SOURCE_LIB})

target_link_libraries(sdl_base_lesson8 PRIVATE SDL2 SDL2_image)
target_link_libraries(sdl_base_lesson8 PRIVATE ${SDL2_LIBRARY})

add_executable(lesson8 lesson8.cpp)

target_link_libraries(lesson8 PRIVATE sdl_base_lesson8)