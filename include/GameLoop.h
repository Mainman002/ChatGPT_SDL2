#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <stdbool.h>
#include <SDL2/SDL.h>

bool GameLoop(SDL_Window* window, SDL_Renderer* renderer, int windowWidth, int windowHeight);

#endif /* GAMELOOP_H */
