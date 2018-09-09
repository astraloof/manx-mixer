#include "module.h"
#include "manx-mixer.h"

static std::vector<HINSTANCE> loaded_libraries;
static std::vector<std::unique_ptr<ModuleBase>> loaded_modules;
static int loaded_count = 0;

typedef std::unique_ptr<ModuleBase>(CALLBACK * Module)(void);

void LoadModule(const char * module_name)
{
	HINSTANCE module_lib = LoadLibrary(module_name);
	Module create = (Module)GetProcAddress(module_lib, CREATE_INSTANCE);
	std::unique_ptr<ModuleBase> result = create();

	std::cout << result->GetData()->name << std::endl;
	result->Start(GetMixerInstance());

	loaded_libraries.push_back(module_lib);
	loaded_modules.push_back(std::move(result));
	loaded_count++;
}

void UnloadModules(void)
{
	for (int i = 0; i < loaded_count; i++)
		loaded_modules[i]->Stop();
	loaded_modules.clear();

	for (HINSTANCE lib : loaded_libraries)
		FreeLibrary(lib);
	loaded_libraries.clear();
}
