#define SPACE_NUMBER 34

/*
*
*	Structures
*
*/
typedef struct Space {
	
	// Building ID & Name
	int id;
	char name[20];
	
	// Facility Infos
	int is_cafe;
	int is_lounge;
	int is_convenience;
	int is_vendingMac;
	int is_copyMac;
	
} Space;

/*
*
*	Global Variables
*
*/
Space SpaceInfo[SPACE_NUMBER];

/*
*
*	File Functions
*
*/
void loadTXT_SpaceInfo(Space * mySpaceArray);
void print_SpaceInfo(Space * mySpaceArray);
