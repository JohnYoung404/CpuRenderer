#include <SDL.h>
#include "renderer.h"

int main(int argc, char *argv[]) {
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(gViewPort.width, gViewPort.height, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "CPU Renderer");
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	CPURenderer::Renderer r;

	while (1) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;

		r.render_loop();

		for (int i = 0; i < gViewPort.width; ++i)
			for (int j = 0; j < gViewPort.height; ++j)
			{
				int pos = (i * gViewPort.height + j) * 3;
				SDL_SetRenderDrawColor(renderer, gViewPort.frame_buffer[pos + 0], gViewPort.frame_buffer[pos + 1], gViewPort.frame_buffer[pos + 2], 255);
				SDL_RenderDrawPoint(renderer, i, j);
			}

		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}