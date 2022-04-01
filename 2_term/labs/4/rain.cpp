#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL.h>
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
    int amount = 0;
};

void updateRaindropLayer(RainLayer& rainLayer)
{
    for (int rndrop = 0; rndrop < rainLayer.amount; rndrop++)
    {
        rainLayer.raindrops[rndrop].x += rainLayer.raindrops[rndrop].len * 1;
        rainLayer.raindrops[rndrop].y += rainLayer.raindrops[rndrop].len * 1;
    }
}

void resetRainLayer(RainLayer& rainLayer, float direction)
{
    int x_range = winWdt;
    int y_range = winHgt;

    int rndrop = 0;
    for (int y = y_range; y > 0; y -= rainLayer.distance, rndrop++)
    {
        rainLayer.raindrops = (Raindrop*)realloc(rainLayer.raindrops, sizeof(Raindrop) * (rndrop + 1));
        rainLayer.raindrops[rndrop].x = -(rand() % 100);
        rainLayer.raindrops[rndrop].y = y - rand() % 100;
        rainLayer.raindrops[rndrop].len = rand() % 10 * 10;
        rainLayer.raindrops[rndrop].direction = direction;
    }

    for (int x = 0; x < x_range; x += rainLayer.distance, rndrop++)
    {
        rainLayer.raindrops = (Raindrop*)realloc(rainLayer.raindrops, sizeof(Raindrop) * (rndrop + 1));
        rainLayer.raindrops[rndrop].x = x - rand() % 100;
        rainLayer.raindrops[rndrop].y = -(rand() % 100);
        rainLayer.raindrops[rndrop].len = rand() % 10 * 10;
        rainLayer.raindrops[rndrop].direction = direction;
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
            rainLayer.raindrops[rndrop].x - cos(angle) * rainLayer.raindrops[rndrop].len,
            rainLayer.raindrops[rndrop].y - sin(angle) * rainLayer.raindrops[rndrop].len
        );
    }
}

void addRainLayer(Rain& rain)
{
    RainLayer rainLayer; rainLayer.distance = 10; rainLayer.speed = 10;
    resetRainLayer(rainLayer, 2);

    rain.rainLayers = (RainLayer*)realloc(rain.rainLayers, sizeof(RainLayer) * (rain.amount+1));
    rain.rainLayers[rain.amount] = rainLayer;
    rain.amount++;
}

int main(int argc, char* artgv[])
{
    init();
    srand(time(0));

    RainLayer rainLayer; rainLayer.distance = 10; rainLayer.speed = 10;

    Rain rain;
    addRainLayer(rain);

    for (int period = 1; period < 100; period++)
    {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        if (period % 1 == 0)
            addRainLayer(rain);

        for (int idx = 0; idx < rain.amount; idx++)
        {
            drawRainLayer(rain.rainLayers[idx]);
            updateRaindropLayer(rain.rainLayers[idx]);
        }

        SDL_RenderPresent(ren);
        SDL_Delay(60);
    }
    free(rain.rainLayers);

    deInit(0);
    return 0;
}