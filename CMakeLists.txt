cmake_minimum_required(VERSION 3.20)
project(Bmp VERSION 6.16.12)
enable_testing()
add_subdirectory(mod/ae2f/mov2)

if(NOT TARGET ${PROJECT_NAME})


set(ae2f_LIBPREFIX "" CACHE STRING "")
ae2f_CoreLibProjTent(
    ${PROJECT_NAME}
    ${ae2f_LIBPREFIX}
    include

    "include/ae2f/Bmp/Dot.h"
    "include/ae2f/Bmp/Head.h"
    "include/ae2f/Bmp/Idx.h"
    "include/ae2f/Bmp/Blend.h"
    "include/ae2f/Bmp/BitCount.h"
    "include/ae2f/Bmp/Src.h"
    "src/Src.c"

    "include/ae2f/Bmp/Src/Rect.h"
    "src/Src/Rect.c"
)

target_link_libraries(${PROJECT_NAME} PUBLIC mov2)

ae2f_CoreTestTent(${PROJECT_NAME} test)

if(LINUX)
    find_library(M_LIB m)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${M_LIB}) # library 'math'
endif()

endif()