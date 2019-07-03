cmake_minimum_required(VERSION 3.2)

# Find 3rd party dependencides
find_package(OpenSSL)

# Configure preprocessor definitions
add_compile_options(-DRAPIDJSON_HAS_STDSTRING=1)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure JWTUtils static library
set(JWT_UTILS JWTUtils)
file(GLOB_RECURSE JWT_UTILS_SRC "*.cpp")
file(GLOB_RECURSE JWT_UTILS_HDR "*.h")
add_library(${JWT_UTILS} STATIC ${JWT_UTILS_SRC} ${JWT_UTILS_HDR})
target_link_libraries(${JWT_UTILS} RapidJSONAdapter OpenSSL::OpenSSL)

#Configure source groups
foreach(FILE ${JWT_UTILS_SRC} ${JWT_UTILS_HDR}) 
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

