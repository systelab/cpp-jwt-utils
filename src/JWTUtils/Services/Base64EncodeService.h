#pragma once

#include "IBase64EncodeService.h"


namespace systelab { namespace jwt {

	class Base64EncodeService : public IBase64EncodeService
	{
	public:
		Base64EncodeService();
		virtual ~Base64EncodeService();

		std::string encodeString(const std::string&) const;
		std::string decodeString(const std::string&) const;

	private:
		bool isBase64(unsigned char c) const;
	};

}}

