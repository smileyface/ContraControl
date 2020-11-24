#include "../basic/switch.h"
#include "../../../Interfaces/common_objects.h"

class LED_Device : public Switch_Device
{
	rgb get_color() { return color; }
	void set_color(uint8_t red, uint8_t green, uint8_t blue)
	{
		color.red = red;
		color.green = green;
		color.blue = blue;
	}

protected:
	rgb color;
};