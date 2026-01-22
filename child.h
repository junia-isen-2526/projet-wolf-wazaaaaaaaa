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
  struct Node *northNeighbor;
  struct Node *northEastNeighbor;
  struct Node *eastNeighbor;
  struct Node *southEastNeighbor;
  struct Node *southNeighbor;
  struct Node *southWestNeighbor;
  struct Node *westNeighbor;
  struct Node *northWestNeighbor;
} Node;

typedef Node DiscoveryPath;

static char forest[FOREST_WIDTH][FOREST_HEIGHT];
int isGameOver(GameStep step, Child child, const Wolf *wolf);
DiscoveryPath moveChildStep(DiscoveryPath *path);
void beginningPos(Child *child);
struct Node *createPathNode();
void detectPathType(Node *path);

#endif // WOLF__CHILD_H_
