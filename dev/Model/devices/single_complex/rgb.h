#include "../basic/gradient.h"
class RGB_Lights : public Gradient_Device
{
private:
	std::tuple<Gradient_Device, Gradient_Device, Gradient_Device> rgb;
};