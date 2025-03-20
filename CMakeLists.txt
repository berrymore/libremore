cmake_minimum_required(VERSION 3.30)

project(
        libremore
        VERSION 0.1.0
        DESCRIPTION "Experiments with C"
        LANGUAGES C
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_C_COMPILER clang)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif ()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -Wpedantic -Werror
        -Wformat=2 -Wformat-security -Wformat-nonliteral
        -Wcast-align -Wpointer-arith -Wstrict-overflow=5
        -Wstrict-prototypes -Wundef -Wswitch-default
        -Wunreachable-code -Wfloat-equal -Wconversion
        -Wdouble-promotion -Wnull-dereference
        -Winit-self -Wwrite-strings
        -Wmissing-include-dirs -Wshift-overflow
        -Wdate-time -Warray-bounds
        -fstack-protector-strong
)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(${PROJECT_NAME} PRIVATE
            -fsanitize=address,undefined -fno-omit-frame-pointer
    )
    target_link_options(${PROJECT_NAME} PRIVATE
            -fsanitize=address,undefined
    )
endif ()

message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")