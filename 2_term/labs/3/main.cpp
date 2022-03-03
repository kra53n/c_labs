#include <SDL2/SDL.h>
#include <malloc.h>
#include <math.h>

/* TODO:
 * - add buttons for choosing exercise 
 */

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

void drawEnvelope(SDL_Renderer* ren)
{
    SDL_SetRenderDrawColor(ren, 94, 81, 125, 0);
    SDL_RenderClear(ren);

    SDL_Rect rect = {
        SCREEN_WIDTH / 5,
        SCREEN_HEIGHT / 5,
        SCREEN_WIDTH - SCREEN_WIDTH / 2.5,
        SCREEN_HEIGHT - SCREEN_HEIGHT / 2.5
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
    float r = 160;
    for (float angle = 0; angle < 270; angle += step)
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

    drawStarts(ren, SCREEN_WIDTH, 0, 0.3, 30);
    drawStarts(ren, 0 - 40, SCREEN_HEIGHT / 2 - 20, 0.4, 20);
}

drawFormula(SDL_Renderer* ren, int a, int b)

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow(
        u8"Бахтин", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
    );

    SDL_Renderer* ren = SDL_CreateRenderer(window, -1, 0);
    
    switch (2)
    {
        case 1:
            drawEnvelope(ren);
            break;
        case 2:
            drawNightSky(ren);
            break;
        case 3:
            break;
    }

    SDL_RenderPresent(ren);

    SDL_Delay(5000);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
