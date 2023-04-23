cmake_minimum_required(VERSION 3.25)
project(cmake_opengl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_GLFW "Fetch GLFW and build from source" ON)

# Find OpenGL binding library
find_package(OpenGL REQUIRED)

# Build GLFW from source
if (BUILD_GLFW)
    include(FetchContent)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG origin/master
        GIT_SHALLOW true
    )

    set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")

    FetchContent_GetProperties(glfw)
    if(NOT glfw_POPULATED)
        FetchContent_Populate(glfw)
        add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
    endif()
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glad)
add_subdirectory(src)
