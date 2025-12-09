#include "child.h"

#include <stdio.h>
#include "child.h"
#include "wolf.h"
Child *create_child(int start_x, int start_y) {
    Child *c = malloc(sizeof(Child));
    if (c == NULL) return NULL;
    c->x = start_x;
    c->y = start_y;
    return c;
}

void move_right(Child *c) {
    if (c == NULL) return;
    c->x += 1;
}


void print_child(const Child *c) {
    if (c == NULL) return;
    printf("Enfant -> x = %d, y = %d\n", c->x, c->y);
}


int isGameOver(GameStep step, Child child, const Wolf *wolf) {
    if (wolf == NULL) return 0;



    if (child.x == wolf->x && child.y == wolf->y) {
        return 1; // GAME OVER
    }


    if (step == 0) {
        return 1;
    }

    return 0;

}

void moveChildStep(Child *child, int **forest, int width, int height) {
    move_right(child);
}
void move_child_with_obstacle(Child *child, int **forest, int width, int height) {
    if (child == NULL || forest == NULL) return;

    int next_x = child->x + 1;
    int next_y = child->y;
    if (next_x >= width) next_x = width - 1;
    if (next_y >= height) next_y = height - 1;
    if (forest[next_y][next_x] == 1) {
        if (child->y + 1 < height) {
            child->x += 1;
            child->y += 1;
        } else {
            child->x += 1;
        }
    } else {
        child->x += 1;
    }
}
