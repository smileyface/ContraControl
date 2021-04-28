#ifndef GRADIENT_DEVICE_H
#define GRADIENT_DEVICE_H

#include "device.h"


class Gradient_Device: public Device
{
public:
	Gradient_Device() {};
	~Gradient_Device() {};

	float get_position() 
	{
		return state.position;
	}

private:

};


#endif // !GRADIENT_DEVICE_H

