#pragma once
#define CREATE_INSTANCE "?CreateInstance@@YA?AV?$unique_ptr@VModuleBase@@U?$default_delete@VModuleBase@@@std@@@std@@XZ"

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

#include "manx-mixer.h"

struct ModuleData
{
	std::string name;
	std::string version;
	std::string author;
};

class ModuleBase
{
public:
	virtual ModuleData * GetData() = 0;

	virtual void Start(ManxMixer * mixer) = 0;
	virtual void Stop(void) = 0;
};

void LoadModule(const char * module_name);
void UnloadModules(void);