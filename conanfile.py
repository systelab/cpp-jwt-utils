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
    options = {"gtest": ["1.7.0", "1.8.1"], "OpenSSL": ["1.0.2n"]}
    default_options = {"gtest":"1.8.1", "OpenSSL":"1.0.2n"}
    exports_sources = "*"

    def configure(self):
        self.options["OpenSSL"].shared = True
        self.options["RapidJSONAdapter"].gtest = self.options.gtest

    def requirements(self):
        self.requires("RapidJSONAdapter/1.0.5@systelab/stable")
        self.requires(("OpenSSL/%s@conan/stable") % self.options.OpenSSL)

    def build_requirements(self):
        if self.options.gtest == "1.7.0":
            self.build_requires("gtest/1.7.0@systelab/stable")
        else:
            self.build_requires("gtest/1.8.1@bincrafters/stable")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy("*.so*", dst="bin", src="lib")

    def package(self):
        self.copy("*.h", dst="include/JWTUtils", src="src/JWTUtils")
        self.copy("*JWTUtils.lib", dst="lib", keep_path=False)
        self.copy("*JWTUtils.pdb", dst="lib", keep_path=False)
        self.copy("*JWTUtils.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
