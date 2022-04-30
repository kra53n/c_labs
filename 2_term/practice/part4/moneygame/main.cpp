#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "window.h"

const int TEXTURES_NUM = 2;

const int MAX_COINS_NUM = 20;
const int INIT_COINS_NUM = 10;

const int BANKNOTE_WIDTH = 300;
const int COIN_WIDTH = 47;

struct Texture
{
    SDL_Texture* texture = NULL;
    SDL_Rect dstrect;
};

struct Coin
{
    SDL_Rect dstrect;
    bool toDraw = true;
    int speed = 5;
};


struct Game
{
    bool run;
    SDL_Event event;
    SDL_Color bgColor;
    Texture textures[TEXTURES_NUM];
    Coin coins[MAX_COINS_NUM];
};

void loadTexture(Texture& texture, int wdt, const char filename[])
{
    SDL_Surface* surf = IMG_Load(filename);
    if (!surf)
    {
        printf("Couldn't load image! Error: %s", SDL_GetError());
        system("pause");
        deInit(1);
    }
    texture.texture = SDL_CreateTextureFromSurface(ren, surf);
    float coeffOfWidth = (float)wdt / surf->w;
    texture.dstrect = { 0, 0, (int)(surf->w * coeffOfWidth), (int)(surf->h * coeffOfWidth) };
    SDL_FreeSurface(surf);
}

void loadTextures(Game& game)
{
    loadTexture(game.textures[0], BANKNOTE_WIDTH, "imgs/banknote.png");
    loadTexture(game.textures[1], COIN_WIDTH, "imgs/coin.png");
}

void CoinsInit(Game& game)
{
    for (int i = 0; i < MAX_COINS_NUM; i++)
    {
        game.coins[i].dstrect = game.textures[1].dstrect;
        game.coins[i].dstrect.x = rand() % (winWdt - game.coins[i].dstrect.w);
        game.coins[i].dstrect.y = rand() % (winHgt - game.coins[i].dstrect.h);
        
        if (i < INIT_COINS_NUM)
            game.coins[i].toDraw = true;
        else
            game.coins[i].toDraw = false;
    }
}

void CoinsDraw(Game& game)
{
    for (int i = 0; i < MAX_COINS_NUM; i++)
        if (game.coins[i].toDraw)
            SDL_RenderCopy(ren, game.textures[1].texture, NULL, &game.coins[i].dstrect);
}

void CoinsUpdate(Game& game)
{
    if (SDL_GetTicks() % 50 == 1)
    {
        for (int i = 0; i < MAX_COINS_NUM; i++)
        {
            if (!game.coins[i].toDraw)
            {
                game.coins[i].toDraw = true;
                game.coins[i].dstrect.x = rand() % (winWdt - game.coins[i].dstrect.w);
                game.coins[i].dstrect.y = rand() % (winHgt - game.coins[i].dstrect.h);
                break;
            }
        }
    }

    for (int i = 0; i < MAX_COINS_NUM; i++)
    {
        if (!game.coins[i].toDraw)
            continue;

        if (game.coins[i].dstrect.x < 0)
            game.coins[i].dstrect.x = 0;
        if (game.coins[i].dstrect.x + game.coins[i].dstrect.w > winWdt)
            game.coins[i].dstrect.x = winWdt - game.coins[i].dstrect.w;

        if (game.coins[i].dstrect.y < 0)
            game.coins[i].dstrect.y = 0;
        if (game.coins[i].dstrect.y + game.coins[i].dstrect.h > winHgt)
            game.coins[i].dstrect.y = winHgt - game.coins[i].dstrect.h;
    }
}

