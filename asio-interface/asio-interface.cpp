#define MODULE_NAME				"ASIO Interface"
#define MODULE_VERSION			"1.0.0"
#define MODULE_AUTHOR			"astraloof"

#include <iostream>
#include <Windows.h>

#include "asio-interface.h"

ModuleData asio_module_data
{
	std::string(MODULE_NAME),
	std::string(MODULE_VERSION),
	std::string(MODULE_AUTHOR)
};

ModuleData * AsioModule::GetData() { return &asio_module_data; }
ManxMixer * mixer_instance;

void AsioModule::Start(ManxMixer * mixer)
{
	mixer_instance = mixer;
	std::cout << "ASIO Start\n";
}

void AsioModule::Stop(void)
{
	std::cout << "ASIO Stop\n";
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
	}

    return TRUE;
}

DLLAPI std::unique_ptr<ModuleBase> CreateInstance(void)
{
	return std::unique_ptr<ModuleBase>(new AsioModule);
}
