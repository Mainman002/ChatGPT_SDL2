// paddle.h
#ifndef PADDLE_H
#define PADDLE_H

#include "ball.h"

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct Paddle {
    SDL_Rect rect;
    float x;
    float y;
    float speed;
    float top_speed;
    float velocity;
    float rotation;
    SDL_Texture* texture;
} Paddle;

void Paddle_Init(Paddle* paddle, float x, float y, int width, int height, float top_speed, SDL_Texture* texture);
void Paddle_Update(Paddle* paddle, float deltaTime, int mouseX, int windowWidth);
void Paddle_Render(Paddle* paddle, SDL_Renderer* renderer);
bool Paddle_CollideWithBall(Paddle* paddle, Ball* ball);

#endif /* PADDLE_H */
