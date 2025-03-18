project(lesson10)
find_package(SDL2_image REQUIRED)


set(SOURCE_LIB ../lesson10/sdl_base_lesson10.cpp)
add_library(sdl_base_lesson10 STATIC ${SOURCE_LIB})

target_link_libraries(sdl_base_lesson10 PRIVATE SDL2 SDL2_image)
target_link_libraries(sdl_base_lesson10 PRIVATE ${SDL2_LIBRARY})

add_executable(lesson10 lesson10.cpp)

target_link_libraries(lesson10 PRIVATE sdl_base_lesson10)

#file(COPY folder DESTINATION folder)