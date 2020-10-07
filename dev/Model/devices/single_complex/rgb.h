#include "../basic/gradient.h"
class RGB_Lights : public Device
{
private:
	std::tuple<Gradient_Device, Gradient_Device, Gradient_Device> rgb;
};