#include "wolf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WOLF__CHILD_H_
#define WOLF__CHILD_H_

typedef struct {
  int x;
  int y;
} Child;

typedef enum { PATH, EXIT, TREE, FULL } NodeType;

typedef struct Node {
  int id;
  int x;
  int y;
  NodeType type;
  Node *northNeighbor;
  Node *northEastNeighbor;
  Node *eastNeighbor;
  Node *southEastNeighbor;
  Node *southNeighbor;
  Node *southWestNeighbor;
  Node *westNeighbor;
  Node *northWestNeighbor;
} Node;

typedef Node DiscoveryPath;

static char forest[FOREST_WIDTH][FOREST_HEIGHT];

int isGameOver(GameStep step, Child child, const Wolf *wolf);

void moveChildStep(Child *child, DiscoveryPath *path);

void beginningPos(Child *child);

struct Node *createPathNode(int x, int y);

#endif // WOLF__CHILD_H_
