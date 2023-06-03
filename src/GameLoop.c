// GameLoop.c
#include "GameLoop.h"
#include "Window.h"
#include "ball.h"
#include "paddle.h"
#include "block.h"
#include "AssetManager.h"
#include "Input.h"

#include <stdbool.h>
#include <SDL2/SDL.h>

bool GameLoop(SDL_Window* window, SDL_Renderer* renderer, int windowWidth, int windowHeight) {
    bool isRunning = true;
    SDL_Event event;

    // Load textures
    SDL_Texture* ballTexture = AssetManager_LoadTexture(renderer, "src/img/Ball_01.png");
    if (ballTexture == NULL) {
        printf("Failed to load ball texture!\n");
        return false;
    }

    SDL_Texture* paddleTexture = AssetManager_LoadTexture(renderer, "src/img/Paddle.png");
    if (paddleTexture == NULL) {
        printf("Failed to load paddle texture!\n");
        return false;
    }

    // Create ball and paddle
    Ball ball;
    Ball_Init(&ball, windowWidth * 0.5, windowHeight * 0.5, 14, 70, 24, ballTexture);

    Paddle paddle;
    Paddle_Init(&paddle, windowWidth * 0.5 - 64, windowHeight - 32 - 8, 128, 32, 100, paddleTexture);

    // Create blocks
    const int numRows = 4;
    const int numCols = 6;
    const int blockWidth = 128;
    const int blockHeight = 40;
    const int blockSpacing = 40;

    Block* blocks[numRows][numCols];

    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            int xPos = (windowWidth - (numCols * blockWidth + (numCols - 1) * blockSpacing)) / 2 +
                       col * (blockWidth + blockSpacing);
            int yPos = 100 + row * (blockHeight + blockSpacing);

            blocks[row][col] = Block_Create(xPos, yPos, blockWidth, blockHeight, 3, 0);
            if (blocks[row][col] == NULL) {
                printf("Failed to create block.\n");
                return false;
            }
        }
    }

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

        // Update ball and paddle
        Ball_Update(&ball, deltaTime, windowWidth, windowHeight);
        Ball_CollideWithWindow(&ball, windowWidth, windowHeight);
        Paddle_Update(&paddle, deltaTime, Input_GetMouseX(), windowWidth);

        // Render ball, paddle, and block
        Ball_Render(&ball, renderer);
        Paddle_Render(&paddle, renderer);
        Paddle_CollideWithBall(&paddle, &ball);

        // Check collision with blocks
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                Block* block = blocks[row][col];

                if (block != NULL && block->health > 0) {
                    Block_Render(block, renderer);

                    // Check if the ball collides with the block
                    if (Block_CollideWithBall(block, &ball)) {
                        Block_ReduceHealth(block, 1);
                        if (Block_GetHealth(block) <= 0) {
                            Block_Destroy(block);
                            blocks[row][col] = NULL;
                        }
                    }
                }
            }
        }

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Free resources
    AssetManager_FreeTexture(ballTexture);
    AssetManager_FreeTexture(paddleTexture);
    // Block_Destroy(block);
    // Block_Destroy(block2);

    return true;
}
