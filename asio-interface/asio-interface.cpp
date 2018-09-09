#include <iostream>
#include <Windows.h>

#include "asio-interface.h"
#include "asio.h"
#include "asiodrivers.h"

ModuleData asio_module_data
{
	std::string(ASIO_NAME),
	std::string(MANX_VERSION),
	std::string(ASIO_AUTHOR)
};

ModuleData * AsioModule::GetData(void) { return &asio_module_data; }

ManxMixer * mixer_instance;
AsioDrivers asio_drivers;
std::vector<std::string> driver_names;

void AsioModule::Start(ManxMixer * mixer)
{
	mixer_instance = mixer;

	char * names[MAX_DRIVERS];
	for (int i = 0; i < MAX_DRIVERS; i++)
		names[i] = new char[DRIVER_NAME_LENGTH];

	long count = asio_drivers.getDriverNames(&names[0], MAX_DRIVERS);
	for (int i = 0; i < count; i++)
		driver_names.push_back(std::string(names[i]));

	for (int i = 0; i < MAX_DRIVERS; i++)
		delete names[i];
}

void AsioModule::Stop(void)
{
	ASIOStop();
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
