#pragma once

#include <vector>

class RotaryBuffer
{
public:
	double * buffer;
	int size, read_head, write_head;

	RotaryBuffer(int size);
	~RotaryBuffer(void);

	void Write(double value);
	double Read(void);

private:
	int instantiated;
};

class AudioSend
{
public:
	std::vector<RotaryBuffer *> channels;
	int size;

	AudioSend(int channels);

	void SetChannels(int channels);

private:
	int created;
};