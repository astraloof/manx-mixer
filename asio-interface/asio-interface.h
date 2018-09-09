#pragma once

#define ASIO_NAME				"ASIO Interface"
#define ASIO_AUTHOR			"astraloof"

#define MAX_DRIVERS				32
#define DRIVER_NAME_LENGTH		128

#include <string>
#include "manx-mixer.h"
#include "module.h"

#define DLLAPI __declspec(dllexport)

class AsioModule : public ModuleBase
{
public:
	~AsioModule(void) = default;

	ModuleData * GetData(void);

	void Start(ManxMixer * mixer);
	void Stop(void);
};

DLLAPI std::unique_ptr<ModuleBase> CreateInstance(void);