cmake_minimum_required(VERSION 3.2)

# Enabled testing module
enable_testing()

# Find external dependencides
find_package(RapidJSONAdapter)
find_package(OpenSSL)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure test project
set(JWT_UTILS_TEST_PROJECT JWTUtilsTest)
file(GLOB_RECURSE JWT_UTILS_TEST_PROJECT_SRC "*.cpp")
file(GLOB_RECURSE JWT_UTILS_TEST_PROJECT_HDR "*.h")
add_executable(${JWT_UTILS_TEST_PROJECT} ${JWT_UTILS_TEST_PROJECT_SRC} ${JWT_UTILS_TEST_PROJECT_HDR})
target_link_libraries(${JWT_UTILS_TEST_PROJECT} gmock_main JWTUtils RapidJSONAdapter)

#Configure source groups
foreach(FILE ${JWT_UTILS_TEST_PROJECT_SRC} ${JWT_UTILS_TEST_PROJECT_HDR}) 
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

# Register tests
add_test(NAME JWTUtilsTest COMMAND ${JWT_UTILS_TEST_PROJECT})

# Additional target for code coverage analysis
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
	include(CodeCoverage)
	setup_target_for_coverage(JWTUtilsTestCoverage JWTUtilsTest coverage)
endif()
