#include <stdio.h>
#include <SDL2/SDL.h>
#include "Window.h"
#include "GameLoop.h"

int main(int argc, char* argv[])
{
    int windowWidth = 1280;   // Replace with the actual width of your window
    int windowHeight = 800;  // Replace with the actual height of your window
   
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // Create the window
    if (!Window_Create(&window, &renderer, "Pong", windowWidth, windowHeight))
    {
        printf("Failed to create the window!\n");
        return 1;
    }

    // Run the game loop
    GameLoop(window, renderer, windowWidth, windowHeight);

    // Destroy the window
    Window_Destroy(window, renderer);

    SDL_Quit(); // Add this line to properly quit SDL

    return 0;
}
