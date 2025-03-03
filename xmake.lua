add_rules("mode.release", "mode.debug")
add_requires("vcpkg::fmt", {alias = "fmt"})

target("logfacade")
    set_kind("headeronly")
    add_headerfiles("logfacade.hpp")
    add_rules("utils.install.cmake_importfiles")
    add_rules("utils.install.pkgconfig_importfiles")
    add_packages("fmt")
