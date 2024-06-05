#include "add-sub.h"

#include "SDL.h"

#ifdef EMSCRIPTEN
// https://www.jamesfmackenzie.com/2019/12/01/webassembly-graphics-with-sdl/
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
using namespace emscripten;
#endif

#include <stdlib.h>
#include <iostream>
#include <string>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* surface;

void drawRandomPixels() {
	if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);

	Uint8* pixels = (Uint8 *)surface->pixels;

	for (int i = 0; i < 1048576; i++) {
		char randomByte = rand() % 255;
		pixels[i] = randomByte;
	}

	if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);

	SDL_Texture* screenTexture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_DestroyTexture(screenTexture);
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(512, 512, 0, &window, &renderer);
	surface = SDL_CreateRGBSurface(0, 512, 512, 32, 0, 0, 0, 0);

#ifdef EMSCRIPTEN
	emscripten_set_main_loop(drawRandomPixels, 0, 1);
#else
	while (1) {
		drawRandomPixels();
		SDL_Delay(16);
	}
#endif 

	int a = add(1, 2);
	int b = sub(2, 1);

	std::cout << "hello world " << std::endl;
	std::cout << "1+2 => " << a << std::endl;
	std::cout << "2-1 => " << b << std::endl;

	return 0;
}