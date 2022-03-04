#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

SDL_Window*   win = NULL;
SDL_Renderer* ren = NULL;

int win_wdt = 800;
int win_hgt = 600;
int win_wdt2 = win_wdt / 2;
int win_hgt2 = win_hgt / 2;

float rad = M_PI / 180;

void init()
{
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow(
        u8"Бахтин Грегорионио", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        win_wdt, win_hgt, SDL_WINDOW_SHOWN
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

    if (rect.x + rect.w >= win_wdt) { changeSpeed(x_speed); x_speed *= -1; }
    if (rect.y + rect.h >= win_hgt) { changeSpeed(y_speed); y_speed *= -1; }

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

void drawCircle(int x, int y, int r)
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

void drawCircles()
{
    for (int i = 0; i < 360; i++)
    {
        SDL_SetRenderDrawColor(ren, 162, 174, 187, 0);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 223, 224, 226, 0);
        drawCircle(win_wdt2, win_hgt2, 20);
        drawCircle(win_wdt2 - cos(i * 22 * rad) * 20, win_hgt2 - sin(i * 22 * rad) * 20, 2);

        drawCircle(win_wdt2, win_hgt2, 40);
        drawCircle(win_wdt2 - cos(i * 15 * rad) * 40, win_hgt2 - sin(i * 15 * rad) * 40, 3);

        drawCircle(win_wdt2, win_hgt2, 80);
        drawCircle(win_wdt2 - cos(i * 10 * rad) * 80, win_hgt2 - sin(i * 10 * rad) * 80, 5);

        drawCircle(win_wdt2, win_hgt2, 160);
        drawCircle(win_wdt2 - cos(i * 3 * rad) * 160, win_hgt2 - sin(i * 3 * rad) * 160, 10);

        drawCircle(win_wdt2, win_hgt2, 280);
        drawCircle(win_wdt2 - cos(i * 1 * rad) * 280, win_hgt2 - sin(i * 1 * rad) * 280, 15);

        SDL_RenderPresent(ren);
        SDL_Delay(20);
    }
}

int main()
{
    init();

    switch (2)
    {
    case 1:
        {
            int rect_wdt = 100, rect_hgt = 100;
            drawMovingRect(
                rand() % (win_wdt - rect_wdt), rand() % (win_hgt - rect_hgt),
                rect_wdt, rect_hgt, 1000
            );
            break;
        }
    case 2:
        SDL_RenderClear(ren);
        drawCircles();
        break;
    }

    deInit();

    return 0;
}
