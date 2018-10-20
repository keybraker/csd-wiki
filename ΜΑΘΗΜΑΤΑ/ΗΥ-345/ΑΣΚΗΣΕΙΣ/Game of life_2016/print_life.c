#include "game_of_life.h"

void print_life(){

	int i,j;
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 100; j++) {
			printf("%d ", lifeTable_fake[i][j]);
			lifeTable[i][j] = lifeTable_fake[i][j];
		}
		printf("\n");
	}
	system("clear");
	
}
