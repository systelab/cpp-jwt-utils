import os
from conans import ConanFile, tools

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
    options = {"gtest": ["1.7.0", "1.8.1", "1.10.0"], "openssl": ["1.0.2n", "1.0.2s", "1.1.1g", "1.1.1k"]}
    default_options = {"gtest":"1.10.0", "openssl":"1.1.1k"}
    exports_sources = "*", "!build-*"

    def configure(self):
        self.options["JWTUtils"].gtest = self.options.gtest
        self.options["JWTUtils"].openssl = self.options.openssl

    def requirements(self):
        if self.options.gtest == "1.7.0":
            self.requires("gtest/1.7.0@systelab/stable")
        elif self.options.gtest == "1.8.1":
            self.requires("gtest/1.8.1")
        else:
            self.requires("gtest/1.10.0#0c895f60b461f8fee0da53a84d659131")

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
