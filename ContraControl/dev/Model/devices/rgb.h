#include "gradient.h"
class RGB_Lights : public Gradient
{
private:
	std::tuple<Gradient, Gradient, Gradient> rgb;
};