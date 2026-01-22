#include "wolf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WOLF__CHILD_H_
#define WOLF__CHILD_H_

#define MAX_VISITED 1000

typedef struct Position {
  int x;
  int y;
} Position;

typedef struct Child {
  int x;
  int y;
  unsigned int visitedCount;
  Position visited[MAX_VISITED]; // Not pointers!
  unsigned char isAlive;
  unsigned char hasEscaped;
  unsigned int startX;
  unsigned int startY;
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

static char forest[FOREST_HEIGHT][FOREST_WIDTH];
int isGameOver(const GameStep step, Child child, const Wolf *wolf);
void moveChildStep(Child *child);
void beginningPos(Child *child);
void detectPathType(Node *path);
void moveTowardsStart(Child *child);
int isAtStartPosition(const Child *child);
void generateMermaidGraph(const Child *child, const char *filename);

#endif // WOLF__CHILD_H_
