#include "graphics.h"

graphics::graphics(string title, const int width, const int height)
	:width(width),height(height)
{
	framebuffer = new rgb[width*height];
	/* Starting SDL */
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		throw InitError();
	}
	/* Create a Window */
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		throw InitError();
	}
	/* Create a Render */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		throw InitError();
	}
	/* Upload surface to render, and then, free the surface */
	framebuffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, 480);
}

void graphics::start_display(){
	SDL_UpdateTexture(framebuffer_texture , NULL, framebuffer, width * sizeof (uint32_t));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, framebuffer_texture , NULL, NULL);
	SDL_RenderPresent(renderer);

	// MAIN LOOP
	while(not quit)
	{
		SDL_Event e;
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}
	}
}

void graphics::clear(float a, float b, float c){
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			framebuffer[i+j*width] = 255; // todo
		}
	}
}

graphics::~graphics(){
	/* Free all objects*/
	SDL_DestroyTexture(framebuffer_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	/* Quit program */
	SDL_Quit();
}