#include "child.h"

char *getForest();

int isGameOver(const GameStep step, Child child, const Wolf *wolf) {
  // TODO
  return step == STEP_WOLF_MOVE;
}

void moveChildStep(DiscoveryPath *currentPath) {
  // Detect if all 8 adjacent cell are already discovered
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

  // If the cell is not of 'path' type that mean that we need to go back
  // Else we go to an adjacent cell not yet discovered
  if (currentPath->type != PATH) {
    printf("Cleared %d : %d %d ; ", currentPath->id, currentPath->x,
           currentPath->y);
  } else {
    Node *newPath = createPathNode();
    if (currentPath->eastNeighbor == NULL) {
      newPath->x = currentPath->x++;
      currentPath->eastNeighbor = newPath;
    } else if (currentPath->southEastNeighbor == NULL) {
      newPath->x = currentPath->x++;
      newPath->y = currentPath->y--;
      currentPath->southEastNeighbor = newPath;
    } else if (currentPath->southNeighbor == NULL) {
      newPath->y = currentPath->y--;
      currentPath->southNeighbor = newPath;
    } else if (currentPath->southWestNeighbor == NULL) {
      newPath->x = currentPath->x--;
      newPath->y = currentPath->y--;
      currentPath->southWestNeighbor = newPath;
    } else if (currentPath->westNeighbor == NULL) {
      newPath->x = currentPath->x--;
      currentPath->westNeighbor = newPath;
    } else if (currentPath->northWestNeighbor == NULL) {
      newPath->x = currentPath->x--;
      newPath->y = currentPath->y++;
      currentPath->northWestNeighbor = newPath;
    } else if (currentPath->northNeighbor == NULL) {
      newPath->y = currentPath->y++;
      currentPath->northNeighbor = newPath;
    } else {
      newPath->x = currentPath->x++;
      newPath->y = currentPath->y++;
      currentPath->northEastNeighbor = newPath;
    }
    detectPathType(newPath);
    currentPath = newPath;
  }
}

void beginningPos(Child *child) {
  // Child spawns on a border of the forest
  // Randomly look for a pos
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

struct Node *createPathNode() {
  static unsigned int id = 1;
  printf("\ncreating node %d ...\n", id);

  Node *newPath = malloc(sizeof(Node));
  newPath->id = id++;
  newPath->x = 0;
  newPath->y = 0;
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

void detectPathType(Node *path) {
  if (path->x < 0 || path->y < 0 || path->x > FOREST_WIDTH ||
      path->y > FOREST_HEIGHT) {
    path->type = EXIT;
  } else if (forest[path->x][path->y] == '1') {
    path->type = TREE;
  } else {
    path->type = PATH;
  }
}