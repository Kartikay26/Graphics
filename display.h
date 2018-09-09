#include <iostream>
#include <map>
#include <SDL.h>
#include <pthread.h>
using namespace std;

typedef uint32_t rgb;

class InitError{

};

class display {

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture* framebuffer_texture;
	pthread_t mainloop_thread;

	int start_time;
	int frames = 0;

	map<int, void (*)(SDL_Event, display*)> callbacks;

public:
	bool quit = false;
	const int width, height;
	rgb* framebuffer;
	
	display(string title, int width, int height);
	
	void start_display();
	void wait_until_quit();
	void register_callback(int e, void(*f)(SDL_Event, display*));

	int getframerate();

	friend void* mainloop(void* gr);
	
	~display();
};