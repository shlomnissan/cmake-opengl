cmake_minimum_required(VERSION 3.25)

include_directories(${GLAD_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(cmake_opengl main.cc ${GLAD_SOURCE_FILES})

target_link_libraries(cmake_opengl glfw OpenGL::GL)
