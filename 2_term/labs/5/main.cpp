#include <SDL2/SDL.h>

SDL_Window*   win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 800;
int winHgt = 600;

void init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow(
        "One more program from Gregory",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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
    float rad = M_PI / 180;
    for (int i = 0, step = 5; i < 360; i += step)
    {
        SDL_RenderDrawLine(
            ren,
            x - cos(i * rad) * r,
            y - sin(i * rad) * r,
            x - cos((i + step) * rad) * r,
            y - sin((i + step) * rad) * r
        );
    }
}

void mainLoop()
{
    SDL_Event event;
    bool isRunning = true;

    while (isRunning)
    {
        SDL_PollEvent(&event);
        }
    }
}

int main()
{
    init();
    mainLoop();
    deInit();

    return 0;
}
