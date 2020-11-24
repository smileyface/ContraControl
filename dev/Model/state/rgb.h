#ifndef MODEL_RBG_STATE
#define MODEL_RGB_STATE


class rgb
{
public:
	rgb(unsigned int byte_string)
	{
		m_red = byte_string % 256;
		m_green = (byte_string << 8) % 256;
		m_blue = (byte_string << 16) % 256;
	}
	rgb(unsigned char byte_array[3])
	{
		m_red = byte_array[0];
		m_green = byte_array[1];
		m_blue = byte_array[2];
	}
	rgb(unsigned char red, unsigned char green, unsigned char blue)
	{
		m_red = red;
		m_green = green;
		m_blue = blue;
	}
private:
	unsigned char m_red;
	unsigned char m_green;
	unsigned char m_blue;

};
#endif // !MODEL_RBG_STATE