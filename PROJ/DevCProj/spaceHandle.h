//#ifndef __SPACEHANDLE_H__
//#define __SPACEHANDLE_H__
#define SPACE_NUMBER 18

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
//char * SpaceFileName = "Space_info.txt";
Space SpaceInfo[SPACE_NUMBER];


void loadTXT_SpaceInfo(Space * mySpaceArray);
void print_SpaceInfo(Space * mySpaceArray);


//#endif