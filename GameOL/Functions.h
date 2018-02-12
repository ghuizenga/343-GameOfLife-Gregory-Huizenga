/*
 * Header File used to separate functions from the main file
 *
 *  Created on: Feb 9, 2018
 *      Author: Gregory Huizenga
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdlib.h>
#include <string.h>

/* The current generation number, starts at 0 */
int Generation;

/* Size of the board Horizontally */
int SizeX;

/* Size of the board Vertically */
int SizeY;

/* Array containing the game board, 0: empty | 1: alive */
int **GameBoard;

/* Array containing adjacency data for generation cycling */
int **AdjacencyBoard;

void PrintBoard(){
	printf("\n");
	printf("Generation: %i\n", Generation);

	for (int i = 0; i < SizeX; i++){
		printf("\n");

		for (int j = 0; j < SizeY; j++){
			printf("%i", GameBoard[i][j]);
		}

	}
	printf("\n");
}

/**
 * Creates the initial state of the board
 * @param sizex the horizontal size of the board
 * @param sizey the vertical size of the board
 * @param file the name of the input file to pre-generate from
 */
void InitializeBoard(int* sizex, int* sizey, char* file){
	SizeX = *sizex;
	SizeY = *sizey;
	Generation = 0;

	if (SizeX < 5){
		SizeX = 5;
	}

	if (SizeY < 5){
		SizeY = 5;
	}

	// inspired by https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
	// creates an array of pointers to get a 2-d array.
	GameBoard = (int **)malloc( SizeX * sizeof(int *));
	for (int i=0; i<SizeX; i++){
		GameBoard[i] = (int *)malloc( SizeY * sizeof(int));
	}

	if (strlen(file) == 0){
		// generates a blinker as default if no file name is given
		for (int i=0; i<SizeX; i++){
				for (int j=0; j<SizeY; j++){
					GameBoard[i][j] = 0;
				}
			}

		for (int i=0; i<3; i++){
			GameBoard[SizeY/2][SizeX/2 -1 + i] = 1;
		}
	}else{
		//Inspiration source from https://www.tutorialspoint.com/cprogramming/c_file_io.htm
		FILE *fp = fopen(file, "r");
		char* buffer = (char*)malloc(SizeX * SizeY * sizeof(char));
		fgets(buffer, SizeX*SizeY, (FILE*)fp);
		int k = 0;

		//fills game board with values from the buffer
		for (int i = 0; i < SizeX; i++){
			for (int j = 0; j < SizeY; j++){

				if (buffer[k] == 'x'){
					GameBoard[i][j] = 1;
				}else{
					GameBoard[i][j] = 0;
				}
				k++;

			}
		}
		free(buffer);
		fclose(fp);

	}

	AdjacencyBoard = (int **)malloc( SizeX * sizeof(int *));
		for (int i=0; i<SizeX; i++){
			AdjacencyBoard[i] = (int *)malloc( SizeY * sizeof(int));
		}

		// initializes the Adjacency board's values
	for (int i=0; i<SizeX; i++){
		for (int j=0; j<SizeY; j++){
			AdjacencyBoard[i][j] = 0;
		}
	}

	PrintBoard();
}

/**
 * Asks user for input and uses it to create the board
 */
void ReceiveInitValues(){
	printf("How wide should the board be?(minimum 5): \n");
	fflush( stdout );
	int* sizex = (int*)malloc(sizeof(int));
	scanf("%i", sizex);

	printf("How tall should the board be?(minimum 5): \n");
	fflush( stdout );
	int* sizey = (int*)malloc(sizeof(int));
	scanf("%i", sizey);

	printf("Enter the name of the loading file: \n");
	fflush( stdout );
	char* filename = (char*)malloc(sizeof(char)*30);
	scanf("%s", filename);

	InitializeBoard(sizex, sizey, filename);
	free(sizex);
	free(sizey);
	free(filename);
}

/**
 * Fills the Adjacency board for future calculations
 */
void AdjacencyGen(){
	for (int i = 0; i < SizeX; i++){
		for (int j = 0; j < SizeY; j++){

			// executes if there is a live cell at point (i,j).
			if (GameBoard[i][j] == 1){

				//increases adjacency count of all valid neighboring cells.
				for (int x = i-1; x < i+2; x++){
					for (int y = j-1; y < j+2; y++){
						if (x < 0 || x >= SizeX || y < 0 || y >= SizeY
							|| (x == i && y == j)){
							//do nothing, cell is invalid
						}else{
							AdjacencyBoard[x][y]+= 1;
						}
					}
				}

			}

		}
	}
}

/**
 * Empties the Adjacency board so that it can be reused for the
 * next generation
 */
void AdjacencyEmpty(){

	for (int i = 0; i < SizeX; i++){
		for (int j = 0; j < SizeY; j++){
			AdjacencyBoard[i][j] = 0;
		}
	}
}

/**
 * updates the board for a new generation and prints it out
 */
void GenerationTick(){
	AdjacencyGen();

	for (int i = 0; i < SizeX; i++){
		for (int j = 0; j < SizeY; j++){

			if (GameBoard[i][j] == 1){
				if (AdjacencyBoard[i][j] < 2 || AdjacencyBoard[i][j] > 3){
					GameBoard[i][j] = 0;
				}
			}else{
				if (AdjacencyBoard[i][j] == 3){
					GameBoard[i][j] = 1;
				}
			}
		}
	}

	Generation++;
	AdjacencyEmpty();
	PrintBoard();
}

/**
 * frees both boards' memory locations
 */
void FreeSpace(){
	for (int i=0; i<SizeX; i++){
			free(GameBoard[i]);
		}

	for (int i=0; i<SizeX; i++){
			free(AdjacencyBoard[i]);
		}
	free(GameBoard);
	free(AdjacencyBoard);
}




#endif /* FUNCTIONS_H_ */
