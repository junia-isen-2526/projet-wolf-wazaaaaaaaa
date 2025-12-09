#include "child.h"

#include <time.h>

int isGameOver(const GameStep step, Child child, const Wolf *wolf) {
	// TODO
	return step == STEP_WOLF_MOVE;
}

void moveChildStep(const Child *child) {
	// TODO
}

void beginningPos(Child *child) {
	//Child spawns on a border of the forest
	//Randomly look for a pos
	char forest[FOREST_WIDTH][FOREST_HEIGHT];
	const int forestCount = readLines("../ressources/foret1.txt", forest);

	//srand(time(NULL));

	int randBegin = rand() % 1;
	printf("%d", randBegin);
	int analysisDirection = rand() % 2;

	switch (randBegin) {
		//pt départ tableau: x:0 ; y:0
		case 0:
			child->x = 0;
			child->y = 0;
			if (analysisDirection == 0) {
				//analysis in x
				for (child->x = 0; child->x < FOREST_WIDTH; child->x++) {
					//Est-ce que arbre ou pas
					//Si oui stopper analyse et définir point de départ
					if (forest[child->x][child->y] == ' ') {
						break;
					}
				}
			}
			if (analysisDirection == 1) {
				//analysis in y
				for (child->y = 0; child->y < FOREST_HEIGHT; child->y++) {
					//Est-ce que arbre ou pas
					//Si oui stopper analyse et définir point de départ
					if (forest[child->x][child->y] == ' ') {
						break;
					}
				}
			}

			break;

			//pt départ x:40 ; y:80
		case 1:
			child->x = FOREST_WIDTH;
			child->y = FOREST_HEIGHT;

			if (analysisDirection == 0) {
				//analysis in x
				for (child->x = FOREST_WIDTH - 1; child->x > 0; child->x--) {
					//Est-ce que arbre ou pas
					//Si oui stopper analyse et définir point de départ
					if (forest[child->x][child->y] == ' ') {
						break;
					}
				}
			}
			if (analysisDirection == 1) {
				//analysis in y
				for (child->y = FOREST_HEIGHT - 1; child->y > 0; child->y--) {
					//Est-ce que arbre ou pas
					//Si oui stopper analyse et définir point de départ
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
				//analysis in x
				for (child->x = 0; child->x < FOREST_WIDTH; child->x++) {
					//Est-ce que arbre ou pas
					//Si oui stopper analyse et définir point de départ
					if (forest[child->x][child->y] == ' ') {
						break;
					}
				}
			}
			if (analysisDirection == 1) {
				//analysis in y
				for (child->y = 0; child->y < FOREST_HEIGHT; child->y++) {
					//Est-ce que arbre ou pas
					//Si oui stopper analyse et définir point de départ
					if (forest[child->x][child->y] == ' ') {
						break;
					}
				}
			}

			break;
	}
}
