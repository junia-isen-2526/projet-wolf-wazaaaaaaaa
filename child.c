#include "child.h"

char *getForest();

Node *findAvailablePath(Node *startNode);

int isGameOver(const GameStep step, Child child, const Wolf *wolf) {
  // TODO
  return step == STEP_WOLF_MOVE;
}

DiscoveryPath moveChildStep(DiscoveryPath *currentPath) {
  detectPathType(currentPath);

  // If the cell is not of 'path' type that mean that we need to go back
  // Else we go to an adjacent cell not yet discovered
  if (currentPath->type != PATH) {
    printf("Cleared %d : %d %d ; ", currentPath->id, currentPath->x,
           currentPath->y);

    Node *backtrackNode = findAvailablePath(currentPath);

    if (backtrackNode != NULL) {
      printf("find %d\n", backtrackNode->id);
      return *backtrackNode;
    } else {
      printf("finished\n");
      return *currentPath;
    }
  } else {
    Node *newPath = createPathNode();
    if (currentPath->eastNeighbor == NULL) {
      newPath->x = currentPath->x + 1;
      newPath->y = currentPath->y;
      currentPath->eastNeighbor = newPath;
      newPath->westNeighbor = currentPath;
      printf("new W %d\n", newPath->westNeighbor->id);
    } else if (currentPath->southEastNeighbor == NULL) {
      newPath->x = currentPath->x + 1;
      newPath->y = currentPath->y - 1;
      currentPath->southEastNeighbor = newPath;
      newPath->northWestNeighbor = currentPath;
      printf("new NW %d\n", newPath->northWestNeighbor->id);
    } else if (currentPath->southNeighbor == NULL) {
      newPath->x = currentPath->x;
      newPath->y = currentPath->y - 1;
      currentPath->southNeighbor = newPath;
      newPath->northNeighbor = currentPath;
      printf("new N %d\n", newPath->northNeighbor->id);
    } else if (currentPath->southWestNeighbor == NULL) {
      newPath->x = currentPath->x - 1;
      newPath->y = currentPath->y - 1;
      currentPath->southWestNeighbor = newPath;
      newPath->northEastNeighbor = currentPath;
      printf("new NE %d\n", newPath->northEastNeighbor->id);
    } else if (currentPath->westNeighbor == NULL) {
      newPath->x = currentPath->x - 1;
      newPath->y = currentPath->y;
      currentPath->westNeighbor = newPath;
      newPath->eastNeighbor = currentPath;
      printf("new E %d\n", newPath->eastNeighbor->id);
    } else if (currentPath->northWestNeighbor == NULL) {
      newPath->x = currentPath->x - 1;
      newPath->y = currentPath->y + 1;
      currentPath->northWestNeighbor = newPath;
      newPath->southEastNeighbor = currentPath;
      printf("new SE %d\n", newPath->southEastNeighbor->id);
    } else if (currentPath->northNeighbor == NULL) {
      newPath->x = currentPath->x;
      newPath->y = currentPath->y + 1;
      currentPath->northNeighbor = newPath;
      newPath->southNeighbor = currentPath;
      printf("new S%d\n", newPath->southNeighbor->id);
    } else if (currentPath->northEastNeighbor == NULL) {
      newPath->x = currentPath->x + 1;
      newPath->y = currentPath->y + 1;
      currentPath->northEastNeighbor = newPath;
      newPath->southWestNeighbor = currentPath;
      printf("new SW %d\n", newPath->southWestNeighbor->id);
    } else {
      printf(":c\n");
    }
    return *newPath;
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
  // Detect if all 8 adjacent cell are already discovered
  if (path->northNeighbor != NULL && path->northEastNeighbor != NULL &&
      path->eastNeighbor != NULL && path->southEastNeighbor != NULL &&
      path->southNeighbor != NULL && path->southWestNeighbor != NULL &&
      path->westNeighbor != NULL && path->northWestNeighbor != NULL) {
    path->type = FULL;
  } else if (path->x < 0 || path->y < 0 || path->x > FOREST_WIDTH ||
             path->y > FOREST_HEIGHT) {
    path->type = EXIT;
  } else if (forest[path->x][path->y] == '1') {
    path->type = TREE;
  } else {
    path->type = PATH;
  }

  printf("path type of %d : %d\n", path->id, path->type);
}

Node *findAvailablePath(Node *startNode) {
  if (startNode == NULL) {
    return NULL;
  }

  // Use BFS with a fresh visited array each time
  Node *queue[1000];
  int visited[1000] = {0}; // NOT static - resets each call
  int front = 0, rear = 0;

  // Add start node to queue
  queue[rear++] = startNode;
  visited[startNode->id] = 1;

  printf("Starting search from node %d\n", startNode->id);

  while (front < rear) {
    Node *current = queue[front++];

    printf("Checking node %d at (%d,%d)\n", current->id, current->x,
           current->y);

    // Add all neighbors to queue
    Node *neighbors[] = {current->northNeighbor, current->northEastNeighbor,
                         current->eastNeighbor,  current->southEastNeighbor,
                         current->southNeighbor, current->southWestNeighbor,
                         current->westNeighbor,  current->northWestNeighbor};

    for (int i = 0; i < 8; i++) {
      if (neighbors[i] != NULL && neighbors[i]->id < 1000 &&
          !visited[neighbors[i]->id]) {
        queue[rear++] = neighbors[i];
        visited[neighbors[i]->id] = 1;
        printf("  Added neighbor %d to queue\n", neighbors[i]->id);
      }
    }
  }

  printf("No available path found\n");
  return NULL;
}