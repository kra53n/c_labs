#include <SDL2/SDL.h>

const int SCREEN_WIDTH  = 700;
const int SCREEN_HEIGHT = 800;

int main()
{
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow("Бахтин", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not initialize! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, NULL,
                SDL_MapRGB(screenSurface->format, 31, 73, 125));

            char imgPath[] = "img.bmp";
            SDL_Surface* img = SDL_LoadBMP(imgPath);
            if (img == NULL)
            {
                printf("Unable to load image %s! SDL_Error: %s\n", imgPath, SDL_GetError());
            }
            else
            {
                SDL_Rect imgRect;
                imgRect.x = SCREEN_WIDTH - img->w;
                imgRect.y = SCREEN_HEIGHT - img->h;
                SDL_BlitSurface(img, NULL, screenSurface, &imgRect);
            }

            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
