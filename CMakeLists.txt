cmake_minimum_required(VERSION 3.10)

project(miserable)

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
    GIT_TAG "release-3.4.20"
    GIT_SHALLOW YES
)
FetchContent_MakeAvailable(SDL3)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3)

