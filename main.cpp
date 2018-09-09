#include "main.h"

static const int width = 640, height = 480;

int main(int argc, char const *argv[])
{
	graphics g("Lulz", width, height);
	
	g.start_display();

	g.clear(1,1,1);

	return 0;
}