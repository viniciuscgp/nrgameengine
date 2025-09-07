cmake_minimum_required(VERSION 3.15)
project(NRGameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- fontes ---
file(GLOB_RECURSE ENGINE_SOURCES 
    src/core/*.cpp
    src/ports/*.h
    src/adapters/sdl/*.cpp
)

add_executable(nrge
    src/main.cpp
    ${ENGINE_SOURCES}
)

# --- SDL2 ---
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# --- Lua (pkg-config) ---
find_package(PkgConfig REQUIRED)
pkg_search_module(LUA REQUIRED lua5.3)

# --- Includes ---
target_include_directories(nrge PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${LUA_INCLUDE_DIRS}
    src
)

# --- Libs ---
target_link_libraries(nrge
    ${SDL2_LIBRARIES}
    ${LUA_LIBRARIES}
    SDL2_image
    SDL2_mixer
    SDL2_ttf
)

