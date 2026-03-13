cmake_minimum_required(VERSION 3.24)
project(embind_unresolved_promise LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(embind_unresolved_promise main.cpp)

target_link_libraries(embind_unresolved_promise PRIVATE Qt6::Widgets)

if(EMSCRIPTEN)
    target_link_options(embind_unresolved_promise PRIVATE -lembind)
endif()
