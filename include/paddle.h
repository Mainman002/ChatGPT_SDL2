// paddle.h
#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

typedef struct Paddle {
    float x;
    float y;
    float speed;
    float top_speed;
    float velocity;
    float rotation;
    SDL_Texture* texture;
} Paddle;

void Paddle_Init(Paddle* paddle, float x, float y, float top_speed, SDL_Texture* texture);
void Paddle_Update(Paddle* paddle, float deltaTime, int mouseX, int windowWidth);
void Paddle_Render(Paddle* paddle, SDL_Renderer* renderer);

#endif /* PADDLE_H */
