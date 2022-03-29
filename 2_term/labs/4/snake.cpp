#include <stdio.h>
#include <malloc.h>
#include <SDL2/SDL.h>
#include "window.h"

struct Snake {
	Uint8 blockSize = 20;
	SDL_Rect head;
	SDL_Rect* body = NULL;
	SDL_Color color = { 120, 255, 255 };
};

int main(int argc, char* argv[]) {
    init();

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	Snake s;
	int bodyLen = 10;
	s.body = (SDL_Rect*)malloc(sizeof(SDL_Rect) * bodyLen);
	for (int i = 0; i < bodyLen; i++)
	{
		s.body[i] = { i * s.blockSize + s.blockSize, s.blockSize, s.blockSize, s.blockSize };
		SDL_SetRenderDrawColor(ren, s.color.r - i * 20, s.color.g - i * 10, s.color.b - i * 10, 255);
		SDL_RenderFillRect(ren, &s.body[i]);
	}

	SDL_RenderPresent(ren);
	SDL_Delay(1000);

    deInit(0);

	return 0;
}
