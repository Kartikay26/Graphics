#include "main.h"

static const int width = 640, height = 480;
display d("Lulz", width, height);	
graphics g(d.framebuffer, width, height);

void key_press_callback(SDL_Event ev, display* p);

// -------------------------------------------------------------

int main()
{
	d.register_callback(SDL_KEYDOWN, key_press_callback);
	
	return 0;
}


// -------------------------------------------------------------
void key_press_callback(SDL_Event ev, display* p){
	cout << "Key Event, ";
	switch(ev.key.keysym.sym){
		case SDLK_UP:
			cout << "UP\n";
			break;
		case SDLK_DOWN:
			cout << "DOWN\n";
			break;
		case SDLK_LEFT:
			cout << "LEFT\n";
			break;
		case SDLK_RIGHT:
			cout << "RIGHT\n";
			break;
	}
}