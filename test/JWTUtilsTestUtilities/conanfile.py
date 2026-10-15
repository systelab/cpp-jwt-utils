import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain
from conan.tools.files import copy, collect_libs

required_conan_version = ">=2.0.0"


class JWTUtilsTestUtilitiesConan(ConanFile):
	name = "jwt-utils-test-utilities"
	description = "Test utilities for C++ JSON Web Token Utilities"
	url = "https://github.com/systelab/cpp-jwt-utils"
	homepage = "https://github.com/systelab/cpp-jwt-utils"
	author = "CSW <csw@werfen.com>"
	topics = ("conan", "jwt", "utils", "security")
	license = "MIT"
	settings = "os", "compiler", "build_type", "arch"

	def export_sources(self):
		copy(self, "*", src=self.recipe_folder, dst=self.export_sources_folder, excludes=["build*", "test_package/*"])

	def requirements(self):
		self.requires("gtest/1.14.0")

		if ("%s" % self.version) == "None":
			self.requires(f"jwt-utils/{os.environ['VERSION']}")
		else:
			self.requires(f"jwt-utils/{self.version}")

	def generate(self):
		tc = CMakeToolchain(self)
		tc.generate()
		deps = CMakeDeps(self)
		deps.generate()

		dep_dst = os.path.join(self.build_folder, "bin")
		for dep in self.dependencies.values():
			if dep.package_folder is None:
				continue
			for bindir in dep.cpp_info.bindirs:
				copy(self, "*.dll", src=bindir, dst=dep_dst)
			for libdir in dep.cpp_info.libdirs:
				copy(self, "*.dylib*", src=libdir, dst=dep_dst)
				copy(self, "*.so*", src=libdir, dst=dep_dst)

	def build(self):
		cmake = CMake(self)
		cmake.configure()
		cmake.build()

	def package(self):
		copy(self, "*.h", src=self.source_folder, dst=os.path.join(self.package_folder, "include", "JWTUtilsTestUtilities"))
		copy(self, "*JWTUtilsTestUtilities.lib", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
		copy(self, "*JWTUtilsTestUtilities.pdb", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
		copy(self, "*JWTUtilsTestUtilities.a", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)

	def package_info(self):
		self.cpp_info.set_property("cmake_file_name", "JWTUtilsTestUtilities")
		self.cpp_info.set_property("cmake_target_name", "JWTUtilsTestUtilities::JWTUtilsTestUtilities")
		self.cpp_info.libs = collect_libs(self)
