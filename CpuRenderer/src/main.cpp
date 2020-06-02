#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SDL.h>
#include <memory>


const int WIDTH = 800;
const int HEIGHT = 600;

/*
struct CpuColorOutput
{
	unsigned char buffer[WIDTH][HEIGHT][3];

	void set_pixel(int pos_x, int pos_y, unsigned char channel, unsigned char value)
	{
		buffer[pos_x][pos_y][channel] = value;
	}
};

static CpuColorOutput colorOutput;

void fill_buffer() {
	for (unsigned int pixelY = 0; pixelY < HEIGHT; ++pixelY) {
		for (unsigned int pixelX = 0; pixelX < WIDTH; ++pixelX) {
			colorOutput.set_pixel(pixelX, pixelY, 0, 255);
			colorOutput.set_pixel(pixelX, pixelY, 2, 255);
		}
	}
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "CPU Renderer", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glViewport(0, 0, WIDTH, HEIGHT);

	fill_buffer();

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, colorOutput.buffer);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
    return 0;
}*/

int main(int argc, char* args[])
{
	//将要渲染的窗口
	SDL_Window* window = NULL;

	//窗口含有的surface
	SDL_Surface* screenSurface = NULL;

	//初始化SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//创建 window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//获取 window surface
			screenSurface = SDL_GetWindowSurface(window);

			//用白色填充surface
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//更新surface
			SDL_UpdateWindowSurface(window);

			//延迟两秒
			SDL_Delay(2000);
		}
	}
	//销毁 window
	SDL_DestroyWindow(window);

	//退出 SDL subsystems
	SDL_Quit();

	return 0;
}