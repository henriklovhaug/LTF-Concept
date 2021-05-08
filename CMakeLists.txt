cmake_minimum_required(VERSION 3.0.0)
project(LTF VERSION 0.1.0)

INCLUDE_DIRECTORIES(
    e:/koding/vcpkg/installed/x64-windows/include
)
link_directories(
    e:/koding/vcpkg/installed/x64-windows/lib
)

add_executable(LTF main.cpp)

target_link_libraries(LTF
    raylib
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
