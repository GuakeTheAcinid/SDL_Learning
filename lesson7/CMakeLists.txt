project(lesson7)
find_package(SDL2_image REQUIRED)


set(SOURCE_LIB ../lesson7/sdl_base_lesson7.cpp)
add_library(sdl_base_lesson7 STATIC ${SOURCE_LIB})

target_link_libraries(sdl_base_lesson7 PRIVATE SDL2 SDL2_image)
target_link_libraries(sdl_base_lesson7 PRIVATE ${SDL2_LIBRARY})

add_executable(lesson7 lesson7.cpp)

target_link_libraries(lesson7 PRIVATE sdl_base_lesson7)