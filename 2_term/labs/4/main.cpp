#include <SDL2/SDL.h>

SDL_Window*   win = NULL;
SDL_Renderer* ren = NULL;
int win_wdt = 800;
int win_hgt = 600;

void init()
{
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow(
        u8"Бахтин Грегорионио", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        win_wdt, win_hgt, SDL_WINDOW_SHOWN
    );
    ren = SDL_CreateRenderer(win, -1, 0);
}

void deInit()
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

int main()
{
    init();
    deInit();

    return 0;
}
