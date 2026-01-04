#include <time.h>
#include <stdlib.h>
#include "wolf.h"
#include "child.h"
#include "mermaid.c"

int main() {
	srand(time(NULL));

	char rhyme[FOREST_WIDTH][FOREST_HEIGHT];
	const int rhymeCount = readLines("../ressources/comptine.txt", rhyme);

	char clothes[MAXClothes][FOREST_HEIGHT];
	const int clothesCount = readLines("../ressources/vetements.txt", clothes);

	Wolf wolf = {-1, -1, 0};
	Child child;

	GameStep step = STEP_COMPTINE;

	while (!isGameOver(step, child, &wolf)) {
		switch (step) {
			case STEP_COMPTINE: if (playComptineStep(rhyme, rhymeCount)) step = STEP_DRESSING;
				break;
			case STEP_DRESSING:
				if (wolfDressingStep(&wolf, clothes, clothesCount)) {
					step = STEP_WOLF_MOVE;
				} else {
					step = STEP_COMPTINE;
				}
				break;
			case STEP_WOLF_MOVE: moveWolfStep(&wolf);
				break;
		}
		moveChildStep(&child);
	}

	    // Create some vertices
    Vertex v1 = {1, 1, 3};
    Vertex v2 = {2, 2, 3};
    Vertex v3 = {3, 2, 4};
    Vertex v4 = {4, 3, 4};
    Vertex v5 = {5, 4, 4};
    Vertex v6 = {6, 2, 2};
    Vertex v7 = {7, 3, 2};
    Vertex v8 = {8, 4, 2};
    Vertex v9 = {9, 4, 3};

    // Create edges
    Edge e1_2 = {&v1, &v2};// TODO
    Edge e2_3 = {&v2, &v3};
    Edge e3_4 = {&v3, &v4};
    Edge e4_5 = {&v4, &v5};
    Edge e2_6 = {&v2, &v6};
    Edge e6_7 = {&v6, &v7};
    Edge e7_8 = {&v7, &v8};
    Edge e5_9 = {&v5, &v9};
    Edge e8_9 = {&v8, &v9};

    // Create nodes for the graph (simplified for this example)
    // In a real application, you might have a more robust way to build this list
    Node n1_2 = {&e1_2, NULL};
    Node n2_3 = {&e2_3, NULL};
    Node n3_4 = {&e3_4, NULL};
    Node n4_5 = {&e4_5, NULL};
    Node n2_6 = {&e2_6, NULL};
    Node n6_7 = {&e6_7, NULL};
    Node n7_8 = {&e7_8, NULL};
    Node n5_9 = {&e5_9, NULL};
    Node n8_9 = {&e8_9, NULL};

    // Link the nodes to form the list (representing the graph)
    n1_2.nextNode = &n2_3;
    n2_3.nextNode = &n3_4;
    n3_4.nextNode = &n4_5;
    n4_5.nextNode = &n2_6; // Note: You need to decide the order for output
    n2_6.nextNode = &n6_7;
    n6_7.nextNode = &n7_8;
    n7_8.nextNode = &n5_9;
    n5_9.nextNode = &n8_9;
    n8_9.nextNode = NULL;

    // Create the graph
    Graph myGraph = {&n1_2};

    // Create the Mermaid file
    if (mermaiding(&myGraph) == 0) {
        printf("Mermaid graph file 'graph.mmd' created successfully.\n");
    } else {
        printf("Failed to create Mermaid graph file.\n");
    }

    return 0;

	return 0;
}
