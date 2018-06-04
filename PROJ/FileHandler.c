/*
	FileHandler.c contains functions for file saving & loading.
	- Space_info.txt
*/

#include <stdio.h>
#include <malloc.h>

#define SPACE_NUMBER 16
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
void loadTXT_SpaceInfo(Space * mySpaceArray, int N) {
	
	FILE * mySpaceFile = NULL;
	int index = 0;
	
	if( (mySpaceFile = fopen(SpaceFileName, "r")) == NULL ) {
		
		printf("Error : Cannot find the file");
		return 0;
	}
	
	for( index = 0; index < N; index++ ) {
		
		fscanf( mySpaceFile, "%d\t%s\t%d\t%d\t%d\t%d\t%d", 
			&mySpaceArray[index].id, &mySpaceArray[index].name, &mySpaceArray[index].is_cafe, 
			&mySpaceArray[index].is_lounge, &mySpaceArray[index].is_convenience, 
			&mySpaceArray[index].is_vendingMac, &mySpaceArray[index].is_copyMac
		);
	}
}

void print_SpaceInfo(Space * mySpaceArray, int N) {
	
	int index = 0;
	
	for( index = 0; index < N; index++ ) {
		
		printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n", 
			mySpaceArray[index].id, &mySpaceArray[index].name, mySpaceArray[index].is_cafe, 
			mySpaceArray[index].is_lounge, mySpaceArray[index].is_convenience, 
			mySpaceArray[index].is_vendingMac, mySpaceArray[index].is_copyMac
		);
	}
}

int main() {
	
	loadTXT_SpaceInfo(SpaceInfo, SPACE_NUMBER);
	
	print_SpaceInfo(SpaceInfo, SPACE_NUMBER);
	
	return 0;
}
