#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int readLines(const char *filename, char forest[FOREST_HEIGHT][FOREST_WIDTH]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erreur : impossible d'ouvrir %s\n", filename);
        return 0;
    }
    
    int lineCount = 0;
    char buffer[256];
    
    while (fgets(buffer, sizeof(buffer), file) && lineCount < FOREST_HEIGHT) {
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        for (int i = 0; i < FOREST_WIDTH && i < len; i++) {
            forest[lineCount][i] = buffer[i];
        }
        for (int i = len; i < FOREST_WIDTH; i++) {
            forest[lineCount][i] = ' ';
        }
        
        lineCount++;
    }
    
    fclose(file);
    return lineCount;
}

int readLinesText(const char *filename, char lines[][256], int maxLines) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erreur : impossible d'ouvrir %s\n", filename);
        return 0;
    }
    
    int lineCount = 0;
    while (fgets(lines[lineCount], 256, file) && lineCount < maxLines) {
        int len = strlen(lines[lineCount]);
        if (len > 0 && lines[lineCount][len - 1] == '\n') {
            lines[lineCount][len - 1] = '\0';
        }
        lineCount++;
    }
    
    fclose(file);
    return lineCount;
}

int manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}
