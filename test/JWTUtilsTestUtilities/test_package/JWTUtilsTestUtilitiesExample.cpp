#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING  1

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>

#include "JWTUtilsTestUtilities/Mocks/MockTokenBuilderService.h"


int main(int argc, char *argv[])
{
	systelab::jwt::test_utility::MockTokenBuilderService tokenBuilderService;
    std::cout << "JWTUtils test utilities work as expected" << std::endl;

    return 0;
}
