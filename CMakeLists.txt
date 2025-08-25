cmake_minimum_required(VERSION 3.24) # Require modern CMake

project(DCEngine LANGUAGES CXX) #Name project

set(CMAKE_CXX_STANDARD 20) #Use C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON) #Fail if the compiler can't do C++20
set(CMAKE_CXX_EXTENSIONS OFF) #Avoid non-standard compiler extensions

#Common warning flags (per compiler)
function(setup_warnings target)
    if (MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else ()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpendantic)
    endif()
endfunction()

add_executable(dc_hello #Build exe dc_hello
    src/main.cpp
)

#Put built EXEs in build/bin/
set_target_properties(dc_hello PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
setup_warnings(dc_hello)

# ---- Fetch raylib (window/input/drawing) for the graphics target ----
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) #don't build raylib's own samples
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)
FetchContent_MakeAvailable(raylib)

# ---- Header-only engine target for future code (empty for now) ----
add_library(dcengine INTERFACE)
target_include_directories(dcengine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/engine)
target_link_libraries(dcengine INTERFACE raylib)

# ---- Target 2: the graphics game window ----
add_executable(dcgame
  game/main.cpp
)
target_link_libraries(dcgame PRIVATE dcengine)
set_target_properties(dcgame PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
setup_warnings(dcgame)