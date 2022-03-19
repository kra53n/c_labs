#include <SDL2/SDL.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

SDL_Window*   win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 800;
int winHgt = 600;

float RAD = M_PI / 180;

struct Snowflake
{
    int x;
    int y;
    int direction;
    int sign;
    float scale;
    float r;
};

struct Snowfall
{
    Snowflake** array = NULL;
    int row;
    int col;
    SDL_Color color;
};

void deInit(char error)
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

void drawFillCirc(float x, float y, float r)
{
    for (int w = 0; w < r * 2; w++)
    {
        for (int h = 0; h < r * 2; h++)
        {
            int dx = r - w;
            int dy = r - h;
            if ((dx * dx + dy * dy) <= (r * r))
            {
                SDL_RenderDrawPoint(ren, x + dx, y + dy);
            }
        }
    }
}

float randFloat(float min, float max)
{
    return ((float)rand() / RAND_MAX) * (max - min) + min;
}

void generateSnowflake(Snowflake &s, int x, int y)
{

    s.direction = rand() % 90 + 225;
    s.sign = rand() % 2 ? 1 : -1;

    s.r = randFloat(2, 5);
    s.scale = 200;

    s.x = (rand() % 10 + 2) * (int)(30 / s.r);
    s.y = y;
}

void addSnowflakesLayer(Snowfall &s)
{
    s.array = (Snowflake**)realloc(s.array, sizeof(Snowflake) * ++s.row);
    if (s.array == NULL)
    {
        printf("\nMemory cannot be allocated!\n");
        exit(1);
    }
    
    s.array[s.row] = (Snowflake*)malloc(sizeof(Snowflake) * s.col);
    if (s.array[s.row] == NULL)
    {
        printf("\nMemory cannot be allocated!\n");
        exit(1);
    }

    for (int i = 0; i < s.col; i++)
        generateSnowflake(s.array[s.row][i], 10 * (rand() % 10), 10 * (rand() % 10));
}

void drawSnow(Snowflake &s)
{
    drawFillCirc(
        cos(s.direction * RAD) * s.scale + s.x,
        sin(-s.direction * RAD) * s.scale + s.y,
        s.r
    );
}

void changeSnowflakePosition(Snowflake &s)
{
    s.direction += s.sign * (s.scale / 10 + (10 / s.r)) * 0.01;

    if (s.direction <= 180)
    {
        s.sign *= -1;
        s.direction = 180;
    }
    if (s.direction >= 360)
    {
        s.sign *= -1;
        s.direction = 360;
    }

    s.y += s.r * 0.7;
    s.x += s.sign * (1 / s.r);
}

int main(int argc, char* argv[])
{
    init();
    
    Snowfall snowfall;
    addSnowflakesLayer(snowfall);

    for (int i = 0; i < 800; i++)
    {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);

        for (int j = 0; j < 100; j++)
        {
            drawSnow(snowfall.array[0][j]);
            changeSnowflakePosition(snowfall.array[0][j]);
        }

        SDL_Delay(10);
        SDL_RenderPresent(ren);
    }

    deInit(0);
    return 0;
}
