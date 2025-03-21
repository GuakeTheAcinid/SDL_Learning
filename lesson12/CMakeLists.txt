project(lesson12)
find_package(SDL2_image REQUIRED)


set(SOURCE_LIB ../lesson12/sdl_base_lesson12.cpp)
add_library(sdl_base_lesson12 STATIC ${SOURCE_LIB})

target_link_libraries(sdl_base_lesson12 PRIVATE SDL2 SDL2_image)
target_link_libraries(sdl_base_lesson12 PRIVATE ${SDL2_LIBRARY})

add_executable(lesson12 lesson12.cpp)

target_link_libraries(lesson12 PRIVATE sdl_base_lesson12)

#file(COPY folder DESTINATION folder)