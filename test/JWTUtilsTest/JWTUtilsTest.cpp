#include "stdafx.h"


int _tmain(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	int rc = RUN_ALL_TESTS();

	return rc;
}

