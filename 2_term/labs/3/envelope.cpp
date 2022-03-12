#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window*   win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 800;
int winHgt = 600;
int winWdt2 = winWdt / 2;
int winHgt2 = winHgt / 2;

void deInit(char error)
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    exit(error);
}

void init()
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
        deInit(1);
    }

    win = SDL_CreateWindow(u8"Бахтин", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, winWdt, winHgt, SDL_WINDOW_SHOWN
    );
    if (win == NULL)
    {
        printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
        deInit(1);
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL)
    {
        printf("SDL couldn't create renderer! SDL_Error: %s\n", SDL_GetError());
        deInit(1);
    }
}

void drawEnvelope(SDL_Renderer* ren)
{
    SDL_SetRenderDrawColor(ren, 94, 81, 125, 0);
    SDL_RenderClear(ren);

    SDL_Rect rect = {
        winWdt / 5,
        winHgt / 5,
        winWdt - winWdt / 2.5,
        winHgt - winHgt / 2.5
    };

    SDL_SetRenderDrawColor(ren, 123, 106, 161, 0);
    SDL_RenderDrawLine(ren, rect.x, rect.y + rect.h,
        rect.x + rect.w / 2, rect.y + rect.h / 2);
    SDL_RenderDrawLine(ren, rect.x + rect.w / 2, rect.y + rect.h / 2,
            rect.x + rect.w, rect.y + rect.h);

    SDL_SetRenderDrawColor(ren, 145, 126, 192, 0);
    SDL_RenderDrawLine(ren, rect.x, rect.y,
        rect.x + rect.w / 2, rect.y + rect.h / 2);
    SDL_RenderDrawLine(ren, rect.x + rect.w / 2 , rect.y + rect.h / 2,
            rect.x + rect.w, rect.y);

    SDL_SetRenderDrawColor(ren, 163, 141, 214, 0);
    SDL_RenderDrawRect(ren, &rect);
}

int main()
{
    init();
    drawEnvelope(ren);
    SDL_RenderPresent(ren);
    SDL_Delay(5000);
    deInit(0);

    return 0;
}
