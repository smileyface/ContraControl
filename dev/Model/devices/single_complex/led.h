#include "../basic/switch.h"

struct RGB
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

class LED_Device : public Switch_Device
{
	RGB get_color() { return color; }
	void set_color(uint8_t red, uint8_t green, uint8_t blue)
	{
		color.red = red;
		color.green = green;
		color.blue = blue;
	}

protected:
	RGB color;
};