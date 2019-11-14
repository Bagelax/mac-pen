cmake_minimum_required(VERSION 3.13)
find_package(glfw3 3.3 REQUIRED)
project(mac-pen)

SET(CMAKE_CXX_STANDARD 17)

add_executable(mac-pen
        main.cpp
        glad.c
        )
target_link_libraries(mac-pen glfw)

find_package(OpenGL REQUIRED)

target_include_directories(mac-pen PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(mac-pen ${OPENGL_gl_LIBRARY})

target_link_libraries(mac-pen ${OPENGL_glu_LIBRARY})