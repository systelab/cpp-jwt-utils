from conans import ConanFile, tools

class JWTUtilsConan(ConanFile):
    name = "JWTUtils"
    description = "C++ JSON Web Token Utilities"
    url = "https://github.com/systelab/cpp-jwt-utils"
    homepage = "https://github.com/systelab/cpp-jwt-utils"
    author = "CSW <csw@werfen.com>"
    topics = ("conan", "jwt", "utils", "security")
    license = "MIT"
    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"
    default_options = "OpenSSL:shared=True"

    def requirements(self):
        self.requires("RapidJSONAdapter/1.0.0@systelab/stable")
        self.requires("OpenSSL/1.0.2n@conan/stable")

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