void CoinsAttractOut(Coin coins[MAX_COINS_NUM], SDL_Rect rect)
{
    for (int i = 0; i < MAX_COINS_NUM; i++)
    {
        if (!coins[i].toDraw)
            continue;

        if (coins[i].dstrect.x + coins[i].dstrect.w <= rect.x)
            coins[i].dstrect.x -= coins[i].speed;
        if (coins[i].dstrect.x >= rect.x + rect.w)
            coins[i].dstrect.x += coins[i].speed;

        if (coins[i].dstrect.y + coins[i].dstrect.h <= rect.y)
            coins[i].dstrect.y -= coins[i].speed;
        if (coins[i].dstrect.y >= rect.y + rect.h)
            coins[i].dstrect.y += coins[i].speed;
    }
}

void CoinsAttractIn(Coin coins[MAX_COINS_NUM], SDL_Rect rect)
{
    for (int i = 0; i < MAX_COINS_NUM; i++)
    {
        if (!coins[i].toDraw)
            continue;

        if (coins[i].dstrect.x + coins[i].dstrect.w <= rect.x)
            coins[i].dstrect.x += coins[i].speed;
        if (coins[i].dstrect.x >= rect.x + rect.w)
            coins[i].dstrect.x -= coins[i].speed;

        if (coins[i].dstrect.y + coins[i].dstrect.h <= rect.y)
            coins[i].dstrect.y += coins[i].speed;
        if (coins[i].dstrect.y >= rect.y + rect.h)
            coins[i].dstrect.y -= coins[i].speed;
    }

}

void BanknoteProcessRublesIntersecion(Game& game)
{
    for (int i = 0; i < MAX_COINS_NUM; i++)
    {
        if (!game.coins[i].toDraw || !SDL_HasIntersection(&game.coins[i].dstrect, &game.textures[0].dstrect))
            continue;
        game.coins[i].toDraw = false;
    }
}

void BanknoteUpdate(Texture& texture)
{
    if (texture.dstrect.x < 0)
        texture.dstrect.x = 0;
    if (texture.dstrect.x + texture.dstrect.w > winWdt)
        texture.dstrect.x = winWdt - texture.dstrect.w;

    if (texture.dstrect.y < 0)
        texture.dstrect.y = 0;
    if (texture.dstrect.y + texture.dstrect.h > winHgt)
        texture.dstrect.y = winHgt - texture.dstrect.h;
}

void GameInit(Game& game)
{
    game.run = true;
    game.bgColor = { 12, 0, 24, 255 };
    loadTextures(game);
    CoinsInit(game);
}

void GameUpdate(Game& game)
{
    while (SDL_PollEvent(&game.event))
    {
        SDL_Point mouse;
        switch (game.event.type)
        {
        case SDL_QUIT:
            game.run = false;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&mouse.x, &mouse.y);
            game.textures[0].dstrect.x = mouse.x - game.textures[0].dstrect.w / 2;
            game.textures[0].dstrect.y = mouse.y - game.textures[0].dstrect.h / 2;
            break;
        case SDL_KEYDOWN:
            switch (game.event.key.keysym.scancode)
            {
            case SDL_SCANCODE_SPACE:
                CoinsAttractOut(game.coins, game.textures[0].dstrect);
                break;
            case SDL_SCANCODE_RETURN:
                CoinsAttractIn(game.coins, game.textures[0].dstrect);
                break;
            }
        }
    }
    BanknoteUpdate(game.textures[0]);
    CoinsUpdate(game);
    BanknoteProcessRublesIntersecion(game);
}

void GameDraw(Game& game)
{
    SDL_SetRenderDrawColor(ren, game.bgColor.r, game.bgColor.g, game.bgColor.b, game.bgColor.a);
    SDL_RenderClear(ren);

    CoinsDraw(game);
    SDL_RenderCopy(ren, game.textures[0].texture, NULL, &game.textures[0].dstrect);

    SDL_RenderPresent(ren);
}

void GameLoop(Game& game)
{
    while (game.run)
    {
        GameUpdate(game);
        GameDraw(game);
        SDL_Delay(60);
    }
}

int main(int argc, char* artgv[])
{
    init();

    Game game;
    GameInit(game);
    GameLoop(game);

    deInit(0);
    return 0;
}