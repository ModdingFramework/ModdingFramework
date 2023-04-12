target("ModdingFramework_EXE")
    set_kind("binary")
    set_basename("modding_framework")
    as_windows_app()
    use_wxwidgets()
    add_files("*.cpp", "*.rc")
    add_packages(
        "DLL_Injection",
        "Logging",
        "simpleini",
        "spdlog",
        "StringFormatting",
        "UserInterface"
    )
