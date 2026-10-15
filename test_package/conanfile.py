import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy

required_conan_version = ">=2.0.0"


class JWTUtilsTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires(self.tested_reference_str)

    def layout(self):
        cmake_layout(self)

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

    def test(self):
        cmake = CMake(self)
        cmake.test()
