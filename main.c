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
                printf("E"); // Enfant
            } else if (wolf->isOut && wolf->x == x && wolf->y == y) {
                printf("L"); // Loup
            } else if (child->startX == x && child->startY == y) {
                printf("D"); // Départ
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
    
    // Initialisation
    Child child;
    Wolf wolf;
    
    char comptine[MAX_COMPTINE_LINES][256];
    char vetements[MAX_CLOTHES_LINES][256];
    
    // Charger les fichiers
    int comptineLines = readLinesText("../ressources/comptine.txt", comptine, MAX_COMPTINE_LINES);
    int vetementLines = readLinesText("../ressources/vetements.txt", vetements, MAX_CLOTHES_LINES);
    
    if (comptineLines == 0 || vetementLines == 0) {
        printf("Erreur : fichiers manquants\n");
        return 1;
    }
    
    // Position de départ de l'enfant
    beginningPos(&child);
    initWolf(&wolf);
    
    printf("PROMENONS-NOUS DANS LES BOIS\n\n");
    printf("L'enfant commence à la position (%d, %d)\n\n", child.x, child.y);
    
    int comptineIndex = 0;
    int totalMoves = 0;
    GameStep currentStep = STEP_CHILD_MOVE;
    
    // Phase 1 : Exploration avant que le loup sorte
    while (!wolf.isOut) {
        // L'enfant chante une phrase de la comptine
        printf("%s\n", comptine[comptineIndex % comptineLines]);
        comptineIndex++;
        
        // L'enfant se déplace
        moveChildStep(&child);
        totalMoves++;
        printf("L'enfant se déplace vers (%d, %d) - Positions visitées : %d\n", 
               child.x, child.y, child.visitedCount);
        
        // Le loup enfile un vêtement
        wolf.clothesCount++;
        if (wolf.clothesCount < wolf.clothesToWear) {
            int clotheIndex = rand() % vetementLines;
            printf("Loup : %s (%d/%d)\n\n", 
                   vetements[clotheIndex], wolf.clothesCount, wolf.clothesToWear);
        } else {
            revealWolf(&wolf);
        }
        
        // Pause pour la lisibilité (optionnel)
        // getchar();
    }
    
    // Phase 2 : Fuite vers le point de départ
    printf("\n💨 L'ENFANT DOIT RETOURNER AU POINT DE DÉPART ! 💨\n\n");
    
    while (!isGameOver(currentStep, child, &wolf)) {
        if (currentStep == STEP_CHILD_MOVE) {
            // L'enfant fuit vers son point de départ
            moveTowardsStart(&child);
            printf("L'enfant fuit vers le départ (%d, %d) - Position actuelle : (%d, %d)\n", 
                   child.startX, child.startY, child.x, child.y);
            
            // Vérifier s'il est arrivé
            if (isAtStartPosition(&child)) {
                child.hasEscaped = 1;
                printf("\nL'ENFANT A RÉUSSI À S'ÉCHAPPER !\n");
                break;
            }
            
            currentStep = STEP_WOLF_MOVE;
        } else {
            // Le loup poursuit l'enfant
            moveWolfTowardsChild(&wolf, child.x, child.y);
            
            // Vérifier si le loup attrape l'enfant
            if (isWolfNearChild(&wolf, child.x, child.y)) {
                child.isAlive = 0;
                printf("\nLE LOUP A ATTRAPÉ L'ENFANT !\n");
                break;
            }
            
            currentStep = STEP_CHILD_MOVE;
        }
        
        // Afficher la carte (optionnel, peut ralentir)
        // displayForest(&child, &wolf);
        // getchar();
    }
    
    // Résultats finaux
    printf("\n=== RÉSULTATS ===\n");
    printf("Déplacements totaux : %d\n", totalMoves + child.visitedCount);
    printf("Cases explorées : %d\n", child.visitedCount);
    printf("Statut : %s\n", child.isAlive && child.hasEscaped ? "SAUVÉ ✅" : "MANGÉ ❌");
    
    // Générer le graphe Mermaid
    generateMermaidGraph(&child, "cartographie.mmd");
    
    printf("\nAppuyez sur Entrée pour afficher la carte finale...\n");
    getchar();
    displayForest(&child, &wolf);
    
    return 0;
}
