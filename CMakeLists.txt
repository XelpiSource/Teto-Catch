cmake_minimum_required(VERSION 4.1)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build all libs static" FORCE)

project(Give_Kasane_Teto_her_baguettes)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory("thirdparty/raylib")

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(Give_Kasane_Teto_her_baguettes ${MY_SOURCES})

target_link_libraries(Give_Kasane_Teto_her_baguettes
        PRIVATE
        raylib_static
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(Give_Kasane_Teto_her_baguettes PUBLIC RESOURCES_PATH="./resources/")
else()
    target_compile_definitions(Give_Kasane_Teto_her_baguettes PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
endif()