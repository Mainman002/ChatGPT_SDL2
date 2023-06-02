// Input.h
#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#define INPUT_CONTROLLER_DEAD_ZONE 8000

typedef struct {
    bool keys[SDL_NUM_SCANCODES];
    bool controllerButtons[SDL_CONTROLLER_BUTTON_MAX];
    float controllerAxisLeftX;
    float controllerAxisLeftY;
    // Add other members as needed
} InputState;

extern InputState inputState;

void Input_Init();
void Input_HandleEvent(SDL_Event* event);
void Input_Update();
int Input_GetMouseX();
bool Input_IsKeyDown(SDL_Scancode key);
bool Input_IsControllerButtonDown(SDL_GameControllerButton button);
float Input_GetControllerAxisLeftX();
float Input_GetControllerAxisLeftY();

#endif  // INPUT_H
