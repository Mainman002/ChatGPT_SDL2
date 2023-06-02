// paddle.c
#include "paddle.h"
#include "Input.h"

#include <math.h>

#define PADDLE_WIDTH 128
#define PADDLE_HEIGHT 24
#define PADDLE_ROTATION_LIMIT 10
// #define PADDLE_MOVEMENT_SPEED 200

void Paddle_Init(Paddle* paddle, float x, float y, float top_speed, SDL_Texture* texture) {
    paddle->x = x;
    paddle->y = y;
    paddle->top_speed = top_speed*10;
    paddle->velocity = 0;
    paddle->rotation = 0;
    paddle->texture = texture;
}

void Paddle_Update(Paddle* paddle, float deltaTime, int mouseX, int windowWidth) {
    // Calculate the paddle's target X position based on the mouse position
    float targetX = mouseX - PADDLE_WIDTH * 0.5f;

    // Clamp the target X position within the window bounds
    if (targetX < 0) {
        targetX = 0;
    } else if (targetX > windowWidth - PADDLE_WIDTH) {
        targetX = windowWidth - PADDLE_WIDTH;
    }

    // Move the paddle towards the target X position
    float speed = paddle->top_speed * deltaTime;
    if (paddle->x < targetX) {
        paddle->x += speed;
        if (paddle->x > targetX) {
            paddle->x = targetX;
        }
    } else if (paddle->x > targetX) {
        paddle->x -= speed;
        if (paddle->x < targetX) {
            paddle->x = targetX;
        }
    }
}

void Paddle_Render(Paddle* paddle, SDL_Renderer* renderer) {
    SDL_Rect destRect = {
        (int)paddle->x,
        (int)paddle->y,
        PADDLE_WIDTH,
        PADDLE_HEIGHT
    };

    SDL_RenderCopyEx(renderer, paddle->texture, NULL, &destRect, paddle->rotation, NULL, SDL_FLIP_NONE);
}
