cmake_minimum_required(VERSION 3.10)
project(Bmp)

option(ae2f_Bmp_Use_OpenCL "Try the implementations using OpenCL." OFF)
option(ae2f_IS_SHARED "Is a shared library or static one." OFF)

if(ae2f_IS_SHARED)
    set(ae2f_PREFIX_LIB SHARED)
    add_compile_definitions(-D_ae2f_IS_SHARED=1)
else()
    set(ae2f_PREFIX_LIB )
    add_compile_definitions(-D_ae2f_IS_SHARED=0)
endif()

# Namespace Package
include(GNUInstallDirs)

add_library(
	${PROJECT_NAME}
    ${ae2f_PREFIX_LIB}
    "include/ae2f/Bmp/Dot.h"
    "include/ae2f/Bmp/Head.h"
    "include/ae2f/Bmp/Idxer.h"
    "include/ae2f/Bmp/Src.h"
    "src/Src/Default.c"
)

include(FetchContent)
find_package(Core)
if(NOT Core_FOUND)
    message("ae2f::Core not found")

    FetchContent_Declare(
        Core
        GIT_REPOSITORY https://github.com/yuisanae2f/ae2f_Core.git
        GIT_TAG "Rel-v1.2.1.1"
        SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/external/ae2f/Core
    )
    
    FetchContent_MakeAvailable(Core)
    target_link_libraries(${PROJECT_NAME} Core)
else()
    target_link_libraries(Bmp ae2f::Core)
endif()

if(${ae2f_Bmp_Use_OpenCL})
find_package(OpenCL)
if(NOT OpenCL_FOUND)
    message("OpenCL::OpenCL not found")

    FetchContent_Declare(
        OpenCL
        GIT_REPOSITORY https://github.com/KhronosGroup/OpenCL-SDK.git
        GIT_TAG "v2024.05.08"
        SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/external/OpenCL/OpenCL
    )

    FetchContent_MakeAvailable(OpenCL)
    target_link_libraries(Bmp OpenCL)
else()
    target_link_libraries(Bmp OpenCL::OpenCL)
endif()
endif()


include_directories(include)

# Header
target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ae2f::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)