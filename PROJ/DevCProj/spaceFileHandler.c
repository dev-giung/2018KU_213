#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "spaceHandle.h"

/*
*
*	File Name
*
*/
char * SpaceFileName = "Space_info.txt";

/*
*
*	File Functions
*
*/
void loadTXT_SpaceInfo(Space * mySpaceArray) {

	FILE * mySpaceFile = NULL;
	int index = 0;

	if ( (mySpaceFile = fopen(SpaceFileName, "r")) == NULL ) {
		printf("Error : Cannot find the file <%s>", SpaceFileName);
		return;
	}

	for ( index = 0; index < SPACE_NUMBER; index++ ) {
		fscanf(mySpaceFile, "%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
			&mySpaceArray[index].id, &mySpaceArray[index].name, &mySpaceArray[index].is_cafe,
			&mySpaceArray[index].is_lounge, &mySpaceArray[index].is_convenience,
			&mySpaceArray[index].is_vendingMac, &mySpaceArray[index].is_copyMac
		);
	}
	
	fclose(mySpaceFile);
	
}

/*
*
*	Temporary Functions
*
*/
void print_SpaceInfo(Space * mySpaceArray) {
	
	int index = 0;
	
	for ( index = 0; index < SPACE_NUMBER; index++ ) {
		printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
			mySpaceArray[index].id, &mySpaceArray[index].name, mySpaceArray[index].is_cafe,
			mySpaceArray[index].is_lounge, mySpaceArray[index].is_convenience,
			mySpaceArray[index].is_vendingMac, mySpaceArray[index].is_copyMac
		);
	}
	
}
