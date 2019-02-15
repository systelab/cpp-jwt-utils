#pragma once

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows 10 or later
#define _WIN32_WINNT 0x0A00	// Change this to the appropriate value to target other versions of Windows.
#endif						

#include <stdio.h>
#include <tchar.h>

// STL
#include <memory>
#include <string>

// GoogleTest
#include <gtest/gtest.h>
#include <gmock/gmock.h>
