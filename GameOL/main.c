/*
 * main file for GameOL, uses functions created in Header File Functions.h for added clarity
 *
 *  Created on: Feb 9, 2018
 *      Author: Gregory
 */

#include <stdio.h>
#include "Functions.h"

int main(int argc, char* argv[])
{

	ReceiveInitValues();

	printf("Do you want to continue? (1 generation y/ end n/ save s/ load L/ multiple generations m): \n");
	fflush( stdout );
	char* EndOfFile = (char*)malloc(sizeof(char));
	scanf(" %c", EndOfFile);

	while(*EndOfFile != 'n'){

		if (*EndOfFile == 'y'){
			GenerationTick();

		}else if(*EndOfFile == 'm'){
			printf("How many Generations? (Enter a number): \n");
			fflush( stdout );
			int* count = (int*)malloc(sizeof(int));
			scanf(" %i", count);

			for (int i = 0; i < *count; i++){
				GenerationTick();
			}
			free(count);
		}else if(*EndOfFile == 's'){
			printf("Enter a file name to save to: \n");
			fflush( stdout );
			char* saveName = (char*)malloc(20 * sizeof(char));
			scanf(" %s", saveName);
			FILE* fp;
			fp = fopen(saveName, "w");

			for (int i = 0; i < SizeX; i++){
				for (int j = 0; j < SizeY; j++){

					if (GameBoard[i][j] == 0){
						fputc('0', fp);
					}else{
						fputc('x', fp);
					}
				}
			}
			fclose(fp);
		}else if(*EndOfFile == 'L'){
			FreeSpace();
			ReceiveInitValues();

		}
		printf("Do you want to continue? (1 generation y/ end n/ save s/ load L/ multiple generations m): \n");
		fflush( stdout );
		scanf(" %c", EndOfFile);

	}

	printf("Thank you for playing!");
	FreeSpace();
	return 0;
}

