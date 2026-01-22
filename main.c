#include "child.h"
// #include "mermaid.c"
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));

  char rhyme[MAXClothes][FOREST_WIDTH];
  const int rhymeCount = readLines("../ressources/comptine.txt", rhyme);

  char clothes[MAXClothes][FOREST_WIDTH];
  const int clothesCount = readLines("../ressources/vetements.txt", clothes);

  Wolf wolf = {-1, -1, 0,
               0,  0,  0}; // x, y, active, isOut, clothesCount, clothesToWear

  // Init child and it's position
  // Create first path
  Child *child = malloc(sizeof(Child));
  beginningPos(child);

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
    moveChildStep(child);
  }

  free(child);

  return 0;
}
