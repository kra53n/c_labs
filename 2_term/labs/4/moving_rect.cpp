#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

SDL_Window*   win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 800;
int winHgt = 600;

const float RAD = M_PI / 180;

void init()
{
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow(
        u8"Бахтин Грегорионио", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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

void changeSpeed(int &coord, int start=3, int end=10)
{
    coord = rand() % (end - start + 1) + start;
}

void rectCollision(SDL_Rect rect, int &x_speed, int &y_speed)
{
    if (rect.x < 0) changeSpeed(x_speed);
    if (rect.y < 0) changeSpeed(y_speed);

    if (rect.x + rect.w >= winWdt) { changeSpeed(x_speed); x_speed *= -1; }
    if (rect.y + rect.h >= winHgt) { changeSpeed(y_speed); y_speed *= -1; }

}

void drawMovingRect(int x, int y, int wdt, int hgt, int moves)
{
    int x_speed = 3;
    int y_speed = 3;
    SDL_Rect rect = {x, y, wdt, hgt};

    for (int move = 0; move < moves; move++)
    {
        SDL_SetRenderDrawColor(ren, 162, 174, 187, 0);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 223, 224, 226, 0);
        SDL_RenderFillRect(ren, &rect);
        rectCollision(rect, x_speed, y_speed);

        rect.x += x_speed;
        rect.y += y_speed;

        SDL_RenderPresent(ren);
        SDL_Delay(20);
    }
}

int main()
{
    init();

    int rect_wdt = 100, rect_hgt = 100;
    drawMovingRect(
        rand() % (winWdt - rect_wdt), rand() % (winHgt - rect_hgt),
        rect_wdt, rect_hgt, 1000
    );

    deInit();

    return 0;
}
