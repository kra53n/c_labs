#include <SDL2/SDL.h>
#include <malloc.h>

/* TODO:
 * - add buttons for choosing exercise 
 */

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

void drawEnvelope(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 94, 81, 125, 0);
    SDL_RenderClear(renderer);

    SDL_Rect rect = {
        SCREEN_WIDTH / 5,
        SCREEN_HEIGHT / 5,
        SCREEN_WIDTH - SCREEN_WIDTH / 2.5,
        SCREEN_HEIGHT - SCREEN_HEIGHT / 2.5
    };

    SDL_SetRenderDrawColor(renderer, 123, 106, 161, 0);
    SDL_RenderDrawLine(renderer, rect.x, rect.y + rect.h,
        rect.x + rect.w / 2, rect.y + rect.h / 2);
    SDL_RenderDrawLine(renderer, rect.x + rect.w / 2, rect.y + rect.h / 2,
            rect.x + rect.w, rect.y + rect.h);

    SDL_SetRenderDrawColor(renderer, 145, 126, 192, 0);
    SDL_RenderDrawLine(renderer, rect.x, rect.y,
        rect.x + rect.w / 2, rect.y + rect.h / 2);
    SDL_RenderDrawLine(renderer, rect.x + rect.w / 2 , rect.y + rect.h / 2,
            rect.x + rect.w, rect.y);

    SDL_SetRenderDrawColor(renderer, 163, 141, 214, 0);
    SDL_RenderDrawRect(renderer, &rect);
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow(
        u8"Бахтин", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    
    switch (1)
    {
        case 1:
            drawEnvelope(renderer);
            break;
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(2000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
