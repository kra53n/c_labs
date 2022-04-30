#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#include "window.h"

const int TEXTURES_NUM = 2;
const int TEXTURE_WIDTH = 100;

const SDL_Color RED   = { 255, 75, 75, 255 };
const SDL_Color GREEN = { 75, 255, 75, 255 };

struct Texture
{
    SDL_Texture* texture = NULL;
    SDL_Rect dstrect;
    SDL_RendererFlip flip;
};

struct AvoidableRect
{
    SDL_Rect rect = { winWdt / 2, winHgt / 2, TEXTURE_WIDTH, TEXTURE_WIDTH };
    SDL_Color col = GREEN;
    Uint32 lastTick;
    bool active = false;
    int minSpeed = 2;
    int maxSpeed = 5;
    int xSpeed = 3;
    int ySpeed = 3;
};

struct Game
{
    bool running = true;
    SDL_Event event;
    SDL_Point mouseLastPoints[TEXTURES_NUM] = { { 100, 100 }, { 200, 100 } };
    AvoidableRect avoidableRect;
    Texture textures[TEXTURES_NUM];
    int textureStep = 3;
};

void loadTexture(Texture& textureStruct, const char name[])
{
    SDL_Surface* surf = IMG_Load(name);
    if (surf == NULL)
    {
        printf("Couldn't load image! Error: %s", SDL_GetError());
        system("pause");
        deInit(1);
    }
    textureStruct.texture = SDL_CreateTextureFromSurface(ren, surf);
    float coeffOfSize = (float)TEXTURE_WIDTH / surf->w;
    textureStruct.dstrect = { 0, 0, (int)(surf->w * coeffOfSize), (int)(surf->h * coeffOfSize)};
    SDL_FreeSurface(surf);
}

void loadTextures(Texture textures[])
{
    loadTexture(textures[0], "imgs/gnu.png");
    loadTexture(textures[1], "imgs/go.png");
}

void updateRect(AvoidableRect& avdr)
{
    avdr.rect.x += avdr.xSpeed;
    avdr.rect.y += avdr.ySpeed;
    avdr.col = avdr.active ? RED : GREEN;

    if (avdr.rect.x + avdr.rect.w > winWdt)
    {
        avdr.rect.x = winWdt - avdr.rect.w;
        avdr.xSpeed = -1 * (rand() % (avdr.maxSpeed - avdr.minSpeed) + avdr.minSpeed);
    }
    if (avdr.rect.x < 0)
    {
        avdr.rect.x = 0;
        avdr.xSpeed = rand() % (avdr.maxSpeed - avdr.minSpeed) + avdr.minSpeed;
    }

    if (avdr.rect.y + avdr.rect.h > winHgt)
    {
        avdr.rect.y = winHgt - avdr.rect.h;
        avdr.ySpeed = -1 * (rand() % (avdr.maxSpeed - avdr.minSpeed) + avdr.minSpeed);
    }
    if (avdr.rect.y < 0)
    {
        avdr.rect.y = 0;
        avdr.ySpeed = rand() % (avdr.maxSpeed - avdr.minSpeed) + avdr.minSpeed;
    }
}

bool processTextureWithActiveRect(Texture& texture, int textureStep, AvoidableRect& avdr)
{
    if (avdr.active)
    {
        if (texture.dstrect.x >= avdr.rect.x)
            texture.dstrect.x += textureStep;
        else
            texture.dstrect.x -= textureStep;

        if (texture.dstrect.y >= avdr.rect.y)
            texture.dstrect.y += textureStep;
        else
            texture.dstrect.y -= textureStep;

        avdr.active = SDL_GetTicks() - avdr.lastTick >= 3000 ? false : true;

        return 1;
    }
    return 0;
}

void updateTextures(Game& game)
{
    for (int i = 0; i < TEXTURES_NUM; i++)
    {
        if (processTextureWithActiveRect(game.textures[i], game.textureStep, game.avoidableRect))
            continue;

        if (game.textures[i].dstrect.x > game.mouseLastPoints[i].x)
        {
            game.textures[i].dstrect.x -= game.textureStep;
            game.textures[i].flip = SDL_FLIP_HORIZONTAL;
        }
        if (game.textures[i].dstrect.x < game.mouseLastPoints[i].x)
        {
            game.textures[i].dstrect.x += game.textureStep;
            game.textures[i].flip = SDL_FLIP_NONE;
        }

        if (game.textures[i].dstrect.y > game.mouseLastPoints[i].y)
            game.textures[i].dstrect.y -= game.textureStep;
        if (game.textures[i].dstrect.y < game.mouseLastPoints[i].y)
            game.textures[i].dstrect.y += game.textureStep;
    }
}

void drawTextures(Texture textures[])
{
    for (int i = 0; i < TEXTURES_NUM; i++)
    {
        SDL_RenderCopyEx(ren, textures[i].texture, NULL, &textures[i].dstrect, 0, NULL, textures[i].flip);
    }
}

void GameInit(Game& game)
{   
    loadTextures(game.textures);
}

void GameUpdate(Game& game)
{
    while (SDL_PollEvent(&game.event))
    {
        switch (game.event.type)
        {
        case SDL_QUIT:
            game.running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
        {
            SDL_Rect tmpRect;
            SDL_Point tmpPoint;

            switch (game.event.button.button)
            {
            case SDL_BUTTON_LEFT:
                SDL_GetMouseState(&tmpRect.x, &tmpRect.y);

                tmpPoint = { tmpRect.x, tmpRect.y };

                if (SDL_PointInRect(&tmpPoint, &game.avoidableRect.rect))
                {
                    game.avoidableRect.active = true;
                    game.avoidableRect.lastTick = SDL_GetTicks();
                }

                tmpRect = {
                    tmpRect.x - game.textures[0].dstrect.w / 2,
                    tmpRect.y - game.textures[0].dstrect.h / 2,
                    game.textures[0].dstrect.w,
                    game.textures[0].dstrect.h
                };
                if (SDL_HasIntersection(&tmpRect, &game.textures[1].dstrect))
                    continue;
                game.mouseLastPoints[0].x = tmpRect.x;
                game.mouseLastPoints[0].y = tmpRect.y;
                break;
            case SDL_BUTTON_RIGHT:
                SDL_GetMouseState(&tmpRect.x, &tmpRect.y);
                tmpRect = {
                    tmpRect.x - game.textures[1].dstrect.w / 2,
                    tmpRect.y - game.textures[1].dstrect.h / 2,
                    game.textures[0].dstrect.w,
                    game.textures[0].dstrect.h
                };
                if (SDL_HasIntersection(&tmpRect, &game.textures[0].dstrect))
                    continue;
                game.mouseLastPoints[1].x = tmpRect.x;
                game.mouseLastPoints[1].y = tmpRect.y;
                break;
            }
        }
        }
    }
    updateTextures(game);
    updateRect(game.avoidableRect);
}

void GameDraw(Game& game)
{
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    drawTextures(game.textures);
    SDL_SetRenderDrawColor(
        ren,
        game.avoidableRect.col.r,
        game.avoidableRect.col.g,
        game.avoidableRect.col.b,
        game.avoidableRect.col.a
    );
    SDL_RenderFillRect(ren, &game.avoidableRect.rect);

    SDL_RenderPresent(ren);
}

void GameLoop(Game& game)
{
    while (game.running)
    {
        GameUpdate(game);
        GameDraw(game);
        SDL_Delay(30);
    }
}

int main(int argc, char* argv[])
{
    init();

    Game game;
    GameInit(game);
    GameLoop(game);

    deInit(0);
    return 0;
}
