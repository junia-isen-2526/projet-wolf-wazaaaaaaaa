#ifndef UTILS_H
#define UTILS_H

#include "wolf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readLinesText(const char *filename, char lines[][256], int maxLines);
int manhattanDistance(int x1, int y1, int x2, int y2);

#endif
