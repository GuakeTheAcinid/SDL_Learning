project(lesson11)
find_package(SDL2_image REQUIRED)


set(SOURCE_LIB ../lesson11/sdl_base_lesson11.cpp)
add_library(sdl_base_lesson11 STATIC ${SOURCE_LIB})

target_link_libraries(sdl_base_lesson11 PRIVATE SDL2 SDL2_image)
target_link_libraries(sdl_base_lesson11 PRIVATE ${SDL2_LIBRARY})

add_executable(lesson11 lesson11.cpp)

target_link_libraries(lesson11 PRIVATE sdl_base_lesson11)

#file(COPY folder DESTINATION folder)