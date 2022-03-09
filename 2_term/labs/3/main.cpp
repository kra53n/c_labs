#include <SDL2/SDL.h>
#include <malloc.h>
#include <stdio.h>
#include <math.h>

/* Задание:
 *  Вывести на  экран
 *   1: конверт
 *   2: звёздное небо
 *   3: y = a*x^3 + b*x^2 + c*x + d в интервале от 10 до 10
 */

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

void drawEnvelope(SDL_Renderer* ren)
{
    SDL_SetRenderDrawColor(ren, 94, 81, 125, 0);
    SDL_RenderClear(ren);

    SDL_Rect rect = {
        winWdt / 5,
        winHgt / 5,
        winWdt - winWdt / 2.5,
        winHgt - winHgt / 2.5
    };

    SDL_SetRenderDrawColor(ren, 123, 106, 161, 0);
    SDL_RenderDrawLine(ren, rect.x, rect.y + rect.h,
        rect.x + rect.w / 2, rect.y + rect.h / 2);
    SDL_RenderDrawLine(ren, rect.x + rect.w / 2, rect.y + rect.h / 2,
            rect.x + rect.w, rect.y + rect.h);

    SDL_SetRenderDrawColor(ren, 145, 126, 192, 0);
    SDL_RenderDrawLine(ren, rect.x, rect.y,
        rect.x + rect.w / 2, rect.y + rect.h / 2);
    SDL_RenderDrawLine(ren, rect.x + rect.w / 2 , rect.y + rect.h / 2,
            rect.x + rect.w, rect.y);

    SDL_SetRenderDrawColor(ren, 163, 141, 214, 0);
    SDL_RenderDrawRect(ren, &rect);
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

void drawPlot(SDL_Renderer* ren, int x, int y, int scr_wdt, int scr_hgt, int scale)
{
    SDL_RenderDrawLine(ren, x, 0, x, scr_hgt);
    SDL_RenderDrawLine(ren, 0, y, scr_wdt, y);

    for (int i = x; i < scr_wdt; i += scale)
    {
        SDL_RenderDrawLine(ren, i + scale, y - 8, i + scale, y + 8);
        SDL_RenderDrawLine(ren, scr_wdt - i, y - 8, scr_wdt - i, y + 8);
    }

    for (int i = y; i < scr_hgt; i += scale)
    {
        SDL_RenderDrawLine(ren, x - 8, i + scale, x + 8, i + scale);
        SDL_RenderDrawLine(ren, x - 8, scr_hgt - i, x + 8, scr_hgt - i);
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

void askUserCoefficients(float arr[4])
{
    for (int i = 0; i < 4; i++)
    {
        printf("Введите k%d коэффициент функции: ", i+1);
        scanf("%f", &arr[i]);
    }
}

void drawGraph(SDL_Renderer* ren, int a, int b, int scale)
{
    SDL_SetRenderDrawColor(ren, 94, 81, 125, 0);
    SDL_RenderClear(ren);

    SDL_SetRenderDrawColor(ren, 145, 126, 192, 0);
    drawPlot(ren, winWdt2, winHgt2, winWdt, winHgt, scale);

    SDL_SetRenderDrawColor(ren, 163, 141, 214, 0);
    float coeffs[4]; askUserCoefficients(coeffs);
    for (float i = -10, step = 0.01; i < 10; i += step)
    {
        float x_stp = i + step;
        SDL_RenderDrawLine(
            ren,
            winWdt2 + i * scale,
            winHgt2 - (coeffs[0]*i*i*i + coeffs[1]*i*i + coeffs[2]*i + coeffs[3]) * scale,
            winWdt2 + x_stp * scale,
            winHgt2 - (coeffs[0]*x_stp*x_stp*x_stp + coeffs[1]*x_stp*x_stp + coeffs[2]*x_stp + coeffs[3]) * scale
        );
    }
}

int main()
{
    init();
    switch (2)
    {
        case 1:
            drawEnvelope(ren);
            break;
        case 2:
            drawNightSky(ren);
            break;
        case 3:
            drawGraph(ren, -10, 10, 38);
            break;
    }

    SDL_RenderPresent(ren);

    SDL_Delay(5000);
    deInit(0);

    return 0;
}
