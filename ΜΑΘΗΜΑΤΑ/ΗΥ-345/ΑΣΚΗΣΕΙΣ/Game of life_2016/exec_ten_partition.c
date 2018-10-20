#include "game_of_life.h"

void *exec_hundredth(void *arguments)
{
	int i=0,j=0,sum=0;
	struct arg_struct *args = (struct arg_struct *)arguments;



	for ( i = args->x; i < args->x+10; i++) {
		for ( j = args->y; j < args->y+10; j++) {

			// sum is the number of neighbours
			if(i == 0 ){
				if( j == 0 ){
					sum = (lifeTable[i][j+1]+lifeTable[i+1][j+1]+lifeTable[i+1][j]);
				}else if ( j == 99){
					sum = (lifeTable[i][j-1]+lifeTable[i+1][j-1]+lifeTable[i+1][j]);
				}else{
					sum = (lifeTable[i][j+1]+lifeTable[i][j-1]+lifeTable[i+1][j]+
						lifeTable[i+1][j-1]+lifeTable[i+1][j+1]);
				}
			}else if( i == 99 ){
				if( j == 0 ){
					sum = (lifeTable[i-1][j]+lifeTable[i-1][j+1]+lifeTable[i][j+1]);
				}else if ( j == 99){
					sum = (lifeTable[i][j-1]+lifeTable[i-1][j-1]+lifeTable[i-1][j]);
				}else{
					sum = (lifeTable[i][j+1]+lifeTable[i][j-1]+lifeTable[i-1][j-1]+
						lifeTable[i-1][j]+lifeTable[i-1][j+1]);
				}
			}else if( j == 0 ){
				sum = (lifeTable[i-1][j]+lifeTable[i+1][j]+lifeTable[i][j+1]+
					lifeTable[i+1][j+1]+lifeTable[i-1][j+1]);
			}else if( j == 99 ){
				sum = (lifeTable[i-1][j]+lifeTable[i+1][j]+lifeTable[i][j-1]+
					lifeTable[i+1][j-1]+lifeTable[i-1][j-1]);
			}else{
				sum = (lifeTable[i-1][j]+lifeTable[i+1][j]+lifeTable[i][j-1]+
					lifeTable[i+1][j-1]+lifeTable[i-1][j-1]+lifeTable[i][j+1]+
					lifeTable[i+1][j+1]+lifeTable[i-1][j+1]);
			}

			// changes the lifeTable_fake
			if (lifeTable[i][j] == 1) {
				if ( sum < 2 || sum > 3) {
					lifeTable_fake[i][j] = 0;
				}
			}else if (lifeTable[i][j] == 0) {
				if (sum == 3) {
					lifeTable_fake[i][j] = 1;
				}
			}

		}
	}


	pthread_exit(0);
}

/*
if (lifeTable[i][j] == 0) {
	printf("(%d, %d) => %d+%d+%d+%d+%d+%d+%d+%d = %d\n",i,j,
	lifeTable[i-1][j],lifeTable[i+1][j],lifeTable[i][j-1],
		lifeTable[i+1][j-1],lifeTable[i-1][j-1],lifeTable[i][j+1],
		lifeTable[i+1][j+1],lifeTable[i-1][j+1],sum );
}
*/
