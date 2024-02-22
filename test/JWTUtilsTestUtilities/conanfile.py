import os
from conans import ConanFile, CMake, tools

class JWTUtilsTestUtilitiesConan(ConanFile):
	name = "JWTUtilsTestUtilities"
	description = "Test utilities for C++ JSON Web Token Utilities"
	url = "https://github.com/systelab/cpp-jwt-utils"
	homepage = "https://github.com/systelab/cpp-jwt-utils"
	author = "CSW <csw@werfen.com>"
	topics = ("conan", "jwt", "utils", "security")
	license = "MIT"
	generators = "cmake_find_package"
	settings = "os", "compiler", "build_type", "arch"
	exports_sources = "*", "!build*", "!test_package*"

	def requirements(self):
		self.requires("gtest/1.14.0#4372c5aed2b4018ed9f9da3e218d18b3")

		if ("%s" % self.version) == "None":
			channel = os.environ['CHANNEL'] if "CHANNEL" in os.environ else "stable"
			self.requires(f"JWTUtils/{os.environ['VERSION']}@systelab/{channel}")
		else:
			self.requires(f"JWTUtils/{self.version}@systelab/{self.channel}")

	def build(self):
		cmake = CMake(self)
		cmake.configure()
		cmake.build()

	def imports(self):
		self.copy("*.dll", dst="bin", src="bin")
		self.copy("*.dylib*", dst="bin", src="lib")
		self.copy("*.so*", dst="bin", src="lib")

	def package(self):
		self.copy("*.h", dst="include/JWTUtilsTestUtilities", keep_path=True)
		self.copy("*JWTUtilsTestUtilities.lib", dst="lib", keep_path=False)
		self.copy("*JWTUtilsTestUtilities.pdb", dst="lib", keep_path=False)
		self.copy("*JWTUtilsTestUtilities.a", dst="lib", keep_path=False)

	def package_info(self):
		self.cpp_info.libs = tools.collect_libs(self)
