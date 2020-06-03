#include <SDL.h>
#include "renderer.h"

CPURenderer::ViewPort port(800, 600);

int main(int argc, char *argv[]) {
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(port.width, port.height, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Hello, world");
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (int i = 0; i < port.width; ++i)
		for (int j = 0; j < port.height; ++j)
		{
			int pos = (i * port.height + j) * 3;
			SDL_SetRenderDrawColor(renderer, port.frame_buffer[pos + 0], port.frame_buffer[pos + 1], port.frame_buffer[pos + 2], 255);
			SDL_RenderDrawPoint(renderer, i, j);
		}
	SDL_RenderPresent(renderer);
	while (1) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}