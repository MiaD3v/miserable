cmake_minimum_required(VERSION 3.10)

project(miserable)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fno-exceptions")
set(CMAKE_CXX_STANDARD "26")
set(SDLTTF_VENDORED ON CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
    GIT_TAG "release-3.4.20"
    GIT_SHALLOW YES
)
FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
    SDL3_image
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL_image.git"
    GIT_TAG "release-3.4.8"
    GIT_SHALLOW YES
)
FetchContent_MakeAvailable(SDL3_image)

FetchContent_Declare(
    SDL3_ttf
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL_ttf.git"
    GIT_TAG "release-3.2.2"
    GIT_SHALLOW YES
)
FetchContent_MakeAvailable(SDL3_ttf)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/miserable.cpp
    src/renderer.cpp
    src/scene.cpp
    src/scenes/main_scene.cpp
    src/deltatime.cpp
    src/image.cpp
    src/inventory.cpp
    src/scenes/game_over_screen.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image::SDL3_image)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_ttf::SDL3_ttf)

