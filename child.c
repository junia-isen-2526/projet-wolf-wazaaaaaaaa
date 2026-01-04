#include "child.h"
#include <stdio.h>
#include <string.h>

char *getForest();

struct Node *createPathNode(int x, int y);

int isGameOver(const GameStep step, Child child, const Wolf *wolf) {
  // TODO
  return step == STEP_WOLF_MOVE;
}

void moveChildStep(Child *child, DiscoveryPath *currentPath) {
  static char forest[FOREST_WIDTH][FOREST_HEIGHT];
  readLines("../ressources/foret1.txt", forest);

  Node *newPath = createPathNode(child->x, child->y);

  if (currentPath->type == UNKNOW) {
    if (child->x < 0 || child->y < 0 || child->x > FOREST_WIDTH ||
        child->y > FOREST_HEIGHT) {
      currentPath->type = EXIT;
    } else if (forest[currentPath->x][currentPath->y] == '1') {
      currentPath->type = TREE;
    } else {
      currentPath->type = PATH;
    }
  } else {
    if (currentPath->northNeighbor != NULL &&
        currentPath->northEastNeighbor != NULL &&
        currentPath->eastNeighbor != NULL &&
        currentPath->southEastNeighbor != NULL &&
        currentPath->southNeighbor != NULL &&
        currentPath->southWestNeighbor != NULL &&
        currentPath->westNeighbor != NULL &&
        currentPath->northWestNeighbor != NULL) {
      currentPath->type = FULL;
    }
  }

  if (currentPath->type != PATH) {
    printf("Cleared %d %d %d", currentPath->id, currentPath->x, currentPath->y);
  } else if (currentPath->eastNeighbor == NULL) {
    child->x++;
    currentPath->eastNeighbor = newPath;
  } else if (currentPath->southEastNeighbor == NULL) {
    child->x++;
    child->y--;
    currentPath->southEastNeighbor = newPath;
  } else if (currentPath->southNeighbor == NULL) {
    child->y--;
    currentPath->southNeighbor = newPath;
  } else if (currentPath->southWestNeighbor == NULL) {
    child->x--;
    child->y--;
    currentPath->southWestNeighbor = newPath;
  } else if (currentPath->westNeighbor == NULL) {
    child->x--;
    currentPath->westNeighbor = newPath;
  } else if (currentPath->northWestNeighbor == NULL) {
    child->x--;
    child->y++;
    currentPath->northWestNeighbor = newPath;
  } else if (currentPath->northNeighbor == NULL) {
    child->y++;
    currentPath->northNeighbor = newPath;
  } else {
    child->x++;
    child->y++;
    currentPath->northEastNeighbor = newPath;
  }

  currentPath = newPath;
}

void beginningPos(Child *child) {
  // Child spawns on a border of the forest
  // Randomly look for a pos
  static char forest[FOREST_WIDTH][FOREST_HEIGHT];
  readLines("../ressources/foret1.txt", forest);

  // srand(time(NULL));

  int randBegin = rand() % 2;
  int analysisDirection = rand() % 2;

  switch (randBegin) {
  // pt départ tableau: x:0 ; y:0
  case 0:
    child->x = 0;
    child->y = 0;
    if (analysisDirection == 0) {
      // analysis in x
      for (child->x = 0; child->x < FOREST_WIDTH; child->x++) {
        // Est-ce que arbre ou pas
        // Si oui stopper analyse et définir point de départ
        if (forest[child->x][child->y] == ' ') {
          break;
        }
      }
    }
    if (analysisDirection == 1) {
      // analysis in y
      for (child->y = 0; child->y < FOREST_HEIGHT; child->y++) {
        // Est-ce que arbre ou pas
        // Si oui stopper analyse et définir point de départ
        if (forest[child->x][child->y] == ' ') {
          break;
        }
      }
    }

    break;

    // pt départ x:40 ; y:80
  case 1:
    child->x = FOREST_WIDTH;
    child->y = FOREST_HEIGHT;

    if (analysisDirection == 0) {
      // analysis in x
      for (child->x = FOREST_WIDTH - 1; child->x > 0; child->x--) {
        // Est-ce que arbre ou pas
        // Si oui stopper analyse et définir point de départ
        if (forest[child->x][child->y] == ' ') {
          break;
        }
      }
    }
    if (analysisDirection == 1) {
      // analysis in y
      for (child->y = FOREST_HEIGHT - 1; child->y > 0; child->y--) {
        // Est-ce que arbre ou pas
        // Si oui stopper analyse et définir point de départ
        if (forest[child->x][child->y] == ' ') {
          break;
        }
      }
    }
    break;
  default:
    child->x = 0;
    child->y = 0;

    if (analysisDirection == 0) {
      // analysis in x
      for (child->x = 0; child->x < FOREST_WIDTH; child->x++) {
        // Est-ce que arbre ou pas
        // Si oui stopper analyse et définir point de départ
        if (forest[child->x][child->y] == ' ') {
          break;
        }
      }
    }
    if (analysisDirection == 1) {
      // analysis in y
      for (child->y = 0; child->y < FOREST_HEIGHT; child->y++) {
        // Est-ce que arbre ou pas
        // Si oui stopper analyse et définir point de départ
        if (forest[child->x][child->y] == ' ') {
          break;
        }
      }
    }

    break;
  }
}

struct Node *createPathNode(int x, int y) {
  static unsigned int id = 0;

  Node *newPath = malloc(sizeof(Node));
  newPath->id = id++;
  newPath->x = x;
  newPath->y = y;
  newPath->type = UNKNOW;
  newPath->eastNeighbor = NULL;
  newPath->southEastNeighbor = NULL;
  newPath->southNeighbor = NULL;
  newPath->southWestNeighbor = NULL;
  newPath->westNeighbor = NULL;
  newPath->northWestNeighbor = NULL;
  newPath->northNeighbor = NULL;
  newPath->northEastNeighbor = NULL;

  return newPath;
}