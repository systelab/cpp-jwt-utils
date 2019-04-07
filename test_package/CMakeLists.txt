cmake_minimum_required(VERSION 3.2)

project(JWTUtilsPackageTestProject)

# Configure environment
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setup 3rd party libraries through conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Configure test package project
set(JWT_UTILS_PACKAGE_TEST_PROJECT JWTUtilsPackageTest)
add_executable(${JWT_UTILS_PACKAGE_TEST_PROJECT} JWTUtilsExample.cpp)
target_link_libraries(${JWT_UTILS_PACKAGE_TEST_PROJECT} ${CONAN_LIBS})
