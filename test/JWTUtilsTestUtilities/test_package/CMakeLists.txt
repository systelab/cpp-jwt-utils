cmake_minimum_required(VERSION 3.2)

project(JWTUtilsTestUtilitiesPackageTestProject)

# Configure environment
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find tested package
find_package(JWTUtilsTestUtilities)

# Configure test package project
set(JWT_UTILS_TEST_UTILITIES_PACKAGE_TEST_PROJECT JWTUtilsTestUtilitiesPackageTest)
add_executable(${JWT_UTILS_TEST_UTILITIES_PACKAGE_TEST_PROJECT} JWTUtilsTestUtilitiesExample.cpp)
target_link_libraries(${JWT_UTILS_TEST_UTILITIES_PACKAGE_TEST_PROJECT} JWTUtilsTestUtilities::JWTUtilsTestUtilities)

# Register test
enable_testing()
add_test(NAME JWTUtilsTestUtilitiesPackageTest COMMAND ${JWT_UTILS_TEST_UTILITIES_PACKAGE_TEST_PROJECT})
