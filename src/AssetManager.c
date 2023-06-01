#include "AssetManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_image.h>

SDL_Texture* AssetManager_LoadTexture(SDL_Renderer* renderer, const char* filePath)
{
    SDL_Surface* surface = IMG_Load(filePath);
    if (surface == NULL) {
        printf("Failed to load image: %s\n", filePath);
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

void AssetManager_FreeTexture(SDL_Texture* texture)
{
    SDL_DestroyTexture(texture);
}
