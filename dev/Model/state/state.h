#ifndef DEVICE_STATE_MACHINE_H
#define DEVICE_STATE_MACHINE_H

#include <cstdint>

struct Device_State
{
	bool initalized = false;
	bool power = false;
	bool valid = false;

	uint8_t switches_pack()
	{
		return (initalized <<2)+(power<<1)+valid;
	}

	void switches_unpack(unsigned char state)
	{
		valid = state & 1;
		power = state >> 1 & 1;
		initalized = state >> 2 & 1;
	}

	uint16_t pack()
	{
		uint16_t packed = switches_pack();

		return packed;
	}
	void unpack(uint16_t state)
	{
		switches_unpack(state >> 8);
	}

};






#endif