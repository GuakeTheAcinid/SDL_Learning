project(lesson9)
find_package(SDL2_image REQUIRED)


set(SOURCE_LIB ../lesson9/sdl_base_lesson9.cpp)
add_library(sdl_base_lesson9 STATIC ${SOURCE_LIB})

target_link_libraries(sdl_base_lesson9 PRIVATE SDL2 SDL2_image)
target_link_libraries(sdl_base_lesson9 PRIVATE ${SDL2_LIBRARY})

add_executable(lesson9 lesson9.cpp)

target_link_libraries(lesson9 PRIVATE sdl_base_lesson9)