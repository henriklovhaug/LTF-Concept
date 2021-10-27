cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0072 NEW)

project(LTF VERSION 0.1.0)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

# Set this to the minimal version you want to support
find_package(raylib 3.0 QUIET) # Let CMake search for a raylib-config.cmake

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)

  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

  endif()

endif()
set(RuntimeOutputDir ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${RuntimeOutputDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${RuntimeOutputDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${RuntimeOutputDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${RuntimeOutputDir})

file(GLOB PROJECT_SOURCE_FILES CONFIGURE_DEPS ./*.cpp)
#file(GLOB PROJECT_HEADER_FILES CONFIGURE_DEPS ./*.hpp)
File(GLOB MY_OBJ_HEADERS
    "${CMAKE_SOURCE_DIR}/resources/*.obj"
)
FILE(COPY ${MY_OBJ_HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/resources")

File(GLOB MY_MTL_HEADERS
    "${CMAKE_SOURCE_DIR}/resources/*.mtl"
)
FILE(COPY ${MY_MTL_HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/resources")

include_directories(${PROJECT_SOURCE_DIR}/resources)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} raylib)
#target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
