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

void drawCirc(float x, float y, float r)
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

Circ fillCircRandomly(float border, float min_r, float max_r)
{
    Circ circ;
    circ.r = randFloat(min_r, max_r);
    circ.x = randFloat(circ.r + border, winWdt - circ.r - border);
    circ.y = randFloat(circ.r + border, winHgt - circ.r - border);
    circ.isDrawing = true;
    return circ;
}

void fillCircsElsNULL(Circ circs[], int num)
{
    for (int i = 0; i < num; i++)
    {
        circs[i].x = NULL;
        circs[i].y = NULL;
        circs[i].r = NULL;
        circs[i].isDrawing = NULL;
    }
}

void generateCircCoords(Circ circs[], int num, float min_r=2.5, float max_r=50)
{
    float border = 10;

    circs[0] = fillCircRandomly(border, min_r, max_r);

    for (int i = 1; i != num; i++)
    {
        while (true)
        {
            circs[i] = fillCircRandomly(border, min_r, max_r);

            bool flag = true;
            for (int j = 0; j < i; j++)
            {
                bool isInserct = (circs[j].x - circs[i].x) * (circs[j].x - circs[i].x) +
                            (circs[j].y - circs[i].y) * (circs[j].y - circs[i].y) <
                            (circs[j].r + circs[i].r) * (circs[j].r + circs[i].r);
                
                if (isInserct)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                break;
        }
    }
}

void drawCircs(Circ circs[], int num)
{
    for (int i = 0; i < num; i++)
        if (circs[i].isDrawing)
            drawCirc(circs[i].x, circs[i].y, circs[i].r);
}

void mainLoop()
{
    SDL_Event event;
    bool isRunning = true;
    int num = 10; Circ circs[num]; fillCircsElsNULL(circs, num); generateCircCoords(circs, num);

    while (isRunning)
    {
        SDL_PollEvent(&event);

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
        drawCircs(circs, num);
        SDL_RenderPresent(ren);

        if (event.type == SDL_QUIT)
            isRunning = false;
    }
}

int main()
{
    init();
    mainLoop();
    //int num = 10; Circ circs[num];
    //generateCircCoords(circs, num);
    deInit();

    return 0;
}
