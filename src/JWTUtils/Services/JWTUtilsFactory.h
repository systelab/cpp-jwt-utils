#pragma once

#include "IJWTUtilsFactory.h"


namespace systelab { namespace json {
	class IJSONAdapter;
}}

namespace systelab { namespace jwt {

	class JWTUtilsFactory : public IJWTUtilsFactory
	{
	public:
		JWTUtilsFactory(json::IJSONAdapter&);
		virtual ~JWTUtilsFactory();

		// Token handling services
		std::unique_ptr<ITokenBuilderService> buildTokenBuilderService() const override;
		std::unique_ptr<ITokenParserService> buildTokenParserService() const override;

		// Helper services
		std::unique_ptr<IBase64EncodeService> buildBase64EncodeService() const override;
		std::unique_ptr<IHMACSHA256SignatureService> buildHMACSHA256SignatureService() const override;

	private:
		json::IJSONAdapter& m_jsonAdapter;
	};

}}

