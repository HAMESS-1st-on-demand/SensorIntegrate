cmake_minimum_required(VERSION 3.0.0)
project(SICmake VERSION 0.1.0 LANGUAGES C)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CTest)
include(CPack)
enable_testing()

add_executable(SICmake SI.c)
target_link_libraries(SICmake wiringPi)
target_link_libraries(SICmake bcm2835)
target_link_libraries(SICmake pthread)