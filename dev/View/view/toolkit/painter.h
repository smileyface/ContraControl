#ifndef COMMON_PAINTER_INTERFACE
#define COMMON_PAINTER_INTERFACE
#include "../View/common/view.h"
#include "lib/dimensions.h"

struct RGB
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};
class Painter
{
public:
    void rectangle(Dimension size, RGB color)
    {

    }
};
#endif // !COMMON_PAINTER_INTERFACE


