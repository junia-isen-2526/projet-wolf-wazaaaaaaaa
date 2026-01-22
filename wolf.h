#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WOLF__WOLF_H_
#define WOLF__WOLF_H_

#define MAXClothes 50
#define FOREST_WIDTH 80
#define FOREST_HEIGHT 40

typedef enum { STEP_COMPTINE, STEP_DRESSING, STEP_WOLF_MOVE } GameStep;

typedef struct {
  int x;
  int y;
  int active;
  unsigned char isOut;
  unsigned int clothesCount;
  unsigned int clothesToWear;
} Wolf;

int readLines(const char *filename, char lines[][FOREST_WIDTH]);

int playComptineStep(char rhyme[][FOREST_WIDTH], int rhymeCount);

int wolfDressingStep(Wolf *wolf, const char clothes[MAXClothes][FOREST_WIDTH],
                     int clothesCount);

void moveWolfStep(Wolf *wolf);

#endif // WOLF__WOLF_H_
