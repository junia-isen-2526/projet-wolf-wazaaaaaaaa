#ifndef WOLF_MERMAID_H
#define WOLF_MERMAID_H
#include <stdio.h>
#include <string.h>

typedef struct {
  int id;
  int x;
  int y;
} Vertex;

typedef struct {
  Vertex *B;
  Vertex *A;
} Edge;

typedef struct Node Node;

struct Node {
  Edge *edge;
  Node *nextNode;
};

typedef struct {
  Node *firstNode;
} Graph;

int mermaiding(Graph *graph);

#endif // WOLF_MERMAID_H
