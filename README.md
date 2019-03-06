[![Build Status](https://travis-ci.org/systelab/cpp-jwt-utils.svg?branch=master)](https://travis-ci.org/systelab/cpp-jwt-utils)
[![Build status](https://ci.appveyor.com/api/projects/status/jtbc93k8i6vtnx56?svg=true)](https://ci.appveyor.com/project/systelab/cpp-jwt-utils)
[![codecov](https://codecov.io/gh/systelab/cpp-jwt-utils/branch/master/graph/badge.svg)](https://codecov.io/gh/systelab/cpp-jwt-utils)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/dd32a177d926495dab93be941a939881)](https://www.codacy.com/app/systelab/cpp-jwt-utils?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=systelab/cpp-jwt-utils&amp;utm_campaign=Badge_Grade)

# C++ JSON Web Token Utilities

This library provides utilities to generate, parse and validate JWTs (JSON Web Tokens) used to implement an authentication mechanism over a REST API. 

## Installation

### Windows
1. Clone this repository into a local folder
2. Create a build folder
```cmd
md build && cd build
```
3. Install 3rd party dependencies through conan
```cmd
conan install .. -s arch=x86
```
4. Configure project using cmake
```cmd
cmake ..
```
5. Build project using VS solution generated on build folder

### Linux

TBD

## Usage

### Build a token

Use the _TokenBuilderService_ class to generate a valid token containing a vector of claims:

`TBD: Code to call the service`

### Parse a token

Use the _TokenParserService_ class to parse a JWT token and retrieve the claims contained on it. It will return false when the provided JWT is not valid.

`TBD: Code to call the service`


