#include <SDL2/SDL.h>
#include <malloc.h>
#include <math.h>

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

void drawBrightStar(SDL_Renderer* ren, int x, int y)
{
    float rad = M_PI / 180;
    float r = 160;
    float scale = 10;
    for (float angle = 0, step = 2; angle < 180; angle += step)
    {
        r = 45 * sin(angle / sqrt(2)) * scale;
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

void drawPlot(SDL_Renderer* ren, int x, int y, int scr_wdt, int scr_hgt)
{
    SDL_RenderDrawLine(ren, x, 0, x, scr_hgt);
    SDL_RenderDrawLine(ren, 0, y, scr_wdt, y);
}

void drawNightSky(SDL_Renderer* ren)
{
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 10);
    SDL_RenderClear(ren);

    SDL_SetRenderDrawColor(ren, 163, 141, 214, 0);
    drawPlot(ren, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT);

    drawBrightStar(ren, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow(
        u8"Бахтин", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
    );

    SDL_Renderer* ren = SDL_CreateRenderer(window, -1, 0);
    
    drawNightSky(ren);

    SDL_RenderPresent(ren);

    SDL_Delay(5000);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
