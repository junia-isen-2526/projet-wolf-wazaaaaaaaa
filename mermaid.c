#include "mermaid.h"

int mermaiding(Graph *graph) {
  FILE *file = fopen("graph.mmd", "w");
  if (file == NULL) {
    perror("Error opening file");
    return -1;
  }

  fprintf(file, "graph TD\n");

  if (graph == NULL || graph->firstNode == NULL) {
    // Handle empty graph gracefully
    fclose(file);
    return 0;
  }

  Node *currentNode = graph->firstNode;
  while (currentNode != NULL) {
    if (currentNode->edge != NULL) {
      Vertex *vertexA = currentNode->edge->A;
      Vertex *vertexB = currentNode->edge->B;

      if (vertexA != NULL && vertexB != NULL) {
        fprintf(file, "    %d(%d,%d) --> %d(%d,%d)\n", vertexA->id, vertexA->x,
                vertexA->y, vertexB->id, vertexB->x, vertexB->y);
      }
    }
    currentNode = currentNode->nextNode;
  }

  fclose(file);
  return 0;
}