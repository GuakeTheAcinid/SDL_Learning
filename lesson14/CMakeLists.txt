project(lesson14)
find_package(SDL2_image REQUIRED)


set(SOURCE_LIB ../lesson14/sdl_base_lesson14.cpp)
add_library(sdl_base_lesson14 STATIC ${SOURCE_LIB})

target_link_libraries(sdl_base_lesson14 PRIVATE SDL2 SDL2_image)
target_link_libraries(sdl_base_lesson14 PRIVATE ${SDL2_LIBRARY})

add_executable(lesson14 lesson14.cpp)

target_link_libraries(lesson14 PRIVATE sdl_base_lesson14)

#file(MAKE_DIRECTORY ${img})
file(COPY ../pngs/img/ DESTINATION img)

#file(COPY folder DESTINATION folder)