[![Build Status](https://travis-ci.org/systelab/cpp-jwt-utils.svg?branch=master)](https://travis-ci.org/systelab/cpp-jwt-utils)
[![Build status](https://ci.appveyor.com/api/projects/status/jtbc93k8i6vtnx56?svg=true)](https://ci.appveyor.com/project/systelab/cpp-jwt-utils)
[![codecov](https://codecov.io/gh/systelab/cpp-jwt-utils/branch/master/graph/badge.svg)](https://codecov.io/gh/systelab/cpp-jwt-utils)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/dd32a177d926495dab93be941a939881)](https://www.codacy.com/app/systelab/cpp-jwt-utils?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=systelab/cpp-jwt-utils&amp;utm_campaign=Badge_Grade)
[![Download](https://api.bintray.com/packages/systelab/conan/JWTUtils:systelab/images/download.svg)](https://bintray.com/systelab/conan/JWTUtils:systelab/_latestVersion)

# C++ JSON Web Token Utilities

This library provides utilities to generate, parse and validate JWTs (JSON Web Tokens) used to implement an authentication mechanism over a REST API. 


## Setup

### Download using Conan

This library is designed to be installed by making use of [Conan](https://conan.io/) package manager. So, you just need to add the following requirement into your Conan recipe:

```python
def requirements(self):
   self.requires("JWTUtils/1.0.0@systelab/stable")
```

> Version number of this code snipped is set just as an example. Replace it for the desired package to retrieve.

As this package is not available on the conan-center, you will also need to configure a remote repository before installing dependencies:

```bash
conan remote add systelab-bintray https://api.bintray.com/conan/systelab/conan 
```

See Conan [documentation](https://docs.conan.io/en/latest/) for further details on how to integrate this package with your build system.

### Build from sources

See [BUILD.md](BUILD.md) document for details.


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

