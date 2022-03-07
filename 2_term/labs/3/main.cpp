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

    drawStarts(ren, SCREEN_WIDTH, 0, 0.3, 30);
    drawStarts(ren, 0 - 40, SCREEN_HEIGHT / 2 - 20, 0.4, 20);
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
    drawPlot(ren, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, scale);

    SDL_SetRenderDrawColor(ren, 163, 141, 214, 0);
    float coeffs[4]; askUserCoefficients(coeffs);
    for (float i = -10, step = 0.01; i < 10; i += step)
    {
        float x_stp = i + step;
        SDL_RenderDrawLine(
            ren,
            SCREEN_WIDTH / 2 + i * scale,
            SCREEN_HEIGHT / 2 - (coeffs[0]*i*i*i + coeffs[1]*i*i + coeffs[2]*i + coeffs[3]) * scale,
            SCREEN_WIDTH / 2 + x_stp * scale,
            SCREEN_HEIGHT / 2 - (coeffs[0]*x_stp*x_stp*x_stp + coeffs[1]*x_stp*x_stp + coeffs[2]*x_stp + coeffs[3]) * scale
        );
    }
}

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
            drawGraph(ren, -10, 10, 38);
            break;
    }

    SDL_RenderPresent(ren);

    SDL_Delay(5000);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
