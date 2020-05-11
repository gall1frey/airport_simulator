#include "ip_op.h"

const char* getfield(char* line, int num)
{
	const char* tok;
	for (tok = strtok(line, ","); tok && *tok ; tok = strtok(NULL, ",\n")){
        	if (!--num)
			return tok;}
	return NULL;
}

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

char menu(){
	char ch;
	printf("\na: ADD PLANE\tc: CONTINUE\tx: EMPTY QUEUES AND EXIT\tCHOICE: ");
	scanf(" %c",&ch);
	return ch;
}

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

void sortedInsert(plane** head_ref, plane* new_node, char list_flag){ 
	if(list_flag == 't'){
		plane* current; 
		if (*head_ref == NULL || (*head_ref)->emergency <= new_node->emergency){ 
			new_node->next = *head_ref;
			*head_ref = new_node; 
		}else{ 
			current = *head_ref; 
			while (current->next!=NULL && current->next->emergency > new_node->emergency) { 
				current = current->next; 
			} 
			new_node->next = current->next; 
			current->next = new_node; 
		} 
	}else{
		plane* current; 
		if (*head_ref == NULL || (*head_ref)->air_time >= new_node->air_time){ 
			new_node->next = *head_ref;
			*head_ref = new_node; 
		}else{ 
			current = *head_ref; 
			while (current->next!=NULL && current->next->air_time < new_node->air_time) { 
				current = current->next; 
			} 
			new_node->next = current->next; 
			current->next = new_node; 
		} 
	
	}
}

void sort_tk_off(plane **head_ref){
	//stuffz
	plane *sorted = NULL; 
	plane *current = *head_ref; 
	while (current != NULL){ 
		plane *next = current->next; 
		sortedInsert(&sorted, current, 't'); 
		current = next; 
	} 
	*head_ref = sorted; 
}

void sort_land(plane **head_ref){
	//stuffz
	plane *sorted = NULL; 
	plane *current = *head_ref; 
	while (current != NULL){ 
		plane *next = current->next; 
		sortedInsert(&sorted, current, 'h'); 
		current = next; 
	}
	*head_ref = sorted;
	sort_tk_off(head_ref);
}

void update_air_time(plane *head){
	plane *iter = head;
	while (iter != NULL){
		iter->air_time++;
		iter = iter->next;
	}
}

int count_planes(plane *head){
	//stuffz
	plane *iter_var = head;
	int count = 0;
	while(iter_var != NULL){
		count++;
		iter_var = iter_var->next;
	}
	return count;
}

