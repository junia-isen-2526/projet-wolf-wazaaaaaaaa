#include "child.h"
// #include "mermaid.c"
#include "wolf.h"
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));

  char rhyme[FOREST_WIDTH][FOREST_HEIGHT];
  const int rhymeCount = readLines("../ressources/comptine.txt", rhyme);

  char clothes[MAXClothes][FOREST_HEIGHT];
  const int clothesCount = readLines("../ressources/vetements.txt", clothes);

  Wolf wolf = {-1, -1, 0};

  // Init child and it's position
  // Create first path
  Child *child = malloc(sizeof(Child));
  beginningPos(child);
  Node *newPath = createPathNode();
  newPath->x = child->x;
  newPath->y = child->y;
  DiscoveryPath currentPath = *newPath;

  GameStep step = STEP_COMPTINE;

  while (!isGameOver(step, *child, &wolf)) {
    switch (step) {
    case STEP_COMPTINE:
      if (playComptineStep(rhyme, rhymeCount))
        step = STEP_DRESSING;
      break;
    case STEP_DRESSING:
      if (wolfDressingStep(&wolf, clothes, clothesCount)) {
        step = STEP_WOLF_MOVE;
      } else {
        step = STEP_COMPTINE;
      }
      break;
    case STEP_WOLF_MOVE:
      moveWolfStep(&wolf);
      break;
    }
    currentPath = moveChildStep(&currentPath);
  }

  // Create the Mermaid file
  // if (mermaiding(&myGraph) == 0) {
  //     printf("Mermaid graph file 'graph.mmd' created successfully.\n");
  // } else {
  //     printf("Failed to create Mermaid graph file.\n");
  // }

  return 0;

  return 0;
}
