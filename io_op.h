/*
Function name:
Input:
Output:
Function:
Logic:
*/
typedef enum emerg{no,yes} emerg;

/*
Function name:
Input:
Output:
Function:
Logic:
*/
typedef enum state{land,air} state;

/*
Function name:
Input:
Output:
Function:
Logic:
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
Function name:
Input:
Output:
Function:
Logic:
*/
typedef struct message{
	char msg[80];
	int col;
	struct message *next;
}message;
	

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
const char* getfield(char* line, int num)
{
	const char* tok;
	for (tok = strtok(line, ","); tok && *tok ; tok = strtok(NULL, ",\n")){
        	if (!--num)
			return tok;}
	return NULL;
}

/*
Function name: read_from_file
Input: string, file_name
Output: array of pointers to heads of linked lists tk_off and land
Function: reads data from a .csv file of the given name. If no file is found, hopefully handles exception. Then stores the data in two linked lists, tk_off and land
Logic: uses file handling to complete the task
*/
plane *read_from_file(char file_name[],char plane_token){
	//stuffz
	FILE *fptr;
	fptr = fopen(file_name,"r");
	if(fptr == NULL)
		return NULL;
	plane *tmp_p = NULL;
	plane *tmp_plane = NULL;
	plane *head = (plane*)malloc(sizeof(plane));
	head = NULL;
	char line[1024], temp[20];
	while (fgets(line, 1024, fptr)){

		tmp_plane = (plane*)malloc(sizeof(plane));
		char* tmp = strdup(line);
		sprintf(tmp_plane->name,"%s",getfield(tmp,1));
		free(tmp);	

		tmp = strdup(line);
		sprintf(temp,"%s",getfield(tmp,2));
		tmp_plane->air_time = atoi(temp);
		free(tmp);	

		tmp = strdup(line);
		sprintf(temp,"%s",getfield(tmp,3));
		tmp_plane->emergency = atoi(temp);
		free(tmp);	

		tmp = strdup(line);
		sprintf(temp,"%s",getfield(tmp,4));
		tmp_plane->status = atoi(temp);

		tmp = strdup(line);
		sprintf(temp,"%s",getfield(tmp,5));
		tmp_plane->no_of_passengers = atoi(temp);
		free(tmp);

		tmp_plane->next = NULL;
	
		if(tmp_plane->status == air && plane_token == 'l'){
			if(head == NULL){
				head = tmp_plane;
			}else{
				tmp_p = head;
				while(tmp_p->next != NULL)
					tmp_p = tmp_p->next;
				tmp_p->next = tmp_plane;
			}
		}else if(tmp_plane->status == land && plane_token == 't'){
			if(head == NULL){
				head = tmp_plane;
			}else{
				tmp_p = head;
				while(tmp_p->next != NULL)
					tmp_p = tmp_p->next;
				tmp_p->next = tmp_plane;
			}
		}
	}
	tmp_plane->next = NULL;
	fclose(fptr);
	return head;
}

/*
Function name: add_flight
Input: new_flight, type: struct plane, plane pointer head
Output: none
Function: Adds a new flight to the linked list 
Logic: If no node exists, returns head. Else, adds a new node to the list.
*/
void add_flight(plane new_flight, plane *head){
	if(head != NULL){
		plane *new = (plane*)malloc(sizeof(plane));
		strcpy(new->name,new_flight.name);
		new->air_time = new_flight.air_time;
		new->emergency = new_flight.emergency;
		new->status = new_flight.status;
		new->no_of_passengers = new_flight.no_of_passengers;
		new->next = NULL;
		plane *tmp = head;
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/*
Function name: user_input
Input:  none
Output: plane tmp_plane
Function: takes user input about a new plane, returns that object.
Logic: none
*/
plane user_input(){
	plane tmp_plane;
	char tmp_input = 'a';
	printf("ENTER PLANE NAME: ");
	scanf("%s",tmp_plane.name);

	while(!(tmp_input == 'f' || tmp_input == 'F' || tmp_input == 'g' || tmp_input == 'G')){
		printf("FLYING OR ON GROUND?(F/g): ");
		scanf(" %c",&tmp_input);
	}
	if(tmp_input == 'f' || tmp_input == 'F')
		tmp_plane.status = air;
	else	
		tmp_plane.status = land;

	while(!(tmp_input == 'y' || tmp_input == 'Y' || tmp_input == 'n' || tmp_input == 'N')){
		printf("EMERGENCY?(Y/n): ");
		scanf(" %c",&tmp_input);
	}
	if(tmp_input == 'y' || tmp_input == 'Y')
		tmp_plane.emergency = yes;
	else	tmp_plane.emergency = no;

	if(tmp_plane.status == air){
		printf("ENTER AIR TIME: ");
		scanf("%d",&(tmp_plane.air_time));
	}else	tmp_plane.air_time = 0;
	
	printf("ENTER NUMBER OF PASSENGERS:");
	scanf("%d",&(tmp_plane.no_of_passengers));
	return tmp_plane;
}

/*
Function name:
Input:
Output:
Function:
Logic:
*/
plane pop(plane **head_ref){
	plane *head = *head_ref;
	plane popped;
	strcpy(popped.name,head->name);
	popped.status = head->status;
	popped.air_time = head->air_time;
	popped.no_of_passengers = head->no_of_passengers;
	popped.emergency = head->emergency;
	popped.next = head->next;
	(*head_ref) = (*head_ref)->next;
	free(head);
	return popped;
}

/*
Function name:
Input:
Output:
Function:
Logic:
*/
char menu(){
	char ch;
	printf("\na: ADD PLANE\tc: CONTINUE\tx: EMPTY QUEUES AND EXIT\tCHOICE: ");
	scanf(" %c",&ch);
	return ch;
}

/*
Function name: 
Input: 
Output: 
Function: 
Logic: 
*/
void add_msg(message new_msg, message *m_head){
	if(m_head != NULL){
		message *new = (message*)malloc(sizeof(message));
		strcpy(new->msg,new_msg.msg);
		new->col = new_msg.col;
		new->next = NULL;
		message *tmp = m_head;
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}


