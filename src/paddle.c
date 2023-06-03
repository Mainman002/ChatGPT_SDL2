#include "ball.h"
#include "paddle.h"
#include "Input.h"

#include <math.h>

#define PADDLE_WIDTH 128
#define PADDLE_HEIGHT 24
#define PADDLE_ROTATION_LIMIT 10
// #define PADDLE_MOVEMENT_SPEED 200

void Paddle_Init(Paddle* paddle, float x, float y, int width, int height, float top_speed, SDL_Texture* texture) {
    paddle->x = x;
    paddle->y = y;
    paddle->rect.w = width;
    paddle->rect.h = height;
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

bool Paddle_CollideWithBall(Paddle* paddle, Ball* ball) {
    // Calculate the distance between the centers of the ball and the block
    float dx = fabsf(ball->x - paddle->x - paddle->rect.w * 0.5f);
    float dy = fabsf(ball->y - paddle->y - paddle->rect.h * 0.5f);

    // Calculate the maximum distance before a collision occurs
    float maxDistanceX = paddle->rect.w * 0.5f + ball->radius;
    float maxDistanceY = paddle->rect.h * 0.5f + ball->radius;

    // Check if the ball collides with the block
    if (dx < maxDistanceX && dy < maxDistanceY) {
        // Determine the side of collision based on the difference between
        // the maximum distance and the actual distance in both X and Y directions
        float offsetX = maxDistanceX - dx;
        float offsetY = maxDistanceY - dy;

        if (offsetX < offsetY) {
            // Colliding from the left or right side
            if (ball->x < paddle->rect.x + paddle->rect.w * 0.5f) {
                // Colliding from the left side
                Ball_Bounce(ball, -1.0f, 0.0f); // Set collision normal to (-1, 0)
            } else {
                // Colliding from the right side
                Ball_Bounce(ball, 1.0f, 0.0f); // Set collision normal to (1, 0)
            }
        } else {
            // Colliding from the top or bottom side
            if (ball->y < paddle->rect.y + paddle->rect.h * 0.5f) {
                // Colliding from the top side
                Ball_Bounce(ball, 0.0f, -1.0f); // Set collision normal to (0, -1)
            } else {
                // Colliding from the bottom side
                Ball_Bounce(ball, 0.0f, 1.0f); // Set collision normal to (0, 1)
            }
        }

        return true; // Collision occurred
    }

    return false; // No collision
}
