#include <SDL.h>
#include "mesh.h"
#include "renderer.h"
#include <cstdlib>

using CPURenderer::ViewPort;

int main(int argc, char *argv[]) {
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Texture* texture;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("CPU Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ViewPort::instance.width, ViewPort::instance.height, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, ViewPort::instance.width, ViewPort::instance.height);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	CPURenderer::Renderer r;
	r.mainCamera.LookAt({ 0.0f, 200.0f, 1000.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 200.0f, 0.0f });
	r.mainCamera.Project(45.0f, (float)ViewPort::instance.width / ViewPort::instance.height, 1.0f, 10000.0f);
	r.mainCamera.ScreenMapping(ViewPort::instance);
	r.mainCamera.RotateX(45.0f);
	r.mainCamera.slide(0.0f, 0.0f, 400.f);
	r.mainCamera.CalViewMat();
	
	CPURenderer::Mesh ms;
	ms.loadMesh("res/cat.obj");
	ms.loadTexture("res/cpp_logo.png");

	//r.mainCamera.LookAt({ 0.0f, -10.0f, 100.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	//r.mainCamera.Project(45.0f, (float)ViewPort::instance.width / ViewPort::instance.height, 1.0f, 10000.0f);
	//r.mainCamera.ScreenMapping(ViewPort::instance);
	////r.mainCamera.RotateX(45.0f);
	////r.mainCamera.slide(0.0f, 0.0f, 400.f);
	////r.mainCamera.CalViewMat();
	//
	//CPURenderer::Mesh ms;
	//ms.loadMesh("res/cat2.obj");
	//ms.loadTexture("res/cat2.png");

	bool mouseDown = false;
	int lastPosX, lastPosY;

	while (1) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			lastPosX = event.button.x;
			lastPosY = event.button.y;
			mouseDown = true;
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			mouseDown = false;
		}
		else if (mouseDown && event.type == SDL_MOUSEMOTION)
		{
			int dx = event.button.x - lastPosX;
			int dy = event.button.y - lastPosY;

			r.mainCamera.RotateX(-(float)dx / 5.0f);
			r.mainCamera.RotateY((float)dy / 5.0f);
			lastPosX = event.button.x;
			lastPosY = event.button.y;
			r.mainCamera.CalViewMat();
		}
		else if (event.type == SDL_MOUSEWHEEL)
		{
			if (event.wheel.y > 0)
			{
				r.mainCamera.slide(0.0f, 0.0f, 25.f);
			}
			else if(event.wheel.y < 0)
			{
				r.mainCamera.slide(0.0f, 0.0f, 25.f);
			}
			r.mainCamera.CalViewMat();
		}

		r.render_loop();
		r.draw_wireframe_mesh(ms, CPURenderer::Color::white);

		SDL_UpdateTexture(texture, NULL, ViewPort::instance.frame_buffer, ViewPort::instance.width * 4 * sizeof(unsigned char));
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}