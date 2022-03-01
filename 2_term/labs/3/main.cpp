#include <SDL2/SDL.h>

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

void drawTrianlge(
    SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3
)
{
    SDL_RenderDrawPoints(renderer, points, count);
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow(
        u8"Бахтин", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 42, 0, 74, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 247, 227, 253, 0);
    SDL_Rect rect = {SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, SCREEN_WIDTH - SCREEN_WIDTH / 2.5, SCREEN_HEIGHT - SCREEN_HEIGHT / 2.5};
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);

    SDL_Delay(2000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
