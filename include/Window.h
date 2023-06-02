#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

bool Window_Create(SDL_Window** window, SDL_Renderer** renderer, const char* title, int width, int height);
void Window_Destroy(SDL_Window* window, SDL_Renderer* renderer);

#endif
