add_rules("mode.debug", "mode.release")
set_toolchains("msvc")
set_languages("c++20")
set_arch("x86")
set_defaultplat("windows")
set_defaultmode("x86")

add_repositories("MrowrLib https://github.com/MrowrLib/package-repo.git")
add_repositories("ModdingFramework https://github.com/ModdingFramework/package-repo.git")

add_requires(
    "DLL_Injection",
    "Logging",
    "simpleini",
    "spdlog",
    "StringFormatting",
    "UserInterface",
    "vcpkg::wxwidgets"
)

function as_windows_app()
    add_ldflags("/subsystem:windows")
    add_ldflags("/entry:WinMainCRTStartup", {force = true})
end 

function use_wxwidgets()
    local vcpkg_triplet = "x86-windows-static"
    local vcpkg_root = os.getenv("VCPKG_ROOT")
    add_packages("vcpkg::wxwidgets")
    add_includedirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "include"))
    add_linkdirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "lib"))
    add_links("kernel32", "user32", "gdi32", "comdlg32", "winspool", "winmm", "shell32", "comctl32", "ole32", "oleaut32", "uuid", "rpcrt4", "advapi32", "wsock32", "wininet", "libpng16", "nanosvg", "nanosvgrast", "zlib")
end

includes("**/xmake.lua")
