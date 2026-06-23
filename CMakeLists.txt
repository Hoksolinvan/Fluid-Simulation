cmake_minimum_required(VERSION 3.16)
project(Fluid LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(Fluidsim main.cpp)

target_link_libraries(Fluidsim PRIVATE OpenGL::GL GLEW::GLEW glfw)
