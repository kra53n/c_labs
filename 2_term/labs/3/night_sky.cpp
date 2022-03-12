#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

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

void drawStarts(SDL_Renderer* ren, int x, int y, float step, int scale)
{
    float rad = M_PI / 180;
    for (float angle = 0; angle < 270; angle += step)
    {
        float r = 45 * sin(angle / sqrt(2)) * scale;
        SDL_RenderDrawLine(
                ren,
                sin(angle * rad) * r + x,
                cos(angle * rad) * r + y,
                sin((angle + step) * rad) * r + x,
                cos((angle + step) * rad) * r + y
        );
        r += step;
    }
}

void drawNightSky(SDL_Renderer* ren)
{
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 10);
    SDL_RenderClear(ren);

    SDL_SetRenderDrawColor(ren, 163, 141, 214, 0);

    drawStarts(ren, winWdt + 50, -30, 0.1, 35);
    drawStarts(ren, 0 - 40, winHgt / 2 - 20, 0.4, 20);
}

int main()
{
    init();
    drawNightSky(ren);
    SDL_RenderPresent(ren);
    SDL_Delay(5000);
    deInit(0);

    return 0;
}
