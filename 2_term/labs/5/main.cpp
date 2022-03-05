#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

SDL_Window*   win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 800;
int winHgt = 600;

struct Circ
{
    float x;
    float y;
    float r;
    bool isDrawing;
};

void init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow(
        "One more program from Gregory",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        winWdt, winHgt, SDL_WINDOW_SHOWN
    );
    ren = SDL_CreateRenderer(win, -1, 0);
    srand(time(0));
}

void deInit()
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void drawCircle(int x, int y, float r)
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

float randFloat(float min, float max)
{
    return ((float)rand() / RAND_MAX) * (max - min) + min;
}

void generateCircCoords(Circ circs[], int num, float min_r=2.5, float max_r=25)
{
    int border = 10;
    for (int i = 0; i != 10; i++)
    {
        circs[i].r = randFloat(min_r, max_r);
        circs[i].x = randFloat(circs[i].r + border, winWdt - circs[i].r - border);
        circs[i].y = randFloat(circs[i].r + border, winHgt - circs[i].r - border);
        circs[i].isDrawing = false;

        // printf("\nCircle %d\n", i);
        // printf("\tr: %f", circs[i].r);
        // printf("\tx: %f", circs[i].x);
        // printf("\ty: %f", circs[i].y);
        // printf("\tisDrawing: %d", circs[i].isDrawing);
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

int main()
{
    init();
    //mainLoop();
    int num = 10; Circ circs[num];
    createCircCoords(circs, num);
    deInit();

    return 0;
}
