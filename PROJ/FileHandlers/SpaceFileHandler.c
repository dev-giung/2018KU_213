/*
	SpaceFileHandler.c contains functions for file loading.
	- Space_info.txt
*/

#include <stdio.h>
#include <malloc.h>

/*
	Constants
*/
#define SPACE_NUMBER 18

/*
	Structures
*/
typedef struct Space {
	
	// Building ID & Name
	int id;
	char name[20];

	// Facility Info
	int is_cafe;
	int is_lounge;
	int is_convenience;
	int is_vendingMac;
	int is_copyMac;
	 
} Space;

/*
	Global Variables
*/
char * SpaceFileName = "Space_info.txt";
Space SpaceInfo[SPACE_NUMBER];

/*
	File Handler Functions
*/
void loadTXT_SpaceInfo(Space * mySpaceArray) {
	
	FILE * mySpaceFile = NULL;
	int index = 0;
	
	if( (mySpaceFile = fopen(SpaceFileName, "r")) == NULL ) {
		
		printf("Error : Cannot find the file <%s>", SpaceFileName);
		return;
	}
	
	for( index = 0; index < SPACE_NUMBER; index++ ) {
		
		fscanf( mySpaceFile, "%d\t%s\t%d\t%d\t%d\t%d\t%d", 
			&mySpaceArray[index].id, &mySpaceArray[index].name, &mySpaceArray[index].is_cafe, 
			&mySpaceArray[index].is_lounge, &mySpaceArray[index].is_convenience, 
			&mySpaceArray[index].is_vendingMac, &mySpaceArray[index].is_copyMac
		);
	}
	
	fclose( mySpaceFile );
}

/*
	Temporary Functions
*/
void print_SpaceInfo(Space * mySpaceArray) {
	
	int index = 0;
	
	for( index = 0; index < SPACE_NUMBER; index++ ) {
		
		printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n", 
			mySpaceArray[index].id, &mySpaceArray[index].name, mySpaceArray[index].is_cafe, 
			mySpaceArray[index].is_lounge, mySpaceArray[index].is_convenience, 
			mySpaceArray[index].is_vendingMac, mySpaceArray[index].is_copyMac
		);
	}
}

/*
	Main Function
*/
int main() {
	
	loadTXT_SpaceInfo(SpaceInfo);
	print_SpaceInfo(SpaceInfo);
	
	return 0;
}
