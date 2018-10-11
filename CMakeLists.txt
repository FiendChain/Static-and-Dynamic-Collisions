cmake_minimum_required(VERSION 3.11)

set(CMAKE_C_COMPILER C:/MinGW/bin/gcc.exe)
set(CMAKE_CXX_COMPILER C:/MinGW/bin/g++.exe)

project("Static and dynamic collisions")

set(SRC_FILES_DIR ${CMAKE_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/libs)


set(SRC_FILES 
    ${SRC_FILES_DIR}/main.cpp
    ${SRC_FILES_DIR}/App.cpp
    ${SRC_FILES_DIR}/AppBalls.cpp
    ${SRC_FILES_DIR}/AppInput.cpp
    ${SRC_FILES_DIR}/AppRender.cpp
    ${SRC_FILES_DIR}/Ball.cpp)

include_directories(${SRC_FILES_DIR})
include_directories(${LIB_DIR})

# sfml libraries
set(SFML_DIR ${LIB_DIR}/SFML-2.5.0)
include_directories(${SFML_DIR}/include)
macro(add_sfml_library name)
    add_library(${name} STATIC IMPORTED)
    set_target_properties(${name} PROPERTIES
        IMPORTED_LOCATION "${SFML_DIR}/lib/lib${name}.a"
        INTERFACE_INCLUDE_DIRECTORIES "${SFML_DIR}/include/SFML"
        INTERFACE_COMPILE_DEFINITIONS SFML_STATIC
    )
endmacro()

add_sfml_library(sfml-graphics-s)
add_sfml_library(sfml-window-s)
add_sfml_library(sfml-system-s)
add_sfml_library(freetype)
add_sfml_library(jpeg)
set(SFML_LIBS 
    sfml-graphics-s sfml-window-s sfml-system-s
    winmm gdi32 opengl32 freetype jpeg)

# imgui
add_subdirectory(${LIB_DIR}/imgui)

# imgui-sfml
add_library(imgui-sfml ${LIB_DIR}/imgui-sfml/imgui-SFML.cpp)
target_link_libraries(imgui-sfml imgui ${SFML_LIBS})
install(TARGETS imgui-sfml DESTINATION bin)

# main
add_executable(main ${SRC_FILES})
target_compile_definitions(main PUBLIC SFML_STATIC)
target_compile_options(main PUBLIC -Werror=return-type)
target_link_libraries(main imgui imgui-sfml ${SFML_LIBS})

install(TARGETS main DESTINATION bin)
