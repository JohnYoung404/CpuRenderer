#include <stdlib.h>
#include <SDL.h>

#define WINDOW_WIDTH 600

int main(int argc, char *argv[]) {
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;
	int i;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Hello, world");
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (i = 0; i < WINDOW_WIDTH; ++i)
		SDL_RenderDrawPoint(renderer, i, i);
	SDL_RenderPresent(renderer);
	while (1) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}