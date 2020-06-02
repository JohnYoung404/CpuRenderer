#include <iostream>
#include <SDL.h>
using namespace  std;

const int WIDTH = 400, HEIGHT = 400; // SDL���ڵĿ�͸�
int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { // ��ʼ��SDL
		cout << "SDL could not initialized with error: " << SDL_GetError() << endl;
	}
	SDL_Window *window = SDL_CreateWindow("Hello SDL world!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI); // ����SDL����
	if (NULL == window) {
		cout << "SDL could not create window with error: " << SDL_GetError() << endl;
	}

	SDL_Event windowEvent; // SDL�����¼�
	while (true) {
		if (SDL_PollEvent(&windowEvent)) { // �Ե�ǰ�������¼�������ѯ��
			if (SDL_QUIT == windowEvent.type) { // ����¼�Ϊ�Ƴ�SDL������ѭ����
				cout << "SDL quit!!" << endl;
				break;
			}
		}
	}
	SDL_DestroyWindow(window); // �Ƴ�SDL����
	SDL_Quit(); // SDL�Ƴ�
	return 0;
}