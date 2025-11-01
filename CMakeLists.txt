cmake_minimum_required(VERSION 3.14)

project(Shooter LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)

add_executable(Shooter src/main.cpp
        lib/sprite_loader/sprite_loader.cpp
        lib/game_loop/game_loop.cpp
        include/app.rc
)

add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
        COMMENT "Copying assets to build directory"
)

add_dependencies(Shooter copy_assets)
target_link_libraries(Shooter PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image)
target_include_directories(Shooter PRIVATE
        lib/sprite_loader
        lib/game_loop
        include
)

if (MSVC)
    set_source_files_properties(include/app.rc PROPERTIES LANGUAGE RC)
endif ()
