#include <iostream>
#include <SDL.h>
using namespace  std;

const int WIDTH = 400, HEIGHT = 400; // SDL窗口的宽和高
int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { // 初始化SDL
		cout << "SDL could not initialized with error: " << SDL_GetError() << endl;
	}
	SDL_Window *window = SDL_CreateWindow("Hello SDL world!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI); // 创建SDL窗口
	if (NULL == window) {
		cout << "SDL could not create window with error: " << SDL_GetError() << endl;
	}

	SDL_Event windowEvent; // SDL窗口事件
	while (true) {
		if (SDL_PollEvent(&windowEvent)) { // 对当前待处理事件进行轮询。
			if (SDL_QUIT == windowEvent.type) { // 如果事件为推出SDL，结束循环。
				cout << "SDL quit!!" << endl;
				break;
			}
		}
	}
	SDL_DestroyWindow(window); // 推出SDL窗体
	SDL_Quit(); // SDL推出
	return 0;
}