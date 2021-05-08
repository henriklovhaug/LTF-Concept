cmake_minimum_required(VERSION 3.0.0)
project(LinearTitanFall VERSION 0.1.0)

INCLUDE_DIRECTORIES(
    e:/koding/vcpkg/installed/x64-windows/include
)
link_directories(
    e:/koding/vcpkg/installed/x64-windows/lib
)
add_executable(LinearTitanFall main.cpp)

target_link_libraries(LinearTitanFall
    raylib
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
