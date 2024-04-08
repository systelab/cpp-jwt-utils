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
		self.requires("RapidJSONAdapter/1.1.6@systelab/stable")
		self.requires("zlib/1.2.13#13c96f538b52e1600c40b88994de240f", override=True)
		self.requires("openssl/3.0.12#1670458f93ec138c3bb6afc65a1cd667")
		if self.settings.arch == "x86":
			self.requires("gtest/1.10.0#e3ded0a841d16e07e6648e38aaa8d8ce")
		else:
			self.requires("gtest/1.10.0#0c895f60b461f8fee0da53a84d659131")

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
