#include "JWTUtilsFactory.h"

#include "Services/Base64EncodeService.h"
#include "Services/HMACSHA256SignatureService.h"
#include "Services/TokenBuilderService.h"
#include "Services/TokenParserService.h"

#include "JSONAdapterInterface/IJSONAdapter.h"


namespace systelab { namespace jwt {

	JWTUtilsFactory::JWTUtilsFactory(json::IJSONAdapter& jsonAdapter)
		:m_jsonAdapter(jsonAdapter)
	{
	}

	JWTUtilsFactory::~JWTUtilsFactory() = default;


	// Token handling services
	std::unique_ptr<ITokenBuilderService> JWTUtilsFactory::buildTokenBuilderService() const
	{
		return std::make_unique<TokenBuilderService>(m_jsonAdapter);
	}

	std::unique_ptr<ITokenParserService> JWTUtilsFactory::buildTokenParserService() const
	{
		return std::make_unique<TokenParserService>(m_jsonAdapter);
	}


	// Helper services
	std::unique_ptr<IBase64EncodeService> JWTUtilsFactory::buildBase64EncodeService() const
	{
		return std::make_unique<Base64EncodeService>();
	}

	std::unique_ptr<IHMACSHA256SignatureService> JWTUtilsFactory::buildHMACSHA256SignatureService() const
	{
		return std::make_unique<HMACSHA256SignatureService>();
	}

}}
