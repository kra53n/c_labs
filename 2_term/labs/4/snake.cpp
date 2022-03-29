#include <stdio.h>
#include <malloc.h>
#include <SDL2/SDL.h>
#include "window.h"

struct Snake {
	Uint8 blockSize = 14;
	SDL_Rect head;
	SDL_Rect* body = NULL;
	SDL_Color color = { 120, 255, 255 };
};

struct Scene {
	Snake snake;
};

int processEvents(SDL_Event ev, Scene &scene) {
		if (ev.type == SDL_QUIT) 
			return 0;
}

int gameLoop() {
	SDL_Event ev;
	
	int bodyLen = 0;
	Scene scene;

	while (true) {
		SDL_PollEvent(&ev);
		processEvents(ev, scene);

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	Snake s;
	s.body = (SDL_Rect*)realloc(s.body, sizeof(SDL_Rect) * ++bodyLen);
	for (int i = 0; i < bodyLen; i++) {
		s.body[i] = { i * s.blockSize + s.blockSize, s.blockSize, s.blockSize, s.blockSize };
		SDL_SetRenderDrawColor(ren, s.color.r - i * 1, s.color.g - i * 4.5, s.color.b - i * 4.5, 255);
		SDL_RenderFillRect(ren, &s.body[i]);
	}

		SDL_RenderPresent(ren);
		SDL_Delay(60);
	}
}

int main(int argc, char* argv[]) {
    init();
	gameLoop();
    deInit(0);

	return 0;
}
