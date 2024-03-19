# AED 2022/2023 - Group Work
cmake_minimum_required(VERSION 3.10)
project(DA2324_PRJ1_G11_3)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(
        DA2324_PRJ1_G11_3 main.cpp
        terminal/TerminalFlow.cpp
        terminal/TerminalFlow.h
        #App/sky_scannix.cpp
        #Tests/Controllers/query_controller_test.cpp
        #Tests/Lib/csv_parser_test.cpp
        #Tests/Lib/db_loader_test.cpp
        #Tests/Lib/file_wrapper_test.cpp
        #Tests/Models/airport_graph_test.cpp
)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/files/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)

target_link_libraries(DA2324_PRJ1_G11_3 gtest gtest_main)