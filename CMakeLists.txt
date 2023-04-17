cmake_minimum_required(VERSION 3.25)
project(cmake_opengl_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_GLFW "Fetch and build GLFW from source" ON)

find_package(OpenGL REQUIRED)

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

add_executable(cmake_opengl_app main.cpp)

target_link_libraries(cmake_opengl_app glfw OpenGL::GL)
