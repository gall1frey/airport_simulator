/*
Function name: sortedInsert
Input: plane double pointer pointing to head of linked list, plane pointer of new node to be inserted, char flag of list
Output: none
Function: inserts the new node in the sorted list
Logic: insertion sort
*/
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

/*
Function name: sort_tk_off
Input: plane double pointer pointing to head of linked list tk_off 
Output: none
Function: sorts the linked list tk_off based. Sends any emergency flights to the head.
Logic: retains queue order, except for emergency cases
*/
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

/*
Function name: sort_land
Input: plane pointer head pointing to head of linked list land
Output: plane pointer pointing to new head of linked list land
Function: sorts the linked list land based on the structure member 'air_time'. Also sends any emergency flights to the head.
Logic: uses selection sort to sort through the list
*/
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

/*
Function name:
Input:
Output:
Function:
Logic:
*/
void update_air_time(plane *head){
	plane *iter = head;
	while (iter != NULL){
		iter->air_time++;
		iter = iter->next;
	}
}
