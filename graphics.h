#include <iostream>
#include <SDL.h>
using namespace std;

typedef uint32_t rgb;

class InitError{

};

class graphics {

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture* framebuffer_texture;
	bool quit = false;

public:
	const int width, height;
	rgb* framebuffer;
	
	graphics(string title, int width, int height);
	~graphics();
	
	void start_display();
	void clear(float a, float b, float c);
};