cmake_minimum_required(VERSION 3.11)

project(imgui)

set(SRC_FILES 
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_widgets.cpp
    imgui.cpp)

set(HEADER_FILES
    imconfig.h
    imgui_internal.h
    imgui.h
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h)

add_library(imgui ${SRC_FILES})

install(TARGETS imgui DESTINATION bin)
install(FILES ${HEADER_FILES} DESTINATION include)


