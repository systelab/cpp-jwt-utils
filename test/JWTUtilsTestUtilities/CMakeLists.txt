cmake_minimum_required(VERSION 3.2)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find external dependencides
find_package(gtest)

# Configure DB Adapter test utilities project
set(JWT_UTILS_TEST_UTILITIES_PROJECT JWTUtilsTestUtilities)
file(GLOB_RECURSE JWT_UTILS_TEST_UTILITIES_PROJECT_SRC "*.cpp")
file(GLOB_RECURSE JWT_UTILS_TEST_UTILITIES_PROJECT_HDR "*.h")
add_library(${JWT_UTILS_TEST_UTILITIES_PROJECT} STATIC ${JWT_UTILS_TEST_UTILITIES_PROJECT_SRC} ${JWT_UTILS_TEST_UTILITIES_PROJECT_HDR})
target_link_libraries(${JWT_UTILS_TEST_UTILITIES_PROJECT} JWTUtils gtest::gtest)

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
