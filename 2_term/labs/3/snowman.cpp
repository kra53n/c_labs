#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

SDL_Window*   win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 800;
int winHgt = 600;

const float RAD = M_PI / 180;

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

    win = SDL_CreateWindow("Gregory snowman", SDL_WINDOWPOS_CENTERED,
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

void drawFillCirc(float x, float y, float radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(ren, x + dx, y + dy);
            }
        }
    }
}

void drawFillHalfUpCirc(float x, float y, float radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(ren, x + dx, y - dy);
            }
        }
    }
}

void drawStick(int &x, int &y, float direction, float scale, float scaleCirc, float step=1)
{
    direction *= RAD;
    float i = 0;
    for (; i < scale; i += step)
        drawFillCirc(cos(direction) * i + x, sin(-direction) * i + y, scaleCirc);
    x = cos(direction) * i + x;
    y = sin(-direction) * i + y;
}

void drawSnowman(int x, int y)
{
    float square = winWdt < winHgt ? winWdt : winHgt;
    SDL_Rect snowRect = { winWdt / 2 - square * 0.2, winHgt / 2 - square * 0.4,
                          square * 0.4, square * 0.8 };
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);

    // body
    drawFillCirc(
        snowRect.x + snowRect.w / 2,
        snowRect.y + snowRect.h - snowRect.w * 0.45,
        snowRect.w * 0.45
    );
    drawFillCirc(
        snowRect.x + snowRect.w / 2,
        snowRect.y + snowRect.h - snowRect.w * 1.1,
        snowRect.w * 0.38
    );
    drawFillCirc(
        snowRect.x + snowRect.w / 2,
        snowRect.y + snowRect.h - snowRect.w * 1.6,
        snowRect.w * 0.3
    );
    
    // legs
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
    drawFillHalfUpCirc(
        snowRect.x + snowRect.w * 0.6 / 2,
        snowRect.y + snowRect.h,
        snowRect.w * 0.15
    );
    drawFillHalfUpCirc(
        snowRect.x + snowRect.w * 1.4 / 2,
        snowRect.y + snowRect.h,
        snowRect.w * 0.15
    );

    // eyes
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
    drawFillCirc(
        snowRect.x + snowRect.w * 0.77 / 2,
        snowRect.y + snowRect.h - snowRect.w * 1.7,
        snowRect.w * 0.04
    );
    SDL_SetRenderDrawColor(ren, 0, 0, 255, 0);
    drawFillCirc(
        snowRect.x + snowRect.w * 1.23 / 2,
        snowRect.y + snowRect.h - snowRect.w * 1.7,
        snowRect.w * 0.04
    );

    // buttons
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    for (float i = 0.2; i < 1.3; i += 0.2)
        drawFillCirc(
            snowRect.x + snowRect.w / 2,
            snowRect.y + snowRect.h - snowRect.w * i,
            snowRect.w * 0.02
        );

    // smile
    for (int i = -180, step = 10; i < 0; i += step)
        drawFillCirc(
            snowRect.x + snowRect.w / 2 - (cos(i * RAD) * snowRect.w * 0.05),
            snowRect.y + snowRect.h - snowRect.w * 1.55 - (sin(i * RAD) * snowRect.w * 0.03),
            snowRect.w * 0.01
        );

    // nose
    SDL_SetRenderDrawColor(ren, 225, 138, 31, 0);
    for (float i = 0; i < snowRect.w * 0.03; i++)
    {
        drawFillCirc(
            snowRect.x + snowRect.w / 2 + snowRect.w * i * 0.01,
            snowRect.y + snowRect.h - snowRect.w * 1.6 + snowRect.w * i * 0.003,
            snowRect.w / (i * 3 + 50)
        );
    }

    // arms
    SDL_SetRenderDrawColor(ren, 139, 90, 43, 255);
    int arm_x, arm_y;
    // left arm
    arm_x = snowRect.x + snowRect.w * 0.89;
    arm_y = (snowRect.y + snowRect.h) - snowRect.w * 1.2;
    drawStick(arm_x, arm_y, -40, 80, 7);
    drawStick(arm_x, arm_y, -120, 100, 5);

    // right arm
    arm_x = snowRect.x + snowRect.w * 0.11;
    arm_y = (snowRect.y + snowRect.h) - snowRect.w * 1.2;
    drawStick(arm_x, arm_y, 220, 80, 7);
    drawStick(arm_x, arm_y, -55, 100, 5);
 }

int main(int argc, char* argv[])
{
    init();
    drawSnowman(winWdt / 2, winHgt / 2);
    SDL_RenderPresent(ren);
    SDL_Delay(15000);
    deInit(0);

    return 0;
}
