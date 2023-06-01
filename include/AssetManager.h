#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL2/SDL.h>

SDL_Texture* AssetManager_LoadTexture(SDL_Renderer* renderer, const char* filePath);
void AssetManager_FreeTexture(SDL_Texture* texture);

#endif /* ASSETMANAGER_H */
