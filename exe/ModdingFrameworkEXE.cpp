#include <DLL_Injection/DLL_Injector.h>
#include <Logging.h>
#include <SimpleIni.h>
#include <StringFormatting.h>
#include <UserInterface/UI_Main.h>

#include <filesystem>

// Returns the name of the currently running executable (using GetModuleName)
std::filesystem::path GetExecutablePath() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    return std::filesystem::path(buffer);
}

// Get the game= value from the .ini file under the [ModdingFramework] section
std::filesystem::path GetTargetExecutable(const std::filesystem::path& iniPath) {
    CSimpleIniA ini;
    ini.LoadFile(iniPath.c_str());
    return ini.GetValue("Modding Framework", "game", "");
}

// Start the target executable as defined in the .ini (if not already running)
// and inject the specified DLL into it
void StartModdingFramework(std::filesystem::path& game, std::filesystem::path& dll) {
    Log("Modding Framework starting...");
    Log("Injecting DLL '{}' into game '{}'", dll.string(), game.string());
    DLL_Injector::InjectDLL(game.string(), dll.string());
    Log("Injected DLL '{}' into game '{}'", dll.string(), game.string());
    Log("Modding Framework started");
}

UI_Main {
    auto exePath = GetExecutablePath();
    auto dllPath = exePath.replace_extension("dll");
    auto iniPath = exePath.replace_extension("ini");
    auto logPath = exePath.replace_extension("log");

    Logging::Config::LogFilePath = logPath.string();
    Log("Modding Framework loading...");

    if (!std::filesystem::exists(dllPath)) {
        Log("DLL '{}' does not exist, exiting...", dllPath.string());
        return 1;
    }
    if (!std::filesystem::exists(iniPath)) {
        Log("INI file '{}' does not exist, exiting...", iniPath.string());
        return 1;
    }

    auto game = GetTargetExecutable(iniPath);
    if (game.empty()) {
        Log("No game specified in [Modding Framework] section of .ini file '{}', exiting...",
            iniPath.string());
        return 1;
    }

    StartModdingFramework(game, dllPath);

    return 0;
}

// Set this based on the modding_framework.ini file
// Use MessageBoxA to show errors before the logger is initialized
// SetLogFilePath("Modding/Logs/ModdingFramework/modding_framework.exe.log");

// int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
//     // Log("Modding Framework EXE started");

//     // auto dllPath = std::filesystem::path("modding_framework.dll");
//     // if (!std::filesystem::exists(dllPath)) {
//     //     Log("DLL '{}' does not exist, exiting...", dllPath.string());
//     //     return 1;
//     // }

//     // if (DLL_Injector::Util::IsProcessRunning(game)) {
//     //     Log("Game '{}' is running, injecting DLL...", game);
//     //     DLL_Injector::InjectDLL(game, "modding_framework.dll");
//     // } else {
//     //     Log("Game '{}' is not running, starting it... [or, okay, we *will* later]", game);
//     // }

//     return 0;
// }
