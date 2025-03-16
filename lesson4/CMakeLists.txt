project(lesson4)
find_package(SDL2_image REQUIRED)


set(SOURCE_LIB ../lesson4/sdl_base_lesson4.cpp)
add_library(sdl_base_lesson4 STATIC ${SOURCE_LIB})

target_link_libraries(sdl_base_lesson4 PRIVATE SDL2 SDL2_image)
target_link_libraries(sdl_base_lesson4 PRIVATE ${SDL2_LIBRARY})

add_executable(lesson4 lesson4.cpp)

target_link_libraries(lesson4 PRIVATE sdl_base_lesson4)