#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "child.h"
#include "wolf.h"
#include "utils.h"

#define MAX_COMPTINE_LINES 50
#define MAX_CLOTHES_LINES 20

void displayForest(const Child *child, const Wolf *wolf) {
    char forest[FOREST_HEIGHT][FOREST_WIDTH];
    readLines("../ressources/foret1.txt", forest);
    
    printf("\n=== CARTE DE LA FORÊT ===\n");
    for (int y = 0; y < FOREST_HEIGHT; y++) {
        for (int x = 0; x < FOREST_WIDTH; x++) {
            if (child->x == x && child->y == y) {
                printf("E"); // le mineur (l'enfant)
            } else if (wolf->isOut && wolf->x == x && wolf->y == y) {
                printf("L"); // loup
            } else if (child->startX == x && child->startY == y) {
                printf("D"); // poing de départ
            } else {
                printf("%c", forest[y][x]);
            }
        }
        printf("\n");
    }
    printf("==========================\n\n");
}

int main() {
    srand(time(NULL));
    
    Child child;
    Wolf wolf;
    
    char comptine[MAX_COMPTINE_LINES][256];
    char vetements[MAX_CLOTHES_LINES][256];
    
    int comptineLines = readLinesText("../ressources/comptine.txt", comptine, MAX_COMPTINE_LINES);
    int vetementLines = readLinesText("../ressources/vetements.txt", vetements, MAX_CLOTHES_LINES);
    
    if (comptineLines == 0 || vetementLines == 0) {
        printf("Erreur : fichiers manquants\n");
        return 1;
    }
    
    // starting point du gosse
    beginningPos(&child);
    initWolf(&wolf);
    
    printf("PROMENONS-NOUS DANS LES BOIS\n\n");
    printf("L'enfant commence à la position (%d, %d)\n\n", child.x, child.y);
    
    int comptineIndex = 0;
    int totalMoves = 0;
    GameStep currentStep = STEP_CHILD_MOVE;
    
    // Exploration avant que le loup sorte de sa caverne
    while (!wolf.isOut) {
        // comptine
        printf("%s\n", comptine[comptineIndex % comptineLines]);
        comptineIndex++;
        
        // gosse qui bouge
        moveChildStep(&child);
        totalMoves++;
        printf("L'enfant se déplace vers (%d, %d) - Positions visitées : %d\n", 
               child.x, child.y, child.visitedCount);
        
        // le loup s'habille
        wolf.clothesCount++;
        if (wolf.clothesCount < wolf.clothesToWear) {
            int clotheIndex = rand() % vetementLines;
            printf("Loup : %s (%d/%d)\n\n", 
                   vetements[clotheIndex], wolf.clothesCount, wolf.clothesToWear);
        } else {
            revealWolf(&wolf);
        }
    }
    
    // retour au point de départ, le loup est sortit
    printf("\nL'ENFANT DOIT RETOURNER AU POINT DE DÉPART ! \n\n");
    
    while (!isGameOver(currentStep, child, &wolf)) {
        if (currentStep == STEP_CHILD_MOVE) {

            moveTowardsStart(&child);
            printf("L'enfant fuit vers le départ (%d, %d) - Position actuelle : (%d, %d)\n", 
                   child.startX, child.startY, child.x, child.y);
            
            // check si arrivé
            if (isAtStartPosition(&child)) {
                child.hasEscaped = 1;
                printf("\nL'ENFANT A RÉUSSI À S'ÉCHAPPER !\n");
                break;
            }
            
            currentStep = STEP_WOLF_MOVE;
        } else {
            // le loup course le gosse
            moveWolfTowardsChild(&wolf, child.x, child.y);
            
            // est-ce que le loup a chopé le gosse
            if (isWolfNearChild(&wolf, child.x, child.y)) {
                child.isAlive = 0;
                printf("\nLE LOUP A ATTRAPÉ L'ENFANT !\n");
                break;
            }
            
            currentStep = STEP_CHILD_MOVE;
        }
    }
    
    printf("\n=== THE END ===\n");
    printf("Déplacements totaux : %d\n", totalMoves + child.visitedCount);
    printf("Cases explorées : %d\n", child.visitedCount);
    printf("Statut : %s\n", child.isAlive && child.hasEscaped ? "sain et sauf" : "mouru");
    
    //graph Mermaid
    generateMermaidGraph(&child, "cartographie.mmd");
    
    printf("\nAppuyez sur Entrée pour afficher la carte finale...\n");
    getchar();
    displayForest(&child, &wolf);
    
    return 0;
}
