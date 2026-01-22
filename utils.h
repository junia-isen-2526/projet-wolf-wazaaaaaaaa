#ifndef UTILS_H
#define UTILS_H

#define FOREST_WIDTH 40
#define FOREST_HEIGHT 80

int readLines(const char *filename, char forest[FOREST_HEIGHT][FOREST_WIDTH]);
int readLinesText(const char *filename, char lines[][256], int maxLines);
int manhattanDistance(int x1, int y1, int x2, int y2);

#endif
