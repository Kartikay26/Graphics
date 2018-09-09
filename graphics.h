#include <iostream>

#include "display.h"

class graphics
{
	rgb * fb;
	const int w, h;
public:
	graphics(rgb* framebuffer, int width, int height);
};