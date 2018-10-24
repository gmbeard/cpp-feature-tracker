cmake_minimum_required(VERSION 3.10)

project(CPPFeatureTest CXX)

file(GLOB test_sources ${CMAKE_CURRENT_LIST_DIR}/tests/*.cpp)

message(STATUS "Build dir: ${PROJECT_BINARY_DIR}")
foreach(test_src IN LISTS test_sources)
    get_filename_component(test_name ${test_src} NAME_WE)

    try_compile(
        supports_${test_name} 
        ${PROJECT_BINARY_DIR} 
        ${test_src}
        CXX_STANDARD 17
    )

    if (supports_${test_name})
        list(APPEND supported ${test_name})
    else()
        list(APPEND unsupported ${test_name})
    endif()
endforeach()

configure_file(config.h.in ${PROJECT_BINARY_DIR}/config.h @ONLY)

set(test_header_file ${PROJECT_BINARY_DIR}/tests.hpp)

file(WRITE 
    ${test_header_file}
    "char const* SUPPORTED[] = {"
)

foreach(test IN LISTS supported)
    file(APPEND 
        ${test_header_file}
        "\"${test}\","
    )
endforeach()

file(APPEND
    ${test_header_file}
    "nullptr};\n"
)

file(APPEND 
    ${test_header_file}
    "char const* UNSUPPORTED[] = {"
)

foreach(test IN LISTS unsupported)
    file(APPEND 
        ${test_header_file}
        "\"${test}\","
    )
endforeach()

file(APPEND
    ${test_header_file}
    "nullptr};\n"
)

add_executable(cpp-features
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)

target_include_directories(cpp-features
    PRIVATE
        ${PROJECT_BINARY_DIR}
)

target_compile_features(cpp-features
    PRIVATE
        cxx_std_11
)
