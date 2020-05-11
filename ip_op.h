#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
	Enum to simplifying emergency attribute of structure plane
*/
typedef enum emerg{no,yes} emerg;

/*
	Enum to simplifying state attribute of structure plane
*/
typedef enum state{land,air} state;

/*
	Structure name: plane
	Attributes: name (string), air_time (int), emergency (enum), status (enum), no_of_passengers (int)
*/
typedef struct plane{
	char name[10];
	int air_time;
	emerg emergency;
	state status;
	int no_of_passengers;
	struct plane *next;
} plane;

/*
	Structure name: message
	Attributes: message (string), colour (int)
*/
typedef struct message{
	char msg[80];
	int col;
	struct message *next;
}message;
	
/*
	Array of ANSI escape sequences. Used for changing text colour in Windows
*/
#ifdef _WIN32
	char col[4][10] = {"\033[1;31m","\033[1;32m","\033[1;33m","\033[0m"};
//			       red          green       yellow       white
#endif

/*
Function name: getfield
Input: string line, int num
Output: const char pointer
Function: returns the n'th comma separated field from the given line
Logic: uses strtok toachieve the result
*/
const char* getfield(char* line, int num);

/*
Function name: read_from_file
Input: string, file_name
Output: array of pointers to heads of linked lists tk_off and land
Function: reads data from a .csv file of the given name. If no file is found, hopefully handles exception. Then stores the data in two linked lists, tk_off and land
Logic: uses file handling to complete the task
*/
plane *read_from_file(char file_name[],char plane_token);

/*
Function name: add_flight
Input: new_flight, type: struct plane, plane pointer head
Output: none
Function: Adds a new flight to the linked list 
Logic: appending to a linked list
*/
void add_flight(plane new_flight, plane *head);

/*
Function name: user_input
Input:  none
Output: plane tmp_plane
Function: takes user input about a new plane, returns that object.
Logic: none
*/
plane user_input();

/*
Function name: pop
Input: double pointer of struct plane
Output: plane variable
Function: pops the first node of the linked list, returns said node
Logic: pop in linked lists
*/
plane pop(plane **head_ref);
/*
Function name: menu
Input: none
Output: char choice
Function: prints a menu and returns the choice
Logic: none
*/
char menu();

/*
Function name: add_msg
Input: message variable new_msg, pointer pointing to head of linked list
Output: none
Function: appends the input message variable to the end of the linked list
Logic: linked lists
*/
void add_msg(message new_msg, message *m_head);

/*
Function name: sortedInsert
Input: plane double pointer pointing to head of linked list, plane pointer of new node to be inserted, char flag of list
Output: none
Function: inserts the new node in the sorted list
Logic: insertion sort
*/
void sortedInsert(plane** head_ref, plane* new_node, char list_flag);

/*
Function name: sort_tk_off
Input: plane double pointer pointing to head of linked list tk_off 
Output: none
Function: sorts the linked list tk_off based. Sends any emergency flights to the head.
Logic: retains queue order, except for emergency cases
*/
void sort_tk_off(plane **head_ref); 

/*
Function name: sort_land
Input: plane pointer head pointing to head of linked list land
Output: plane pointer pointing to new head of linked list land
Function: sorts the linked list land based on the structure member 'air_time'. Also sends any emergency flights to the head.
Logic: uses selection sort to sort through the list
*/
void sort_land(plane **head_ref);

/*
Function name: update_air_time
Input: plane pointer head
Output: none
Function: updates the air time of planes in air for each iteration.
Logic: none
*/
void update_air_time(plane *head);

/*
Function name: count_planes
Input: plane pointer pointing to head of linked list land
Output: int, number of nodes in linked list 
Function: counts the number of planes in the list
Logic: loops through the list and increments the count variable by one for each node
*/
int count_planes(plane *head);
