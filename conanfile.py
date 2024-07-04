from conans import ConanFile, CMake, tools


class JWTUtilsConan(ConanFile):
	name = "JWTUtils"
	description = "C++ JSON Web Token Utilities"
	url = "https://github.com/systelab/cpp-jwt-utils"
	homepage = "https://github.com/systelab/cpp-jwt-utils"
	author = "CSW <csw@werfen.com>"
	topics = ("conan", "jwt", "utils", "security")
	license = "MIT"
	generators = "cmake_find_package"
	settings = "os", "compiler", "build_type", "arch"
	exports_sources = "*", "!test/JWTUtilsTestUtilities", "!build*", "!*.yml", "!*.xml", "!*.md", "!*.in", "!ci", "!.gitattributes", "!.gitignore", "!test_package*"

	def configure(self):
		self.options["openssl"].shared = True

	def requirements(self):
		self.requires("RapidJSONAdapter/1.1.7@systelab/stable")
		self.requires("zlib/1.3.1@#f52e03ae3d251dec704634230cd806a2", override=True)
		self.requires("openssl/3.0.14@#a723a7081f2ca0811fafd9a6420252db")
		self.requires("gtest/1.14.0#4372c5aed2b4018ed9f9da3e218d18b3")

	def build(self):
		cmake = CMake(self)
		cmake.configure()
		cmake.build()

	def imports(self):
		self.copy("*.dll", dst=("bin/%s" % self.settings.build_type), src="bin")
		self.copy("*.dylib*", dst="bin", src="lib")
		self.copy("*.so*", dst="bin", src="lib")

	def package(self):
		self.copy("*.h", dst="include/JWTUtils", src="src/JWTUtils")
		self.copy("*JWTUtils.lib", dst="lib", keep_path=False)
		self.copy("*JWTUtils.pdb", dst="lib", keep_path=False)
		self.copy("*JWTUtils.a", dst="lib", keep_path=False)

	def package_info(self):
		self.cpp_info.libs = tools.collect_libs(self)
