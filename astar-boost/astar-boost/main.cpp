#include <boost/lexical_cast.hpp>

#include <iostream>

#include "SDL.h"

#include "maze.h"
#include "random_num_utils.h"

constexpr int SDL_DELAY_MS = 100;

constexpr int NUM_MAZE_COLS = 40;
constexpr int NUM_MAZE_ROWS = 40;
constexpr int NUM_BYTES_PIXEL = 4;

constexpr int MAZE_CELL_WIDTH_PIXEL = 20;
constexpr int MAZE_CELL_HEIGHT_PIXEL = 20;

constexpr int NUM_BYTES_IN_ROW = (NUM_MAZE_COLS * MAZE_CELL_WIDTH_PIXEL * NUM_BYTES_PIXEL);

constexpr size_t bufferLength = 1024;
unsigned char* byteBuffer = new unsigned char[bufferLength]();

std::unique_ptr<maze> m;

#ifdef __EMSCRIPTEN__
// https://www.jamesfmackenzie.com/2019/12/01/webassembly-graphics-with-sdl/
// https://terminalroot.com/how-to-transform-your-games-into-c-cpp-for-the-web-with-emscripten-sdl2/
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
using namespace emscripten;

val getBytes() 
{
	return val(typed_memory_view(bufferLength, byteBuffer));
}
void resetMaze() 
{
	m.reset();
	m = random_maze(NUM_MAZE_COLS, NUM_MAZE_ROWS);
	const bool is_solved = m->solve();
	if (is_solved)
	{
		std::cout << "Solved the maze." << std::endl;
	}
	else
	{
		std::cout << "The maze is not solvable." << std::endl;
	}
	std::cout << *m << std::endl;
}
#endif

enum RGBA {
	GREEN = 1,
	RED = 2,
	ALPHA = 3,
	BLUE = 0
};

class PixelRGBA
{
private:
	unsigned char _red;
	unsigned char _green;
	unsigned char _blue;
	unsigned char _alpha;

public:
	unsigned char Red() const {
		return _red;
	};
	unsigned char Green() const {
		return _green;
	};
	unsigned char Blue() const {
		return _blue;
	};
	unsigned char Alpha() const {
		return _alpha;
	};

	PixelRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
		: _red(r), _green(g), _blue(b), _alpha(a)
	{
	}
};

const PixelRGBA pixel_red(255, 0, 0, 0);
const PixelRGBA pixel_green(0, 255, 0, 0);
const PixelRGBA pixel_blue(0, 0, 255, 0);
const PixelRGBA pixel_black(0, 0, 0, 0);
const PixelRGBA pixel_yellow(255, 255, 0, 0);
const PixelRGBA pixel_white(255, 255, 255, 0);

struct Context {
	std::string title;
	int width;
	int height;
	SDL_Renderer* renderer;
	SDL_Event event;
	SDL_Surface* surface;
	SDL_Window* window;
};

void setPixels(Uint8* pixels, int coln, int coly, PixelRGBA color)
{
	const int col_offset = (NUM_BYTES_IN_ROW * 20 * coly);

	for (int j = 0; j < MAZE_CELL_HEIGHT_PIXEL; j++)
	{
		const int row_offset = (j * NUM_BYTES_IN_ROW);
		const int offset = row_offset + col_offset;

		for (int i = (MAZE_CELL_WIDTH_PIXEL * NUM_BYTES_PIXEL * coln);
			i < (MAZE_CELL_WIDTH_PIXEL * NUM_BYTES_PIXEL * coln) + (MAZE_CELL_WIDTH_PIXEL * NUM_BYTES_PIXEL);
			i += NUM_BYTES_PIXEL)
		{
			pixels[i + (int)(RGBA::BLUE)+offset] = color.Blue();
			pixels[i + (int)(RGBA::GREEN)+offset] = color.Green();
			pixels[i + (int)(RGBA::RED)+offset] = color.Red();
			pixels[i + (int)(RGBA::ALPHA)+offset] = color.Alpha();
		}
	}
}

void callback(void* arg) {
	Context* context = static_cast<Context*>(arg);

	const uint32_t ticksNow = SDL_GetTicks();

	while (SDL_PollEvent(&context->event))
	{
		if (context->event.type == SDL_QUIT)
		{
			exit(0);
		}
		else if (context->event.type == SDL_MOUSEBUTTONDOWN)
		{

		}
	}

	if (SDL_MUSTLOCK(context->surface)) SDL_LockSurface(context->surface);

	Uint8* pixels = (Uint8*)(context->surface->pixels);

	//1048576=512*512*4
	//const int num_pix = context->width * context->height * 4;
	//std::cout << "num pix " << num_pix << std::endl;
	//for (int i = 0; i < num_pix; i++) {
	//	char randomByte = rand() % 255;
	//	pixels[i] = randomByte;
	//}	

	for (vertices_size_type x = 0; x < m->length(0); x++)
	{
		for (vertices_size_type y = 0; y < m->length(1); y++)
		{
			// Put the character representing this point in the maze grid.
			const vertex_descriptor u = { {x, vertices_size_type(y)} };

			const bool is_solution = m->solution_contains(u);
			const bool is_barrier = m->has_barrier(u);

			//clear out previous
			setPixels(pixels, x, y, pixel_black);

			if (is_solution) 
			{
				setPixels(pixels, x, y, pixel_white);
			}
			else
			{
				if (is_barrier) 
				{
					setPixels(pixels, x, y, pixel_red);
				}
				else 
				{
					//background maze
					//setPixels(pixels, x, y, pixel_yellow);
				}
			}
		}
	}

	if (SDL_MUSTLOCK(context->surface)) SDL_UnlockSurface(context->surface);

	SDL_Texture* screenTexture = SDL_CreateTextureFromSurface(context->renderer, context->surface);

	SDL_RenderClear(context->renderer);
	SDL_RenderCopy(context->renderer, screenTexture, NULL, NULL);
	SDL_RenderPresent(context->renderer);

	SDL_DestroyTexture(screenTexture);

	SDL_Delay(SDL_DELAY_MS);
}

//https://www.boost.org/doc/libs/1_70_0/libs/graph/example/astar_maze.cpp

int main(int argc, char* argv[])
{
	global_random_generator.seed(std::time(0));

	m = random_maze(NUM_MAZE_COLS, NUM_MAZE_ROWS);

	const bool is_solved = m->solve();
	if (is_solved)
	{
		std::cout << "Solved the maze." << std::endl;
	}
	else
	{
		std::cout << "The maze is not solvable." << std::endl;
	}
	std::cout << *m << std::endl;

	byteBuffer[0] = 'A';
	byteBuffer[1] = 'B';
	byteBuffer[2] = 'C';

	Context context;

	SDL_Init(SDL_INIT_EVERYTHING);

	context.title = "SDL2 It's Works!";
	context.width = NUM_MAZE_COLS * MAZE_CELL_WIDTH_PIXEL;
	context.height = NUM_MAZE_ROWS * MAZE_CELL_HEIGHT_PIXEL;

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
	while (1) 
	{
		callback(&context);
	}
#endif 

	exit(0);
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(memory_view_example) {
	function("getBytes", &getBytes);
	function("resetMaze", &resetMaze);
}
#endif