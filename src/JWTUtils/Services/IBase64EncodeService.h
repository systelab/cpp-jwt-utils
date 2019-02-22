#pragma once

#include <string>

namespace systelab { namespace jwt {

	class IBase64EncodeService
	{
	public:
		virtual ~IBase64EncodeService() {};

		virtual std::string encodeString(const std::string&) const = 0;
		virtual std::string decodeString(const std::string&) const = 0;
	};

}}
