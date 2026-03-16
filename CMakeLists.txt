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

    # Post-build: expose the Emscripten instance globally so embind functions
    # are accessible from the browser dev console (e.g. window.Module.get_label_contents())
    add_custom_command(TARGET embind_unresolved_promise POST_BUILD
        COMMAND ${CMAKE_COMMAND}
            -DHTML_FILE=$<TARGET_FILE_DIR:embind_unresolved_promise>/embind_unresolved_promise.html
            -P ${CMAKE_CURRENT_SOURCE_DIR}/patch_html.cmake
        COMMENT "Patching HTML to expose Emscripten instance on window.Module"
    )
endif()
