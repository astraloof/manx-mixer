#include <iostream>
#include <Windows.h>
#include <memory>
#include <string>

#include "manx-mixer.h"
#include "module.h"

ManxMixer mixer_instance;
ManxMixer * GetMixerInstance() { return &mixer_instance; }

void ManxMixer::Start()
{
	LoadModule("asio-interface.dll");
	UnloadModules();
}

int main(void)
{
	mixer_instance = ManxMixer();
	mixer_instance.Start();
}