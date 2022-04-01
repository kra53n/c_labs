#include <SDL2/SDL.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "window.h"

struct Raindrop
{
    float x;
    float y;
    float len = 100;
    float direction = 1;
};

struct RainLayer
{
    Raindrop* raindrops = NULL;
    float distance;
    float speed;
    int amount;
};

struct Rain
{
    RainLayer* rainLayers = NULL;
    int amount;
};

void updateraindropLayer(RainLayer &rainLayer)
{
    for (int rndrop = 0; rndrop < rainLayer.amount; rndrop++)
    {
        rainLayer.raindrops[rndrop].x += rainLayer.raindrops[rndrop].len * 0.2;
        rainLayer.raindrops[rndrop].y += rainLayer.raindrops[rndrop].len * 0.2;
    }
}

void resetRainLayer(RainLayer &rainLayer, float direction)
{
    int x_range = winWdt;
    int y_range = winHgt;

    int rndrop = 0;
    for (int y = y_range; y > 0; y -= rainLayer.distance, rndrop++)
    {
        rainLayer.raindrops = (Raindrop*)realloc(rainLayer.raindrops, sizeof(Raindrop) * (rndrop+1));
        rainLayer.raindrops[rndrop].x = 0;
        rainLayer.raindrops[rndrop].y = y + rand() % 50;
        rainLayer.raindrops[rndrop].len = rand() % 10 * 10;
        rainLayer.raindrops[rndrop].direction = direction;
        //printf("mmmx: %f y: %f\n", RainLayer.raindrops[rndrop].x, RainLayer.raindrops[rndrop].y);
    }

    for (int x = 0; x < x_range; x += rainLayer.distance, rndrop++)
    {
        rainLayer.raindrops = (Raindrop*)realloc(rainLayer.raindrops, sizeof(Raindrop) * (rndrop+1));
        rainLayer.raindrops[rndrop].x = x + rand() % 50;
        rainLayer.raindrops[rndrop].y = 0;
        rainLayer.raindrops[rndrop].len = rand() % 10 * 10;
        rainLayer.raindrops[rndrop].direction = direction;
        //printf("x: %f y: %f\n", RainLayer.raindrops[rndrop].x, RainLayer.raindrops[rndrop].y);
    }
    rainLayer.amount = rndrop++;
}

void drawRainLayer(RainLayer rainLayer)
{
    for (int rndrop = 0; rndrop < rainLayer.amount; rndrop++)
    {
        float angle = atan(rainLayer.raindrops[rndrop].direction);
        SDL_SetRenderDrawColor(ren, 0, 0, 255 * rainLayer.raindrops[rndrop].len / 90, 255);
        SDL_RenderDrawLine(
            ren,
            rainLayer.raindrops[rndrop].x,
            rainLayer.raindrops[rndrop].y,
            rainLayer.raindrops[rndrop].x + cos(angle) * rainLayer.raindrops[rndrop].len,
            rainLayer.raindrops[rndrop].y + sin(angle) * rainLayer.raindrops[rndrop].len
        );
    }
}

void addRainLayer(Rain& rain, int idx)
{
    RainLayer rainLayer; rainLayer.distance = 10; rainLayer.speed = 10;
    resetRainLayer(rainLayer, 1.3);

    rain.amount++;
    rain.rainLayers = (RainLayer*)realloc(rain.rainLayers, sizeof(RainLayer) * rain.amount);
    rain.rainLayers[idx] = rainLayer;
}

int main(int argc, char* artgv[])
{
    init();
    srand(time(0));

    RainLayer rainLayer; rainLayer.distance = 10; rainLayer.speed = 10;

    Rain rain;
    addRainLayer(rain, 1);

    for (int period = 1; period < 100; period++)
    {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        if (period % 20 == 0)
            addRainLayer(rain, rain.amount+1);

        for (int idx = 0; idx < rain.amount; idx++)
        {
            drawRainLayer(rain.rainLayers[idx]);
            updateraindropLayer(rain.rainLayers[idx]);
        }

        SDL_RenderPresent(ren);
        SDL_Delay(60);
    }

    deInit(0);
    return 0;
}