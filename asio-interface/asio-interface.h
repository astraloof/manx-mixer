#pragma once

#include <string>
#include "manx-mixer.h"
#include "module.h"

#define DLLAPI __declspec(dllexport)

class AsioModule : public ModuleBase
{
public:
	~AsioModule() = default;

	ModuleData * GetData();

	void Start(ManxMixer * mixer);
	void Stop(void);
};

DLLAPI std::unique_ptr<ModuleBase> CreateInstance(void);