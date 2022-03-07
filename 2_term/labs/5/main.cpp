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

void generateCircCoords(Circ circs[], int num, float min_r=2.5, float max_r=25)
{
    int border = 10;
    for (int i = 0; i != num; i++)
    {
        bool intersect = true;
        if (i > 0) while (intersect)
        {
            circs[i].r = randFloat(min_r, max_r);
            circs[i].x = randFloat(circs[i].r + border, winWdt - circs[i].r - border);
            circs[i].y = randFloat(circs[i].r + border, winHgt - circs[i].r - border);
            circs[i].isDrawing = true;

            for (int j = 0; j < i; j++)
            {
                if (!(circs[j].x - circs[j].r <= circs[i].x + circs[i].r && circs[j].x + circs[j].r <= circs[i].x - circs[i].r ||
                      circs[j].y - circs[j].r <= circs[i].y + circs[i].r && circs[j].y + circs[j].r <= circs[i].y - circs[i].r))
                {
                    intersect = false;
                    break;
                }
            }
        }

        // printf("\nCircle %d\n", i);
        // printf("\tr: %f", circs[i].r);
        // printf("\tx: %f", circs[i].x);
        // printf("\ty: %f", circs[i].y);
        // printf("\tisDrawing: %d", circs[i].isDrawing);
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
    int num = 20; Circ circs[num]; generateCircCoords(circs, num);

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
