#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "AssetManager.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const int PADDLE_WIDTH = 128;
const int PADDLE_HEIGHT = 24;
const int PADDLE_SPEED = 5;
double angle = 0.0;
double rotationSpeed = 20.0; // 20 rotations per minute

const int FRAME_DELAY = 1000 / 60;
Uint32 frameStart;
int frameTime;

void GameLoop()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // Create a window with VSync enabled
    SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    // Load the paddle texture
    SDL_Texture* paddleTexture = AssetManager_LoadTexture(renderer, "src/img/Paddle.png");
    if (paddleTexture == NULL) {
        printf("Failed to load paddle texture!\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Load the ball texture
    SDL_Texture* ballTexture = AssetManager_LoadTexture(renderer, "src/img/Ball_01.png");
    if (ballTexture == NULL) {
        printf("Failed to load ball texture!\n");
        SDL_DestroyTexture(paddleTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Set the initial position of the paddle
    int paddleX = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;
    int paddleY = SCREEN_HEIGHT - PADDLE_HEIGHT - 16;

    // Variables for timing
    Uint32 frameStart;
    int frameTime;

    // Variable to track whether the left or right arrow key is held down
    bool moveLeft = false;
    bool moveRight = false;

    // Game loop
    while (true) {
        frameStart = SDL_GetTicks();

        // Event handling
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_DestroyTexture(paddleTexture);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_LEFT)
                    moveLeft = true;
                else if (event.key.keysym.sym == SDLK_RIGHT)
                    moveRight = true;
            }
            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_LEFT)
                    moveLeft = false;
                else if (event.key.keysym.sym == SDLK_RIGHT)
                    moveRight = false;
            }
        }

        // Move the paddle based on the arrow key input
        if (moveLeft && paddleX > 0) {
            paddleX -= PADDLE_SPEED;
        }
        else if (moveRight && paddleX < SCREEN_WIDTH - PADDLE_WIDTH) {
            paddleX += PADDLE_SPEED;
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the paddle
        SDL_Rect paddleRect = { paddleX, paddleY, PADDLE_WIDTH, PADDLE_HEIGHT };
        SDL_RenderCopy(renderer, paddleTexture, NULL, &paddleRect);

        // Render the grid of rotating balls
        int gridSizeX = 15;
        int gridSizeY = 8;
        int ballSize = 64;
        int spacing = 20;

        for (int row = 0; row < gridSizeY; row++) {
            for (int col = 0; col < gridSizeX; col++) {
                int ballX = col * (ballSize + spacing);
                int ballY = row * (ballSize + spacing);
                SDL_Rect ballRect = { ballX, ballY, ballSize, ballSize };
                SDL_RenderCopyEx(renderer, ballTexture, NULL, &ballRect, angle * 180.0 / M_PI, NULL, SDL_FLIP_NONE);
            }
        }

        // Update the angle for rotation
        double dt = frameTime / 1000.0; // Delta time in seconds
        double rotationAngle = (rotationSpeed * 2.0 * M_PI / 60.0) * dt;
        angle += rotationAngle;

        // Update the screen
        SDL_RenderPresent(renderer);

        // Frame rate regulation
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
}
