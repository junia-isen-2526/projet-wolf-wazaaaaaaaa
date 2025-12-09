#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wolf.h"

#ifndef WOLF_CHILD_H_
#define WOLF_CHILD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wolf.h"

// Structure de l'enfant
typedef struct {
    int x;
    int y;
} Child;
Child *create_child(int start_x, int start_y);
void move_right(Child *c);
void print_child(const Child *c);
int isGameOver(GameStep step, Child child, const Wolf *wolf);


void move_child_with_obstacle(Child *child, int **forest, int width, int height);

void moveChildStep(Child *child, int **forest, int width, int height);

#endif // CHILD_H
