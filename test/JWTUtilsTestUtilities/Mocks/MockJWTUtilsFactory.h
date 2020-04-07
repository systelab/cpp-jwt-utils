#pragma once

#include "JWTUtils/Services/IJWTUtilsFactory.h"

#include "JWTUtils/Services/IBase64EncodeService.h"
#include "JWTUtils/Services/IHMACSHA256SignatureService.h"
#include "JWTUtils/Services/ITokenBuilderService.h"
#include "JWTUtils/Services/ITokenParserService.h"


namespace systelab { namespace jwt { namespace test_utility {

	class MockJWTUtilsFactory : public IJWTUtilsFactory
	{
	public:
		MockJWTUtilsFactory();
		virtual ~MockJWTUtilsFactory();

		// Token handling services
		MOCK_CONST_METHOD0(buildTokenBuilderServiceProxy, ITokenBuilderService*());
		std::unique_ptr<ITokenBuilderService> buildTokenBuilderService() const override
		{
			return std::unique_ptr<ITokenBuilderService>(buildTokenBuilderServiceProxy());
		}

		MOCK_CONST_METHOD0(buildTokenParserServiceProxy, ITokenParserService* ());
		std::unique_ptr<ITokenParserService> buildTokenParserService() const override
		{
			return std::unique_ptr<ITokenParserService>(buildTokenParserServiceProxy());
		}


		// Helper services
		MOCK_CONST_METHOD0(buildBase64EncodeServiceProxy, IBase64EncodeService* ());
		std::unique_ptr<IBase64EncodeService> buildBase64EncodeService() const override
		{
			return std::unique_ptr<IBase64EncodeService>(buildBase64EncodeServiceProxy());
		}

		MOCK_CONST_METHOD0(buildHMACSHA256SignatureServiceProxy, IHMACSHA256SignatureService* ());
		std::unique_ptr<IHMACSHA256SignatureService> buildHMACSHA256SignatureService() const override
		{
			return std::unique_ptr<IHMACSHA256SignatureService>(buildHMACSHA256SignatureServiceProxy());
		}
	};

}}}

