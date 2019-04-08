[![Build Status](https://travis-ci.org/systelab/cpp-jwt-utils.svg?branch=master)](https://travis-ci.org/systelab/cpp-jwt-utils)
[![Build status](https://ci.appveyor.com/api/projects/status/jtbc93k8i6vtnx56?svg=true)](https://ci.appveyor.com/project/systelab/cpp-jwt-utils)
[![codecov](https://codecov.io/gh/systelab/cpp-jwt-utils/branch/master/graph/badge.svg)](https://codecov.io/gh/systelab/cpp-jwt-utils)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/dd32a177d926495dab93be941a939881)](https://www.codacy.com/app/systelab/cpp-jwt-utils?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=systelab/cpp-jwt-utils&amp;utm_campaign=Badge_Grade)
[![Download](https://api.bintray.com/packages/systelab/conan/JWTUtils:systelab/images/download.svg)](https://bintray.com/systelab/conan/JWTUtils:systelab/_latestVersion)

# C++ JSON Web Token Utilities

This library provides utilities to generate, parse and validate JWTs (JSON Web Tokens) used to implement an authentication mechanism over a REST API. 

## Setup

### Build from sources

Prerequisites:
  - [Git](https://git-scm.com/)
  - [Conan](https://conan.io/)
  - [CMake](https://cmake.org/)
  - [Visual Studio](https://visualstudio.microsoft.com/) (only on Windows)
  - [GCC](https://gcc.gnu.org/) (only on Linux)

Build library with the following steps:
  1. Clone this repository in a local drive
  2. Make a build directory (i.e. `build/`)
  3. Install `conan` dependencies in the build directory
  4. Run `cmake` in the build directory to configure build targets
  5. Use `Visual Studio` (on Windows) or `make` (on Linux) to build the library

#### Windows
``` bash
> git clone https://github.com/systelab/cpp-jwt-utils
> md build && cd build
> conan install .. -s arch=x86
> cmake ..
> devenv.exe JWTUtils.sln
```

#### Linux
``` bash
> git clone https://github.com/systelab/cpp-jwt-utils
> mkdir build && cd build
> conan install ..
> cmake .. -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release]
> make
```

### Download using Conan

  1. Create/update your `conanfile.txt` to add this library as follows:

```
[requires]
JWTUtils/1.0.0@systelab/stable

[generators]
cmake
```

  2. Integrate Conan into CMake by adding the following code into your `CMakeLists.txt`:

```cmake
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
```

  3. Link against `${CONAN_LIBS}` when configuring your executables in CMake:

```cmake
set(MY_PROJECT MyProject)
add_executable(${MY_PROJECT} main.cpp)
target_link_libraries(${MY_PROJECT} ${CONAN_LIBS})
```

## Usage

### Build a token

Use the `systelab::jwt::TokenBuilderService` class to generate a valid token containing a vector of claims:

```cpp
#include "RapidJSONAdapter/JSONAdapter.h"
#include "JWTUtils/Services/TokenBuilderService.h"

systelab::json::rapidjson::JSONAdapter jsonAdapter;
systelab::jwt::TokenBuilderService tokenBuilderService(jsonAdapter);

std::string secretKey = "Here goes your secret key";
std::vector< std::pair<std::string, std::string> > claims =
    { {"sub", "1234567890"}, {"name", "John Doe"}, {"iat", "1516239022"} };

std::string token = tokenBuilderService.buildJWT(secretKey, claims);
```

### Parse a token

Use the `systelab::jwt::TokenParserService` class to parse a JWT token and retrieve the claims contained on it. It will return false when the provided JWT is not valid.

```cpp
#include "RapidJSONAdapter/JSONAdapter.h"
#include "JWTUtils/Services/TokenParserService.h"

systelab::json::rapidjson::JSONAdapter jsonAdapter;
systelab::jwt::TokenParserService tokenParserService(jsonAdapter);

std::string token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9."
                    "eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoiMTUxNjIzOTAyMiJ9."
                    "5ODOvx-citIP2b7EbnG1TlSUcoAKmCeOyE-_Kw3-dLo";
std::string secretKey = "Here goes your secret key";

std::vector< std::pair<std::string, std::string> > claims;
bool valid = tokenParserService.validateJWT(token, secretKey, claims);
```

