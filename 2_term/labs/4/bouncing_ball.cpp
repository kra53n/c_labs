#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

SDL_Window*   win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 800;
int winHgt = 600;

const float GRAVIT = 9.807; // 1 pixel is 1 metr

struct Circ{
    float x;
    float y;
    float r;
    float xs=1; // x stretching
    float ys=1; // y stretching
    int xdir = 1; // sign of delta x
    int ydir = 1; // sign of delta y
    float maxh = 0;
};

void deInit(int error)
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    exit(error);
}

void init()
{
    srand(time(0));

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
        deInit(1);
    }

    win = SDL_CreateWindow(u8"Снегопад", SDL_WINDOWPOS_CENTERED,
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

void drawFillCric(Circ c)
{
    for (int w = 0; w < c.r * 2; w++)
    {
        for (int h = 0; h < c.r * 2; h++)
        {
            int dx = c.r - w;
            int dy = c.r - h;
            if ((dx * dx + dy * dy) <= (c.r * c.r))
                SDL_RenderDrawPoint(ren, (c.x + dx) * c.xs, (c.y + dy) * c.ys);
        }
    }
}

void screenCircCollision(Circ &c)
{
    if (c.x - c.r < 0)
    {
        c.xdir *= -1;
        c.x = c.r;
    }
    if (c.y - c.r < c.maxh) {
        c.maxh = (winHgt - c.maxh) * 0.1;
        c.y = c.maxh + c.r;
        c.ydir *= -1;
    }
    if (c.x + c.r > winWdt)
    {
        c.xdir *= -1; c.x = winWdt - c.r;
    }
    if (c.y + c.r > winHgt)
    {
        c.ydir *= -1;
    }
}

void changeCircPos(Circ &c)
{
    screenCircCollision(c);
    c.x += 0 * c.xdir;

    if (c.ys >= 1)
        c.y += GRAVIT * c.ydir;
}

void mainLoop()
{
    SDL_Event ev;

    Circ circ = { winWdt/2, 400, 100, 1, 1 };
    bool isRunning = true;
    while (isRunning)
    {
        SDL_PollEvent(&ev);
        if (ev.type == SDL_QUIT)
            isRunning = false;

        SDL_SetRenderDrawColor(ren, 40, 40, 40, 255);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 80, 73, 69, 255);

        drawFillCric(circ);
        changeCircPos(circ);

        SDL_Delay(10);
        SDL_RenderPresent(ren);
    }
}

int main(int argc, char* argv[])
{
    init();
    mainLoop();
    deInit(0);

    return 0;
}
