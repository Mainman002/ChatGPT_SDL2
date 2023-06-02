#include "ColliderManager.h"

bool Rect_Hovering(Vector2 event, Rect node) {
    if (event.x > node.position.x && event.x < node.position.x + node.size.x &&
        event.y > node.position.y && event.y < node.position.y + node.size.y) {
        return true;
    }
    return false;
}

bool Rect_Collision(Rect rect1, Rect rect2) {
    if (rect1.position.x + rect1.size.x >= rect2.position.x &&
        rect1.position.x <= rect2.position.x + rect2.size.x &&
        rect1.position.y + rect1.size.y >= rect2.position.y &&
        rect1.position.y <= rect2.position.y + rect2.size.y) {
        return true;
    }
    return false;
}
