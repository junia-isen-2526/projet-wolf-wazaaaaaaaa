#include "child.h"
#include <stdio.h>
#include <string.h>

char *getForest();

int isGameOver(const GameStep step, Child child, const Wolf *wolf) {
  // TODO
  return step == STEP_WOLF_MOVE;
}

void moveChildStep(Child *child, DiscoveryPath *path) {
  static unsigned int id = 0;

  static char forest[FOREST_WIDTH][FOREST_HEIGHT];
  readLines("../ressources/foret1.txt", forest);

  if (path == NULL) {
    path->id = id++;
    path->x = child->x;
    path->y = child->y;
  }

  if (path->type == NULL) {
    if (child->x < 0 || child->y < 0 || child->x > FOREST_WIDTH ||
        child->y > FOREST_HEIGHT) {
      path->type = EXIT;
    } else if (forest[path->x][path->y] == '1') {
      path->type = TREE;
    } else {
      path->type = PATH;
    }
  } else {
    if (path->nortNeighbor != NULL && path->nortEastNeighbor != NULL &&
        path->eastNeighbor != NULL && path->southEastNeighbor != NULL &&
        path->southNeighbor != NULL && path->southWestNeighbor != NULL &&
        path->westNeighbor != NULL && path->nortWestNeighbor != NULL) {
      path->type = FULL;
    }
  }

  if (path->type != PATH) {
    printf("Cleared %d %d %d", path->id, path->x, path->y);
  }

  if (path->eastNeighbor == NULL) {
    child->x++;
  } else if (path->southEastNeighbor == NULL) {
    child->x++;
    child->y--;
  } else if (path->southNeighbor == NULL) {
    child->y--;
  } else if (path->southWestNeighbor == NULL) {
    child->x--;
    child->y--;
  } else if (path->westNeighbor == NULL) {
    child->x--;
  } else if (path->nortWestNeighbor == NULL) {
    child->x--;
    child->y++;
  } else if (path->nortNeighbor == NULL) {
    child->y++;
  } else {
    child->x++;
    child->y++;
  }
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
