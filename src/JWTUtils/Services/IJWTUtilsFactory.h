#pragma once

#include <memory>


namespace systelab { namespace jwt {

	class IBase64EncodeService;
	class IHMACSHA256SignatureService;
	class ITokenBuilderService;
	class ITokenParserService;

	class IJWTUtilsFactory
	{
	public:
		virtual ~IJWTUtilsFactory() = default;

		// Token handling services
		virtual std::unique_ptr<ITokenBuilderService> buildTokenBuilderService() const = 0;
		virtual std::unique_ptr<ITokenParserService> buildTokenParserService() const = 0;

		// Helper services
		virtual std::unique_ptr<IBase64EncodeService> buildBase64EncodeService() const = 0;
		virtual std::unique_ptr<IHMACSHA256SignatureService> buildHMACSHA256SignatureService() const = 0;
	};

}}

