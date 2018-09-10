#include <iostream>
#include <Windows.h>
#include <memory>
#include <string>

#include "manx-mixer.h"
#include "module.h"
#include "routing.h"

ManxMixer mixer_instance;
ManxMixer * GetMixerInstance() { return &mixer_instance; }

void ManxMixer::Start(void)
{
	LoadModule("asio-interface.dll");
	UnloadModules();

	AudioSend * send = new AudioSend(2);
	for (int i = 0; i < send->size; i++)
	{
		send->channels[i]->Write(i);
	}
	for (int i = 0; i < send->size; i++)
		std::cout << send->channels[i]->Read() << std::endl;

	send->SetChannels(20);
	for (int i = 0; i < send->size; i++)
		send->channels[19 -i]->Write(i);
	for (int i = 0; i < send->size; i++)
		std::cout << send->channels[i]->Read() << std::endl;

	send->SetChannels(8);
	for (int i = 0; i < send->size; i++)
		for (int d = 0; d < 2201; d++)
			send->channels[i]->Write(d);
	for (int i = 0; i < send->size; i++)
		for (int d = 0; d < 2048; d++)
			std::cout << send->channels[i]->Read() << std::endl;

	system("pause");
}

int main(void)
{
	mixer_instance = ManxMixer();
	mixer_instance.Start();
}