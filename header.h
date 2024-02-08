#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>


//arrow keys 
#define up 80
#define down 72
#define left 75
#define right 77

//ANSI color codes   
#define red "\e[1;31m"
#define green "\e[1;32m"
#define yellow "\e[0;33m"
#define  reset "\e[0m"
#define clear "\e[1;1H\e[2J"
#define underlinedYellow "\e[4;33m"
#define gray "\e[1;37m"


typedef struct xoy
{
    int x;
    int y;
}xoy;
typedef struct userInfo
{
    char id[21];
    int password;
    int level;
    int lastPlayStatus;
    struct userInfo *next;
}userInfo;
typedef struct mapInfo
{
    char** map;
    int xLength;
    int yWidth;
    int score;
}mapInfo;


//menu display 
/*
DESCRIPTION: Displays the play menu.
INPUT: None
OUTPUT: None
*/
void playMenu();
/*
DESCRIPTION: Displays the main menu.
INPUT: None
OUTPUT: None
*/
void mainMenu();
/*
DESCRIPTION: Displays the game menu.
INPUT: None
OUTPUT: None
*/
void gameMenu();


//message display 
/*
DESCRIPTION: Displays an error message.
INPUT: Error message string
OUTPUT: None
*/
void error(char*);
/*
DESCRIPTION: Displays a confirmation message.
INPUT: Confirmation message string
OUTPUT: None
*/
void confirmation(char*);
/*
DESCRIPTION: Displays text in the center of the screen.
INPUT: Text to be displayed
OUTPUT: None
*/
void printInTheCenter(char*);
/*
DESCRIPTION: Displays a message for winning the game.
INPUT: None
OUTPUT: None
*/
void printWin();
/*
DESCRIPTION: Displays a message for losing the game.
INPUT: None
OUTPUT: None
*/
void printLose();
void win();
void lose();


//load functions 
/*
DESCRIPTION: Loads user information.
INPUT: None
OUTPUT: Pointer to userInfo as the head of the linked list that was created in this function 
*/
userInfo* loadUsers();
/*
DESCRIPTION: Loads map information of the user's last play  
INPUT: Filename, pointer to xoy for the pacMan, pointer to xoy for the ghost
OUTPUT: mapInfo containing the users last play map
*/
mapInfo loadUserMap1(char[21],xoy*,xoy*);
/*
DESCRIPTION: Loads map information of the user's last play
INPUT: Filename, pointer to xoy for the pacMan, pointer to xoy for the first ghost, pointer to xoy for the second ghost
OUTPUT: mapInfo containing the users last play map
*/
mapInfo loadUserMap2(char[21],xoy*,xoy*,xoy*);
/*
DESCRIPTION: Loads map information based on the map type.
INPUT: Map type
OUTPUT: mapInfo structure
*/
mapInfo loadMap(int);
/*
DESCRIPTION: Reads the type of the map.
INPUT: The user's id 
OUTPUT: Integer representing the map type
*/
int readType(char*);


//store functions 
/*
DESCRIPTION: Stores user information.
INPUT: Pointer to userInfo as the header of the users linked list 
OUTPUT: None
*/
void storeUsers(userInfo*);
/*
DESCRIPTION: Stores map information of the users last play.
INPUT: mapInfo structure, filename, xoy for the pacMan, xoy for the ghost 
OUTPUT: None
*/
void storeUserMap1(mapInfo,char[21],xoy,xoy);
/*
DESCRIPTION: Stores map information of the users last play.
INPUT: mapInfo structure, filename, xoy for the pacMan, xoy for the first ghost, xoy for the second ghost
OUTPUT: None
*/
void storeUserMap2(mapInfo,char[21],xoy,xoy,xoy);
/*
DESCRIPTION: Attaches userInfo to a linked list.
INPUT: userInfo of the current user, pointer to userInfo as the head of the users linked list 
OUTPUT: None
*/
void attachToLinkedList(userInfo,userInfo*);

//free function 
void freeMap(mapInfo);

//authentication
/*
DESCRIPTION: Logs in a user.
INPUT: Pointer to userInfo as the head of the users linkeed list 
OUTPUT: userInfo structure containg current user information
*/
userInfo logIn(userInfo*);
/*
DESCRIPTION: Signs up a new user.
INPUT: Pointer to userInfo as the head of the users linkeed list
OUTPUT: Pointer to userInfo as the new head 
*/
userInfo* signUp(userInfo*);
/*
DESCRIPTION: Deletes a user account.
INPUT: Pointer to userInfo as the head of the users linkeed list
OUTPUT: Pointer to userInfo as the (new) head
*/
userInfo* deleteAccount(userInfo*);


//game functions 
/*
DESCRIPTION: Displays the map.
INPUT: mapInfo structure
OUTPUT: None
*/
void mapDisplay(mapInfo);
/*
DESCRIPTION: Generates a random move.
INPUT: None
OUTPUT: Random move
*/
int ghostMove(mapInfo,xoy);
/*
DESCRIPTION: Manages the game 
INPUT: Pointer to xoy for the pacMan, pointer to xoy for the ghost, pointer to mapInfo of the map, 
pointer to userInfo containg the current user's inoformation, integer (max points there to get)
OUTPUT: Result of the move
*/
int play1(xoy*,xoy*,mapInfo*,userInfo*,int);
/*
DESCRIPTION: Manages the game
INPUT: Pointer to xoy for the pacMan, pointer to xoy for the first ghost, pointer to xoy for the second ghost, 
pointer to mapInfo of the map, pointer to userInfo containg the current user's inoformation, integer (max points there to get)
OUTPUT: Result of the move
*/
int play2(xoy*,xoy*,xoy*,mapInfo*,userInfo*,int);


#endif