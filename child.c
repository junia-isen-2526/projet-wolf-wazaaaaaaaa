#include "child.h"

void addVisitedPosition(Child *child, int x, int y);
int hasVisitedPosition(const Child *child, int x, int y);

void addVisitedPosition(Child *child, int x, int y) {
  if (!hasVisitedPosition(child, x, y) && child->visitedCount < MAX_VISITED) {
    child->visited[child->visitedCount].x = x;
    child->visited[child->visitedCount].y = y;
    child->visitedCount++;
  }
}

int hasVisitedPosition(const Child *child, int x, int y) {
  for (int i = 0; i < child->visitedCount; i++) {
    if (child->visited[i].x == x && child->visited[i].y == y) {
      return 1;
    }
  }
  return 0;
}

int isGameOver(const GameStep step, Child child, const Wolf *wolf) {
  // fin jeu, gosse éclaté par le loup ou vivant
  if (!child.isAlive) {
    return 1;
  }
  if (child.hasEscaped && wolf->isOut) {
    return 1;
  }
  return 0;
}

void moveChildStep(Child *child) {
  char forest[FOREST_HEIGHT][FOREST_WIDTH];
  readLines("../ressources/foret1.txt", forest);

  // ajouter position à l'instant aux positions parcourues par le gosse
  addVisitedPosition(child, child->x, child->y);

  int directions[8][2] = {
      {0, -1},  // Haut
      {0, 1},   // Bas
      {-1, 0},  // Gauche
      {1, 0},   // Droite
      {-1, -1}, // Haut-gauche
      {1, -1},  // Haut-droite
      {-1, 1},  // Bas-gauche
      {1, 1}    // Bas-droite
  };

  // Liste des directions valides
  int validMoves[8][2];
  int validCount = 0;

  // chercher directions valide
  for (int i = 0; i < 8; i++) {
    int newX = child->x + directions[i][0];
    int newY = child->y + directions[i][1];

    // check si la nouvelle position est dans les limites de la map
    if (newX >= 0 && newX < FOREST_WIDTH && newY >= 0 && newY < FOREST_HEIGHT) {

      // voir si c'est un espace sans arbre
      if (forest[newY][newX] == ' ') {
        validMoves[validCount][0] = newX;
        validMoves[validCount][1] = newY;
        validCount++;
      }
    }
  }

  // si moves valides existent, en choisir un random
  if (validCount > 0) {
    int chosenMove = rand() % validCount;
    child->x = validMoves[chosenMove][0];
    child->y = validMoves[chosenMove][1];
  }
}

int isAtStartPosition(const Child *child) {
  return (child->x == child->startX && child->y == child->startY);
}

void moveTowardsStart(Child *child) {
  char forest[FOREST_HEIGHT][FOREST_WIDTH];
  readLines("../ressources/foret1.txt", forest);

  addVisitedPosition(child, child->x, child->y);

  int dx = child->startX - child->x;
  int dy = child->startY - child->y;

  int moveX = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
  int moveY = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

  int newX = child->x + moveX;
  int newY = child->y + moveY;

  if (newX >= 0 && newX < FOREST_WIDTH && newY >= 0 && newY < FOREST_HEIGHT &&
      forest[newY][newX] == ' ') {
    child->x = newX;
    child->y = newY;
    return;
  }

  // si impossible, essayer directions à côtés
  int directions[8][2] = {{moveX, 0},      {0, moveY},      {moveX, moveY},
                          {-moveY, moveX}, {moveY, -moveX}, {-moveX, -moveY},
                          {-moveX, 0},     {0, -moveY}};

  for (int i = 0; i < 8; i++) {
    newX = child->x + directions[i][0];
    newY = child->y + directions[i][1];

    if (newX >= 0 && newX < FOREST_WIDTH && newY >= 0 && newY < FOREST_HEIGHT &&
        forest[newY][newX] == ' ') {
      child->x = newX;
      child->y = newY;
      return;
    }
  }
}

void beginningPos(Child *child) {
  char forest[FOREST_HEIGHT][FOREST_WIDTH];
  readLines("../ressources/foret1.txt", forest);

  int randBegin = rand() % 2;
  int analysisDirection = rand() % 2;

  switch (randBegin) {
  case 0:
    child->x = 0;
    child->y = 0;
    if (analysisDirection == 0) {
      for (child->x = 0; child->x < FOREST_WIDTH; child->x++) {
        if (forest[child->y][child->x] == ' ') {
          break;
        }
      }
    } else {
      for (child->y = 0; child->y < FOREST_HEIGHT; child->y++) {
        if (forest[child->y][child->x] == ' ') {
          break;
        }
      }
    }
    break;

  case 1:
    child->x = FOREST_WIDTH - 1;
    child->y = FOREST_HEIGHT - 1;

    if (analysisDirection == 0) {
      for (child->x = FOREST_WIDTH - 1; child->x >= 0; child->x--) {
        if (forest[child->y][child->x] == ' ') {
          break;
        }
      }
    } else {
      for (child->y = FOREST_HEIGHT - 1; child->y >= 0; child->y--) {
        if (forest[child->y][child->x] == ' ') {
          break;
        }
      }
    }
    break;
  }

  child->startX = child->x;
  child->startY = child->y;
  child->visitedCount = 0;
  child->isAlive = 1;
  child->hasEscaped = 0;
  addVisitedPosition(child, child->x, child->y);
}

void generateMermaidGraph(const Child *child, const char *filename) {
  FILE *file = fopen(filename, "w");
  if (!file) {
    printf("Erreur : impossible d'ouvrir le fichier %s\n", filename);
    return;
  }

  fprintf(file, "graph TD\n");

  // créer les noeuds
  for (int i = 0; i < child->visitedCount - 1; i++) {
    int x1 = child->visited[i].x;
    int y1 = child->visited[i].y;
    int x2 = child->visited[i + 1].x;
    int y2 = child->visited[i + 1].y;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    if (dx <= 1 && dy <= 1 && (dx + dy) > 0) {
      fprintf(file, "    %d(%d,%d) --> %d(%d,%d)\n", i + 1, x1, y1, i + 2, x2,
              y2);
    }
  }

  fclose(file);
  printf("Graph Mermaid généré dans %s\n", filename);
}
