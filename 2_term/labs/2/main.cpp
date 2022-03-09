#include <SDL2/SDL.h>

SDL_Window*  win        = NULL;
SDL_Surface* screenSurf = NULL;

int winWdt = 700;
int winHgt = 800;


void deInit(char error)
{
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

    win = SDL_CreateWindow("Bakhtin SDL lab", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, winWdt, winHgt, SDL_WINDOW_SHOWN
    );
    if (win == NULL)
    {
        printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
        deInit(1);
    }

}

SDL_Surface* loadMedia(char filename[])
{
    SDL_Surface* media = SDL_LoadBMP(filename);
    if (media == NULL)
    {
        printf("Unable to load media %s! SDL_Error:%s\n", filename, SDL_GetError());
        deInit(1);
    }
    return media;
}

int main()
{

    init();

    screenSurf = SDL_GetWindowSurface(win);
    SDL_FillRect(screenSurf, NULL, SDL_MapRGB(screenSurf->format, 31, 73, 125));

    SDL_Surface* img = loadMedia("img.bmp");

    SDL_Rect imgRect;
    imgRect.x = winWdt - img->w;
    imgRect.y = winHgt - img->h;
    SDL_BlitSurface(img, NULL, screenSurf, &imgRect);

    SDL_UpdateWindowSurface(win);
    SDL_Delay(2000);

    deInit(0);

    return 0;
}
