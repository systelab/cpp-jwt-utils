#include <iostream>
#include <stdexcept>

#include "JWTUtils/Services/ITokenBuilderService.h"
#include "RapidJSONAdapter/JSONAdapter.h"


int main(int argc, char *argv[])
{
	systelab::json::rapidjson::JSONAdapter jsonAdapter;
	systelab::jwt::TokenBuilderService tokenBuilderService(jsonAdapter);
	std::string token = tokenBuilderService.buildJWT("SecretKey", { {"sub", "user"}, {"iat", "20190101T121212"} });
	std::cout << "JWT token generated " << token << std::endl;

    return 0;
}
