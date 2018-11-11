cmake_minimum_required(VERSION 3.12)
project(opengl101)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES main.cpp glad.c)
#find_package(SFML 2.5 COMPONENTS graphics audio system window REQUIRED) #‍1
add_executable(opengl101 ${SOURCES})
#target_link_libraries(opengl101 sfml-graphics sfml-audio) #1
target_include_directories(opengl101 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps)
target_link_libraries(opengl101 glfw ${CMAKE_DL_LIBS})