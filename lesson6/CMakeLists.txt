project(lesson6)
find_package(SDL2_image REQUIRED)


set(SOURCE_LIB ../lesson6/sdl_base_lesson6.cpp)
add_library(sdl_base_lesson6 STATIC ${SOURCE_LIB})

target_link_libraries(sdl_base_lesson6 PRIVATE SDL2 SDL2_image)
target_link_libraries(sdl_base_lesson6 PRIVATE ${SDL2_LIBRARY})

add_executable(lesson6 lesson6.cpp)

target_link_libraries(lesson6 PRIVATE sdl_base_lesson6)