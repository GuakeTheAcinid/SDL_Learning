project(lesson13)
find_package(SDL2_image REQUIRED)


set(SOURCE_LIB ../lesson13/sdl_base_lesson13.cpp)
add_library(sdl_base_lesson13 STATIC ${SOURCE_LIB})

target_link_libraries(sdl_base_lesson13 PRIVATE SDL2 SDL2_image)
target_link_libraries(sdl_base_lesson13 PRIVATE ${SDL2_LIBRARY})

add_executable(lesson13 lesson13.cpp)

target_link_libraries(lesson13 PRIVATE sdl_base_lesson13)

#file(MAKE_DIRECTORY ${img})
file(COPY ../pngs/img/ DESTINATION img)

#file(COPY folder DESTINATION folder)