cmake_minimum_required(VERSION 3.20)

project(OpenNet VERSION 0.1.0 LANGUAGES CXX)

option(OPENNET_BUILD_TESTS "Build OpenNet tests" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(opennet
    src/network.cpp
)

target_include_directories(opennet
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(opennet PUBLIC cxx_std_20)

add_executable(opennet_demo
    src/main.cpp
)
target_link_libraries(opennet_demo PRIVATE opennet)

if(OPENNET_BUILD_TESTS)
    enable_testing()
    add_executable(opennet_tests
        tests/network_tests.cpp
    )
    target_link_libraries(opennet_tests PRIVATE opennet)
    add_test(NAME opennet_tests COMMAND opennet_tests)
endif()
