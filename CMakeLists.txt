cmake_minimum_required(VERSION 3.20)
project(Bmp VERSION 4.14.6)
enable_testing()

if(NOT TARGET ${PROJECT_NAME})

add_subdirectory(mod/ae2f/mov2)
link_libraries(mov2)

# Namespace Package
include(GNUInstallDirs)

add_library(
    ${PROJECT_NAME}
    ${ae2f_LIBPREFIX}

    "include/ae2f/Bmp/Dot.h"
    "include/ae2f/Bmp/Head.h"
    "include/ae2f/Bmp/Idx.h"
    "include/ae2f/Bmp/Blend.h"
    "include/ae2f/Bmp/BitCount.h"
    "include/ae2f/Bmp/Src.h"
    "src/Src/Double.c"
)

if(LINUX)
    find_library(M_LIB m)
    target_link_libraries(${PROJECT_NAME} ${M_LIB}) # library 'math'
endif()

include_directories(include)
add_subdirectory(test)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY include/ae2f/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ae2f
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ae2f::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

endif()