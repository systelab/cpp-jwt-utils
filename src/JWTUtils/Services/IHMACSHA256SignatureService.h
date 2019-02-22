#pragma once

#include <string>

namespace systelab { namespace jwt {

	class IHMACSHA256SignatureService
	{
	public:
		virtual ~IHMACSHA256SignatureService() {};

		virtual std::string signMessage(const std::string& key, const std::string& msg) const = 0;
	};

}}

