#include <SDL2/SDL.h>
#include <math.h>

SDL_Window*   win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 800;
int winHgt = 600;

const float RAD = M_PI / 180;

void init()
{
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow(
        u8"Бахтин Грегорионио", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        winWdt, winHgt, SDL_WINDOW_SHOWN
    );
    ren = SDL_CreateRenderer(win, -1, 0);
}

void deInit()
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void drawCircle(int x, int y, int r)
{
    for (int i = 0, step = 5; i < 360; i += step)
    {
        SDL_RenderDrawLine(
            ren,
            x - cos(i * RAD) * r,
            y - sin(i * RAD) * r,
            x - cos((i + step) * RAD) * r,
            y - sin((i + step) * RAD) * r
        );
    }
}

void drawCircles()
{
    for (int i = 0; i < 360; i++)
    {
        SDL_SetRenderDrawColor(ren, 162, 174, 187, 0);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 223, 224, 226, 0);
        drawCircle(winWdt / 2, winHgt / 2, 20);
        drawCircle(winWdt / 2 - cos(i * 22 * RAD) * 20, winHgt / 2 - sin(i * 22 * RAD) * 20, 2);

        drawCircle(winWdt / 2, winHgt / 2, 40);
        drawCircle(winWdt / 2 - cos(i * 15 * RAD) * 40, winHgt / 2 - sin(i * 15 * RAD) * 40, 3);

        drawCircle(winWdt / 2, winHgt / 2, 80);
        drawCircle(winWdt / 2 - cos(i * 10 * RAD) * 80, winHgt / 2 - sin(i * 10 * RAD) * 80, 5);

        drawCircle(winWdt / 2, winHgt / 2, 160);
        drawCircle(winWdt / 2 - cos(i * 3 * RAD) * 160, winHgt / 2 - sin(i * 3 * RAD) * 160, 10);

        drawCircle(winWdt / 2, winHgt / 2, 280);
        drawCircle(winWdt / 2 - cos(i * 1 * RAD) * 280, winHgt / 2 - sin(i * 1 * RAD) * 280, 15);

        SDL_RenderPresent(ren);
        SDL_Delay(20);
    }
}

int main()
{
    init();
    drawCircles();
    deInit();

    return 0;
}
