link_libraries(Bmp)

project(BmpTest)

add_executable(${PROJECT_NAME} "a.c" "b.c")
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})