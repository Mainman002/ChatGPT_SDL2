#ifndef RECT_COLLISION_H
#define RECT_COLLISION_H

#include <stdbool.h>

typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    Vector2 position;
    Vector2 size;
} Rect;

bool Rect_Hovering(Vector2 event, Rect node);
bool Rect_Collision(Rect rect1, Rect rect2);

#endif
