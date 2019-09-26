cmake_minimum_required(VERSION 3.2)

project(JWTUtils)

# Configure environment
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Setup google_test
include(ConfigureGoogleTest)
configure_google_test()

# Setup extern repositories
include(GitCloneRepository)
git_clone_repository(URL https://github.com/systelab/cpp-test-utilities.git           DIR extern/TestUtilities      BRANCH v1.0.0)
git_clone_repository(URL https://github.com/systelab/cpp-json-adapter.git             DIR extern/JSONAdapter        BRANCH v1.0.1)
git_clone_repository(URL https://github.com/systelab/cpp-rapidjson-json-adapter.git   DIR extern/RapidJSONAdapter   BRANCH v1.0.1)

# Configure include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/test)
include_directories(${CMAKE_SOURCE_DIR}/extern/RapidJSONAdapter/src)

# Add subprojects
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/RapidJSONAdapter/src/RapidJSONAdapter)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/JWTUtils)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/JWTUtilsTestUtilities)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/JWTUtilsTest)
