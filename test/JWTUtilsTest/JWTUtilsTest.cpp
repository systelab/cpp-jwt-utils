#include "stdafx.h"


int main(int argc, char* argv[])
{
	::testing::FLAGS_gmock_verbose = "error";
	::testing::InitGoogleTest(&argc, argv);

	int rc = RUN_ALL_TESTS();

	return rc;
}

