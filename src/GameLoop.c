// GameLoop.c

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

    // Create a window with VSync enabled
    SDL_Window* window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    // Create a renderer with VSync enabled
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

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

    // Variables for rotation
    double angle = 0.0;
    double rotationSpeed = 20.0; // 20 rotations per minute

    // Variables for timing
    const int UPDATE_FPS = 60;
    const int UPDATE_FRAME_DELAY = 1000 / UPDATE_FPS;
    Uint32 updateFrameStart;
    int updateFrameTime;

    const int RENDER_FPS = 40;
    const int RENDER_FRAME_DELAY = 1000 / RENDER_FPS;
    Uint32 renderFrameStart;
    int renderFrameTime;

    // Create an off-screen buffer for rendering
    SDL_Texture* buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (buffer == NULL) {
        printf("Failed to create buffer texture!\n");
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Update loop
    while (true) {
        updateFrameStart = SDL_GetTicks();

        // Event handling
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_DestroyTexture(buffer);
                SDL_DestroyTexture(texture);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return;
            }
        }

        // Game logic update
        double dt = 1.0 / UPDATE_FPS; // Delta time for game logic (60 FPS)

        // Frame rate regulation
        updateFrameTime = SDL_GetTicks() - updateFrameStart;
        if (UPDATE_FRAME_DELAY > updateFrameTime) {
            SDL_Delay(UPDATE_FRAME_DELAY - updateFrameTime);
        }

        // Render loop
        renderFrameStart = SDL_GetTicks();
        while (SDL_GetTicks() - renderFrameStart < RENDER_FRAME_DELAY) {
            // Clear the buffer with the sky blue color
            SDL_SetRenderTarget(renderer, buffer);
            SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
            SDL_RenderClear(renderer);

            // Update rotation
            angle += (rotationSpeed * 2.0 * M_PI / 60.0) * dt; // 20 rotations per minute

            // Set the rotation center
            SDL_Point rotationCenter = {imgWidth / 2, imgHeight / 2};

            // Render the image with rotation
            SDL_RenderCopyEx(renderer, texture, NULL, &destRect, angle * 180.0 / M_PI, &rotationCenter, SDL_FLIP_NONE);

            // Set the render target back to the default window
            SDL_SetRenderTarget(renderer, NULL);

            // Copy the buffer to the window
            SDL_RenderCopy(renderer, buffer, NULL, NULL);

            // Update the screen
            SDL_RenderPresent(renderer);

            // Frame rate regulation
            renderFrameTime = SDL_GetTicks() - renderFrameStart;
            if (RENDER_FRAME_DELAY > renderFrameTime) {
                SDL_Delay(RENDER_FRAME_DELAY - renderFrameTime);
            }
        }
    }
}
