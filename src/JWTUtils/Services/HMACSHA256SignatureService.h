#pragma once

#include "IHMACSHA256SignatureService.h"


namespace systelab { namespace jwt {

	class HMACSHA256SignatureService : public IHMACSHA256SignatureService
	{
	public:
		HMACSHA256SignatureService();
		virtual ~HMACSHA256SignatureService();

		std::string signMessage(const std::string& key, const std::string& msg) const;
	};

}}

