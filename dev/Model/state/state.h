#ifndef DEVICE_STATE_MACHINE_H
#define DEVICE_STATE_MACHINE_H

#include <vector>
#include <typeinfo> 
#include <cinttypes>

#define INVALID_POSITION -1


struct Device_State
{
	bool initalized = false;
	bool power = false;
	bool valid = false;
	bool transitioning = false;
	float position = INVALID_POSITION;

	uint8_t switches_pack()
	{
		return (initalized <<3)+(power<<2)+(valid<<1)+transitioning;
	}

	void switches_unpack(unsigned char state)
	{
		transitioning = state & 1;
		valid = (state >> 1) & 1;
		power = (state >> 2) & 1;
		initalized = (state >> 3) & 1;
	}

	uint16_t pack()
	{
		uint16_t packed = switches_pack() << 8;
		unsigned char pos = static_cast<int>(position) * 255;
		packed += pos;

		return packed;
	}
	void unpack(uint16_t state)
	{
		position = (state & 0xff)/255.0f;
		switches_unpack(state >> 8);
	}

};






#endif