import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain
from conan.tools.files import copy, collect_libs

required_conan_version = ">=2.0.0"


class JWTUtilsConan(ConanFile):
	name = "jwt-utils"
	description = "C++ JSON Web Token Utilities"
	url = "https://github.com/systelab/cpp-jwt-utils"
	homepage = "https://github.com/systelab/cpp-jwt-utils"
	author = "CSW <csw@werfen.com>"
	topics = ("conan", "jwt", "utils", "security")
	license = "MIT"
	settings = "os", "compiler", "build_type", "arch"

	def export_sources(self):
		copy(self, "CMakeLists.txt", src=self.recipe_folder, dst=self.export_sources_folder)
		copy(self, "src/*", src=self.recipe_folder, dst=self.export_sources_folder)
		copy(self, "test/JWTUtilsTest/*", src=self.recipe_folder, dst=self.export_sources_folder)

	def configure(self):
		self.options["openssl/*"].shared = True

	def requirements(self):
		self.requires("rapidjson-adapter/1.2.0")
		self.requires("openssl/3.0.16")
		self.requires("gtest/1.14.0")

	def generate(self):
		tc = CMakeToolchain(self)
		tc.generate()
		deps = CMakeDeps(self)
		deps.generate()

		dep_dst = os.path.join(self.build_folder, "bin", str(self.settings.build_type))
		for dep in self.dependencies.values():
			if dep.package_folder is None:
				continue
			for bindir in dep.cpp_info.bindirs:
				copy(self, "*.dll", src=bindir, dst=dep_dst)
			for libdir in dep.cpp_info.libdirs:
				copy(self, "*.dylib*", src=libdir, dst=os.path.join(self.build_folder, "bin"))
				copy(self, "*.so*", src=libdir, dst=os.path.join(self.build_folder, "bin"))

	def build(self):
		cmake = CMake(self)
		cmake.configure()
		cmake.build()

	def package(self):
		copy(self, "*.h", src=os.path.join(self.source_folder, "src", "JWTUtils"), dst=os.path.join(self.package_folder, "include", "JWTUtils"))
		copy(self, "*JWTUtils.lib", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
		copy(self, "*JWTUtils.pdb", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
		copy(self, "*JWTUtils.a", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)

	def package_info(self):
		self.cpp_info.set_property("cmake_file_name", "JWTUtils")
		self.cpp_info.set_property("cmake_target_name", "JWTUtils::JWTUtils")
		self.cpp_info.libs = collect_libs(self)
