#include "display.h"

void quit_callback(SDL_Event ev, display* d){
	d->quit = true;
}

display::display(string title, const int width, const int height)
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

	// set initial time
	start_time = time(NULL);

	this->register_callback(SDL_QUIT, quit_callback); // only default callback
	this->start_display();
}

int display::getframerate(){
	int time_new = time(NULL);
	if(time_new != start_time)
		return frames/(time(NULL) - start_time);
	else
		return -1;
}

void display::register_callback(int e, void (*f)(SDL_Event, display*)){
	callbacks[e] = f;
}

void* mainloop(void* gr){
	display* g = (display*) gr;
	while(not g->quit)
	{
		SDL_Event e;
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if (g->callbacks[e.type] != nullptr)
				g->callbacks[e.type](e, g);
		}
	 	SDL_UpdateTexture(g->framebuffer_texture , NULL, g->framebuffer, g->width * sizeof (uint32_t));
	 	SDL_RenderClear(g->renderer);
		SDL_RenderCopy(g->renderer, g->framebuffer_texture , NULL, NULL);
		SDL_RenderPresent(g->renderer);
		g->frames ++;
	}
	return NULL;
}

void display::start_display(){
	// MAIN LOOP
	pthread_create(&mainloop_thread, NULL, mainloop, this);
}

void display::wait_until_quit(){
	pthread_join(mainloop_thread, NULL);
}

display::~display(){
	this->wait_until_quit();
	/* Free all objects*/
	SDL_DestroyTexture(framebuffer_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	/* Quit program */
	SDL_Quit();
}