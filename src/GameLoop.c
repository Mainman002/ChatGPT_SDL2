#include <stdbool.h>
#include "AssetManager.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void GameLoop()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Clear the renderer with the sky blue color
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
    SDL_RenderClear(renderer);

    // Load an image
    SDL_Texture* texture = AssetManager_LoadTexture(renderer, "src/img/Ball_01.png");
    if (texture == NULL) {
        printf("Failed to load image!\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Get the image dimensions
    int imgWidth, imgHeight;
    SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);

    // Set the destination rectangle for rendering the image
    SDL_Rect destRect = {SCREEN_WIDTH / 2 - imgWidth / 2, SCREEN_HEIGHT / 2 - imgHeight / 2, imgWidth, imgHeight};

    // Render the image
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    // Update the screen
    SDL_RenderPresent(renderer);

    // Event loop
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    // Cleanup
    AssetManager_FreeTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
