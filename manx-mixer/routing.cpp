#include "routing.h"
#include <iostream>

#define ROTARY_BUFFER_SIZE		2048

RotaryBuffer::RotaryBuffer(int size)
{
	buffer = new double[size];
	this->size = size;
}

RotaryBuffer::~RotaryBuffer(void)
{
	delete[] buffer;
}

void RotaryBuffer::Write(double value)
{
	if (read_head == write_head && instantiated == this->size - 1)
	{
		read_head++;
		if (read_head >= size)
			read_head = 0;
	} else if (instantiated < this->size - 1)
		instantiated++;

	buffer[write_head++] = value;
	if (write_head >= size)
		write_head = 0;
}

double RotaryBuffer::Read(void)
{
	double value = buffer[read_head];
	buffer[read_head++] = 0.;
	if (read_head == write_head)
		read_head--;
	if (read_head >= size)
		read_head = 0;
	return value;
}

AudioSend::AudioSend(int channels)
{
	this->SetChannels(channels);
}

void AudioSend::SetChannels(int channels)
{
	this->size = channels;

	while (this->created < channels)
	{
		this->channels.push_back(new RotaryBuffer(ROTARY_BUFFER_SIZE));
		created++;
	}

	while (this->created > channels)
	{
		RotaryBuffer * del = this->channels.back();
		this->channels.pop_back();

		delete del;
		created--;
	}
}
