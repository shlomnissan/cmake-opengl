cmake_minimum_required(VERSION 3.25)

add_executable(cmake_opengl main.cc ${GLAD_SOURCE_FILES})

file(GLOB SHADERS "shaders/*.glsl")

foreach(SHADER IN LISTS SHADERS)
    get_filename_component(FILENAME ${SHADER} NAME)
    string(REGEX REPLACE "\\.[^.]*$" "" FILENAME_NO_EXT ${FILENAME})
    set(HEADER_FILE shaders/${FILENAME_NO_EXT}.h)

    file(READ ${SHADER} CONTENTS)
    file(WRITE ${HEADER_FILE} "static const char* _SHADER_${FILENAME_NO_EXT} = R\"(")
    file(APPEND ${HEADER_FILE} "${CONTENTS}")
    file(APPEND ${HEADER_FILE} ")\";")
endforeach()

target_include_directories(
    cmake_opengl PRIVATE
    ${GLAD_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    cmake_opengl PRIVATE
    glfw
    OpenGL::GL
)