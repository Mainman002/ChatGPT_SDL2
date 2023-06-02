// ball.h
#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

typedef struct {
    float x;
    float y;
    float dx;
    float dy;
    float speed;
    float rotationSpeed;
    int radius;
    float rotation;
    SDL_Texture* texture;
    float velocityX;
    float velocityY;
} Ball;

void Ball_Init(Ball* ball, float x, float y, float speed, float rotationSpeed, int radius, SDL_Texture* texture);
void Ball_Update(Ball* ball, float deltaTime, int windowWidth, int windowHeight);
void Ball_Render(Ball* ball, SDL_Renderer* renderer);
void Ball_CollideWithWindow(Ball* ball, int windowWidth, int windowHeight);
void Ball_Cleanup(Ball* ball);


#endif
