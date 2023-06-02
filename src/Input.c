// Input.c
#include "Input.h"

InputState inputState;

void Input_Init() {
    // Initialize the input state as needed
}

void Input_HandleEvent(SDL_Event* event) {
    switch (event->type) {
        case SDL_KEYDOWN:
            inputState.keys[event->key.keysym.scancode] = true;
            break;
        case SDL_KEYUP:
            inputState.keys[event->key.keysym.scancode] = false;
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            inputState.controllerButtons[event->cbutton.button] = true;
            break;
        case SDL_CONTROLLERBUTTONUP:
            inputState.controllerButtons[event->cbutton.button] = false;
            break;
        case SDL_CONTROLLERAXISMOTION:
            if (event->caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
                if (event->caxis.value < -INPUT_CONTROLLER_DEAD_ZONE) {
                    inputState.controllerAxisLeftX = -1;
                } else if (event->caxis.value > INPUT_CONTROLLER_DEAD_ZONE) {
                    inputState.controllerAxisLeftX = 1;
                } else {
                    inputState.controllerAxisLeftX = 0;
                }
            }
            if (event->caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
                if (event->caxis.value < -INPUT_CONTROLLER_DEAD_ZONE) {
                    inputState.controllerAxisLeftY = -1;
                } else if (event->caxis.value > INPUT_CONTROLLER_DEAD_ZONE) {
                    inputState.controllerAxisLeftY = 1;
                } else {
                    inputState.controllerAxisLeftY = 0;
                }
            }
            break;
        // Handle other event types as needed
    }
}

void Input_Update() {
    // Update the input state
}

bool Input_IsKeyDown(SDL_Scancode key) {
    return inputState.keys[key];
}

bool Input_IsControllerButtonDown(SDL_GameControllerButton button) {
    return inputState.controllerButtons[button];
}

float Input_GetControllerAxisLeftX() {
    return inputState.controllerAxisLeftX;
}

float Input_GetControllerAxisLeftY() {
    return inputState.controllerAxisLeftY;
}

int Input_GetMouseX() {
    int x;
    SDL_GetMouseState(&x, NULL);
    return x;
}
