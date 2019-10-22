cmake_minimum_required(VERSION 3.2)

project(JWTUtilsTestUtilities)

# Configure environment
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find external dependencides
find_package(gtest)
find_package(JWTUtils)

# Configure DB Adapter test utilities project
set(JWT_UTILS_TEST_UTILITIES_PROJECT JWTUtilsTestUtilities)
file(GLOB_RECURSE JWT_UTILS_TEST_UTILITIES_PROJECT_SRC "Mocks/*.cpp")
file(GLOB_RECURSE JWT_UTILS_TEST_UTILITIES_PROJECT_HDR "Mocks/*.h")
add_library(${JWT_UTILS_TEST_UTILITIES_PROJECT} STATIC ${JWT_UTILS_TEST_UTILITIES_PROJECT_SRC} ${JWT_UTILS_TEST_UTILITIES_PROJECT_HDR})
target_link_libraries(${JWT_UTILS_TEST_UTILITIES_PROJECT} JWTUtils::JWTUtils gtest::gtest)

# Configure source groups
foreach(FILE ${JWT_UTILS_TEST_UTILITIES_PROJECT_SRC} ${JWT_UTILS_TEST_UTILITIES_PROJECT_HDR})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    if ("${FILE}" MATCHES ".*\\.cpp")
       set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
       set(GROUP "Header Files${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()
