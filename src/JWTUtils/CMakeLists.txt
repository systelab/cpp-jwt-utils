# Configure preprocessor definitions
add_compile_options(-DRAPIDJSON_HAS_STDSTRING=1)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure JWTUtils static library
set(JWT_UTILS JWTUtils)
file(GLOB_RECURSE JWT_UTILS_SRC "*.cpp")
file(GLOB_RECURSE JWT_UTILS_HDR "*.h")
add_library(${JWT_UTILS} STATIC ${JWT_UTILS_SRC} ${JWT_UTILS_HDR})
