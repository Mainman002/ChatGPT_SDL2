// block.h
#ifndef BLOCK_H
#define BLOCK_H

#include "ball.h"

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct Block {
    SDL_Rect rect;
    int health;
    SDL_Color color;
    SDL_Texture* texture;
} Block;

Block* Block_Create(int x, int y, int width, int height, int health, int idx, SDL_Texture* texture);
void Block_Destroy(Block* block);
void Block_Render(Block* block, SDL_Renderer* renderer);
bool Block_CollideWithBall(Block* block, Ball* ball);
void Block_ReduceHealth(Block* block, int amount);
int Block_GetHealth(Block* block);

#endif  // BLOCK_H
