#include "game_of_life.h"

int main()
{
	int args[2] = {0, 0}, k = 0, check = 0, input = 0, file_check = 0;
	char *cmd = (char *)malloc(sizeof(char));

	printf("\n");
	printf("|---------------------------------------------------------|\n");
	printf("|	ID	|		FILENAME		  |\n");
	printf("|---------------------------------------------------------|\n");
	printf("|	1	|	oscillator_beacon.txt             |\n");
	printf("|	2	|	oscillator_blinker.txt            |\n");
	printf("|	3	|	oscillator_Pentadecathlon.txt     |\n");
	printf("|	4	|	oscillator_pulsar.txt             |\n");
	printf("|	5	|	oscillator_toad.txt               |\n");
	printf("|	6	|	spaceships_glider.txt             |\n");
	printf("|	7	|	spaceships_lwss.txt               |\n");
	printf("|	8	|	still_behive.txt                  |\n");
	printf("|	9	|	still_block.txt                   |\n");
	printf("|	10	|	still_boat.txt                    |\n");
	printf("|	11	|	still_loaf.txt                    |\n");
	printf("|---------------------------------------------------------|\n");

	printf("\n Give me the number of the file you\n");
	printf(" want to execute or enter custom file : ");
	scanf("%d", &input);

	if (input == 1)
	{
		file_check = file_reader("oscillator_beacon.txt");
	}
	else if (input == 2)
	{
		file_check = file_reader("oscillator_blinker.txt");
	}
	else if (input == 3)
	{
		file_check = file_reader("oscillator_Pentadecathlon.txt");
	}
	else if (input == 4)
	{
		file_check = file_reader("oscillator_pulsar.txt");
	}
	else if (input == 5)
	{
		file_check = file_reader("oscillator_toad.txt");
	}
	else if (input == 6)
	{
		file_check = file_reader("spaceships_glider.txt");
	}
	else if (input == 7)
	{
		file_check = file_reader("spaceships_lwss.txt");
	}
	else if (input == 8)
	{
		file_check = file_reader("still_behive.txt");
	}
	else if (input == 9)
	{
		file_check = file_reader("still_block.txt");
	}
	else if (input == 10)
	{
		file_check = file_reader("still_boat.txt");
	}
	else if (input == 11)
	{
		file_check = file_reader("still_loaf.txt");
	}
	else if (input == 0)
	{
		printf(" Enter the custom file you want to execute : ");
		scanf("%s", cmd);
		file_check = file_reader(cmd);
	}
	else
	{
		printf(" invalid input given, program will end\n");
		return 0;
	}

	if (file_check)
	{
		return 0;
	}

	// first time life_print
	print_life();

	// creating all one hundred necessary threads to run simultaneously
	pthread_t executioner[100];

	// infinite looper
	while (1)
	{

		// 100 loops for every thread
		k = 0;
		while (k < 100)
		{

			// giving every one of the threads a hundredth of the work to execute
			check = pthread_create(&(executioner[k]), NULL, exec_hundredth, (void *)&args);
			if (check == 1)
			{
				fprintf(stderr, "Error creating thread\n");
				return 1;
			}
			// joining every threat to mother exec
			pthread_join(executioner[k], NULL);
			// changing x,y for next thread's starting point
			if (args[1] == 90)
			{
				args[0] = args[0] + 10;
				args[1] = 0;
			}
			else
			{
				args[1] = args[1] + 10;
			}
			k++;
		}
		// initializing args for next thread
		args[0] = 0;
		args[1] = 0;
		// printing every life stage
		print_life();
	}

	return 0;
}
