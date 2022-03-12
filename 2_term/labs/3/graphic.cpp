#include <SDL2/SDL.h>
#include <stdio.h>

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
    drawGraph(ren, -10, 10, 38);
    SDL_RenderPresent(ren);
    SDL_Delay(5000);
    deInit(0);

    return 0;
}
