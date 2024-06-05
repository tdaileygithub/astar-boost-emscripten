#include "add-sub.h"

#include "SDL.h"

#include <boost/unordered_set.hpp>

#include <iostream>
#include <string>

unsigned char* byteBuffer = new unsigned char[1024]();
size_t bufferLength = 1024;

#ifdef EMSCRIPTEN
// https://www.jamesfmackenzie.com/2019/12/01/webassembly-graphics-with-sdl/
// https://terminalroot.com/how-to-transform-your-games-into-c-cpp-for-the-web-with-emscripten-sdl2/
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
using namespace emscripten;

val getBytes() {
	return val(typed_memory_view(bufferLength, byteBuffer));
}
#endif

struct Context {
	std::string title;
	int width;
	int height;
	SDL_Renderer* renderer;
	SDL_Event event;	
	SDL_Surface* surface;
	SDL_Window* window;
};

void callback(void* arg) {
	Context* context = static_cast<Context*>(arg);

	uint32_t ticksNow = SDL_GetTicks();

	while (SDL_PollEvent(&context->event)) {
		if (context->event.type == SDL_QUIT) {
			exit(0);
		}
		else if (context->event.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	if (SDL_MUSTLOCK(context->surface)) SDL_LockSurface(context->surface);

	Uint8* pixels = (Uint8*)(context->surface->pixels);

	//1048576
	const int num_pix = context->width * context->height * 4;
	for (int i = 0; i < num_pix; i++) {
		char randomByte = rand() % 255;
		pixels[i] = randomByte;
	}

	if (SDL_MUSTLOCK(context->surface)) SDL_UnlockSurface(context->surface);

	SDL_Texture* screenTexture = SDL_CreateTextureFromSurface(context->renderer, context->surface);

	SDL_RenderClear(context->renderer);
	SDL_RenderCopy(context->renderer, screenTexture, NULL, NULL);
	SDL_RenderPresent(context->renderer);

	SDL_DestroyTexture(screenTexture);

	//std::cout << "yo" << std::endl;
}

int main(int argc, char* argv[])
{
	byteBuffer[0] = 'A';
	byteBuffer[1] = 'B';
	byteBuffer[2] = 'C';

	Context context;
	SDL_Init(SDL_INIT_EVERYTHING);

	context.title = "SDL2 It's Works!";
	context.width = 512;
	context.height = 512;

	context.window = SDL_CreateWindow(
		context.title.c_str(),
		0, 
		0,
		context.width, 
		context.height,
		SDL_WINDOW_SHOWN
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(context.window, -1, 0);
	context.renderer = renderer;
	
	context.surface = SDL_CreateRGBSurface(0, context.width, context.height, 32, 0, 0, 0, 0);

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(callback, &context, -1, 1);
#else
	while (1) {
		callback(&context);
		SDL_Delay(100);
	}
#endif 

	int a = add(1, 2);
	int b = sub(2, 1);

	std::cout << "hello world " << std::endl;
	std::cout << "1+2 => " << a << std::endl;
	std::cout << "2-1 => " << b << std::endl;

	return 0;
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(memory_view_example) {
	function("getBytes", &getBytes);
}
#endif