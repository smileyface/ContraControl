#ifndef GRADIENT_DEVICE_H
#define GRADIENT_DEVICE_H

#include "device.h"

class Gradient_Device: public Device
{
public:
	Gradient_Device() { position = 0.0; };
	~Gradient_Device() {};

	void set_position(float new_position)
	{
		position = new_position;
	};
	float get_position() 
	{
		return position;
	}

	virtual std::string type_id() { return "Gradient"; };
private:
	float position;

};


#endif // !GRADIENT_DEVICE_H

