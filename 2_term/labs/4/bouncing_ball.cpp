#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 800;
int winHgt = 600;

struct Circ {
    float x;
    float y;
    float r;
    float x_speed = 1;
    float y_speed = 1;
    float acceleration = 1;
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

    win = SDL_CreateWindow("BB | Bouncing Ball", SDL_WINDOWPOS_CENTERED,
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
            if (dx * dx + dy * dy <= c.r * c.r)
                SDL_RenderDrawPoint(ren, (c.x + dx), (c.y + dy));
        }
    }
}

void screenCircCollision(Circ& c)
{
    float deformation_speed = 1 * fabs(c.y_speed);

    // horizontal collision
    if (c.x - c.r < 0)
    {
        c.x_speed *= -1;
        c.x = c.r;
    }
    if (c.x + c.r > winWdt)
    {
        c.x_speed *= -1; c.x = winWdt - c.r;
    }

    // vertical collision
    if (c.y - c.r < 0)
    {
        c.y_speed *= -1;
    }

    if (c.y + c.r > winHgt)
    {

        c.y = winHgt - c.r - 1;
        c.y_speed *= -0.8;
        if (fabs(c.y_speed) <= 1.777)
            c.y_speed = -70;
    }
}

void updateCirc(Circ& c)
{
    c.x += 0 * c.x_speed;
    c.y_speed += c.acceleration;
    c.y += c.y_speed;

    screenCircCollision(c);
}

void mainLoop()
{
    SDL_Event ev;

    Circ circ = { winWdt / 2, 200, 50, 1, 1 };

    bool isRunning = true;
    while (isRunning)
    {
        SDL_PollEvent(&ev);
        if (ev.type == SDL_QUIT)
            isRunning = false;
        updateCirc(circ);

        SDL_SetRenderDrawColor(ren, 40, 40, 40, 255);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 80, 73, 69, 255);

        drawFillCric(circ);

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