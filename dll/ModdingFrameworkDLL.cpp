#include <Logging/Autodetect.h>
//

#include <DLL_Injection/Injected_DLL.h>
#include <UserInterface.h>

#include <filesystem>

// TODO
// #include <ModdingFramework/Runtime.h>

Logging_SetLogFilePath("C:/temp/ModdingFrameworkDLL.log");

// Return the name of the current .dll using GetModuleFileName
// The current hMODULE is avaiable via Injected_DLL::InjectedIntoModule
std::filesystem::path GetDLLPath() {
    char dllPath[MAX_PATH];
    GetModuleFileName(Injected_DLL::InjectedIntoModule, dllPath, MAX_PATH);
    return std::filesystem::path(dllPath);
}

DLL_Main {
    auto dllPath = GetDLLPath();
    // Logging::Config::LogFilePath = logPath.string();

    Logging_Log("Modding Framework DLL loaded");  // <--- do anything!
    Logging_Log("DLL Path: '{}'", dllPath.string());
    Logging_Log("Look, we did a thing!");

    // TODO
    // ModdingFramework::Runtime::Boot();

    // TODO - move eject responsibilities to runtime
    Logging_Log("Ejecting Modding Framework DLL");
    EjectDLL();
}
