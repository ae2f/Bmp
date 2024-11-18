cmake_minimum_required(VERSION 3.20)
project(Bmp)
enable_testing()

if(NOT TARGET ${PROJECT_NAME})

add_subdirectory(mod/ae2f/Core)
link_libraries(Core)

# Namespace Package
include(GNUInstallDirs)


add_library(
    ${PROJECT_NAME}
    ${ae2f_LIBPREFIX}

    "include/ae2f/Bmp/Dot.h"
    "include/ae2f/Bmp/Head.h"
    "include/ae2f/Bmp/Idxer.h"
    "include/ae2f/Bmp/Src.h"
    "src/Src/Double.c"
)

if(LINUX)
    find_library(M_LIB m)
    target_link_libraries(${PROJECT_NAME} ${M_LIB}) # library 'math'
endif()

include_directories(include)
add_subdirectory(test)

# Header
target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# 설치 설정
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY include/ae2f/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ae2f
)

# 패키지 설정
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ae2f::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)

# 패키지 구성 파일 생성
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