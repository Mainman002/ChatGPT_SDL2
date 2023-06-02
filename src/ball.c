#include "ball.h"

void Ball_Init(Ball* ball, float x, float y, float speed, float rotationSpeed, int radius, SDL_Texture* texture) {
    ball->x = x;
    ball->y = y;
    ball->speed = speed;
    ball->velocityX = speed;
    ball->velocityY = speed;
    ball->rotationSpeed = rotationSpeed;
    ball->radius = radius;
    ball->rotation = 0.0f;
    ball->texture = texture;
}

void Ball_Update(Ball* ball, float deltaTime, int windowWidth, int windowHeight) {
    float movement = ball->speed * deltaTime;

    ball->x += ball->velocityX * movement;
    ball->y += ball->velocityY * movement;

    // Check for collision with window borders
    if (ball->x - ball->radius < 0) {
        ball->x = ball->radius;
        ball->velocityX = -ball->velocityX;
    }
    if (ball->x + ball->radius > windowWidth) {
        ball->x = windowWidth - ball->radius;
        ball->velocityX = -ball->velocityX;
    }
    if (ball->y - ball->radius < 0) {
        ball->y = ball->radius;
        ball->velocityY = -ball->velocityY;
    }
    if (ball->y + ball->radius > windowHeight) {
        ball->y = windowHeight - ball->radius;
        ball->velocityY = -ball->velocityY;
    }

    // Update the ball's rotation based on delta time
    ball->rotation += ball->rotationSpeed * deltaTime;
}

void Ball_Render(Ball* ball, SDL_Renderer* renderer) {
    SDL_Rect destRect = {
        (int)(ball->x - ball->radius),
        (int)(ball->y - ball->radius),
        ball->radius * 2,
        ball->radius * 2
    };

    SDL_RenderCopyEx(renderer, ball->texture, NULL, &destRect, ball->rotation, NULL, SDL_FLIP_NONE);
}

void Ball_CollideWithWindow(Ball* ball, int windowWidth, int windowHeight) {
    if (ball->x - ball->radius < 0 || ball->x + ball->radius > windowWidth) {
        ball->velocityX = -ball->velocityX;
    }
    if (ball->y - ball->radius < 0 || ball->y + ball->radius > windowHeight) {
        ball->velocityY = -ball->velocityY;
    }
}

