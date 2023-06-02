// GameLoop.c
#include "GameLoop.h"
#include "Window.h"
#include "ball.h"
#include "paddle.h"
#include "AssetManager.h"
#include "Input.h"

#include <stdbool.h>
#include <SDL2/SDL.h>

bool GameLoop(SDL_Window* window, SDL_Renderer* renderer, int windowWidth, int windowHeight) {
    bool isRunning = true;
    SDL_Event event;

    // Load the ball texture
    SDL_Texture* ballTexture = AssetManager_LoadTexture(renderer, "src/img/Ball_01.png");
    if (ballTexture == NULL) {
        printf("Failed to load ball texture!\n");
        return false;
    }

    // Load the paddle texture
    SDL_Texture* paddleTexture = AssetManager_LoadTexture(renderer, "src/img/Paddle.png");
    if (paddleTexture == NULL) {
        printf("Failed to load paddle texture!\n");
        return false;
    }

    Ball ball;
    Ball_Init(&ball, windowWidth*0.5, windowHeight*0.5, 14, 70, 32, ballTexture);

    Paddle paddle;
    Paddle_Init(&paddle, windowWidth*0.5-24, windowHeight-24-8, 100, paddleTexture);

    Uint32 prevTime = SDL_GetTicks(); // Previous frame time

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            Input_HandleEvent(&event);
        }

        // Calculate delta time
        Uint32 currTime = SDL_GetTicks();
        float deltaTime = (currTime - prevTime) / 1000.0f; // Convert to seconds
        prevTime = currTime;

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
        SDL_RenderClear(renderer);

        // Update the ball
        Ball_Update(&ball, deltaTime, windowWidth, windowHeight);
        Ball_CollideWithWindow(&ball, windowWidth, windowHeight);

        // Update the paddle with mouse position
        int mouseX = Input_GetMouseX();
        Paddle_Update(&paddle, deltaTime, mouseX, windowWidth);

        // Render the ball
        Ball_Render(&ball, renderer);
        Paddle_Render(&paddle, renderer);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    AssetManager_FreeTexture(ballTexture); // Free the ball texture
    AssetManager_FreeTexture(paddleTexture); // Free the paddle texture
    return true;
}
