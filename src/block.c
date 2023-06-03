#include "ball.h"
#include "block.h"

// Create an array of colors
SDL_Color colorList[] = {
    (SDL_Color){255, 0, 0, 255},
    (SDL_Color){255, 255, 0, 255},
    (SDL_Color){0, 255, 0, 255}
};

Block* Block_Create(int x, int y, int width, int height, int health, int idx) {
    Block* block = (Block*)malloc(sizeof(Block));
    if (block != NULL) {
        block->rect.x = x;
        block->rect.y = y;
        block->rect.w = width;
        block->rect.h = height;
        block->health = health;
        block->color = colorList[health-1];
    }
    return block;
}

void Block_Destroy(Block* block) {
    // free(block);
    block->color = (SDL_Color){50, 50, 50, 255};
}

void Block_Render(Block* block, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, block->color.r, block->color.g, block->color.b, block->color.a);
    SDL_RenderFillRect(renderer, &(block->rect));
}

bool Block_CollideWithBall(Block* block, Ball* ball) {
    // Calculate the distance between the centers of the ball and the block
    float dx = fabsf(ball->x - block->rect.x - block->rect.w * 0.5f);
    float dy = fabsf(ball->y - block->rect.y - block->rect.h * 0.5f);

    // Calculate the maximum distance before a collision occurs
    float maxDistanceX = block->rect.w * 0.5f + ball->radius;
    float maxDistanceY = block->rect.h * 0.5f + ball->radius;

    // Check if the ball collides with the block
    if (dx < maxDistanceX && dy < maxDistanceY) {
        // Determine the side of collision based on the difference between
        // the maximum distance and the actual distance in both X and Y directions
        float offsetX = maxDistanceX - dx;
        float offsetY = maxDistanceY - dy;

        if (offsetX < offsetY) {
            // Colliding from the left or right side
            if (ball->x < block->rect.x + block->rect.w * 0.5f) {
                // Colliding from the left side
                Ball_Bounce(ball, -1.0f, 0.0f); // Set collision normal to (-1, 0)
            } else {
                // Colliding from the right side
                Ball_Bounce(ball, 1.0f, 0.0f); // Set collision normal to (1, 0)
            }
        } else {
            // Colliding from the top or bottom side
            if (ball->y < block->rect.y + block->rect.h * 0.5f) {
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



void Block_ReduceHealth(Block* block, int amount) {
    block->health -= amount;
    block->color = colorList[block->health-1];
}

int Block_GetHealth(Block* block) {
    return block->health;
}
