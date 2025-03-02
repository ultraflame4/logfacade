add_rules("mode.release", "mode.debug")
add_requires("vcpkg::fmt", {alias = "fmt"})

target("logfacade")
    set_kind("headeronly")
    add_headerfiles("logfacade.hpp")
    add_rules("utils.install.cmake_importfiles")
    add_rules("utils.install.pkgconfig_importfiles")
    add_packages("fmt")



package("logfacade")
    set_kind("library", {headeronly = true})
    set_description("The logfacade package")

    add_deps("vcpkg::fmt")

    on_load(function (package)
        package:set("installdir", path.join(os.scriptdir(), package:plat(), package:arch(), package:mode()))
    end)

    on_fetch(function (package)
        local result = {}
        result.includedirs = package:installdir("include")
        return result
    end)
