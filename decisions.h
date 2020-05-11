#define arbitrary_air_time_const 9
#define arbitrary_planes_in_air_const 6


/*
Function name: count_planes
Input: plane pointer pointing to head of linked list land
Output: int, number of nodes in linked list land
Function: counts the number of planes in air
Logic: loops through the list and incremwnts the count variable by one for each node
*/
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

/*
Function name: decide
Input: take_off_plane and landing_plane (plane type), int planes_in_air (no. of planes currently in air)
Output: character, 't' or 'l'
Function: chooses which plane gets to use the runway
Logic: makes decision based on whether either of the planes have an emergency situation, the number of planes in air, time of plane in air, and number of passengers
*/
char decide(plane take_off_plane, plane landing_plane, int planes_in_air){
	if(take_off_plane.emergency ^ landing_plane.emergency){
		if(take_off_plane.emergency)
			return 't';
		else
			return 'l';
	}else if(take_off_plane.emergency && landing_plane.emergency){
		if(take_off_plane.no_of_passengers > landing_plane.no_of_passengers)
			return 't';
		else
			return 'l';
	}else if(landing_plane.air_time > arbitrary_air_time_const || planes_in_air > arbitrary_planes_in_air_const){
		return 'l';
	}else if(take_off_plane.no_of_passengers > landing_plane.no_of_passengers){
		return 't';
	}else	return 'l';
}

/*
Function name:
Input:
Output:
Function:
Logic:
*/
int random_decider(float rate){
	int random_no = rand();
	if(random_no % (int) (1/rate))
		return 1;
	return 0;
}

/*
Function name:
Input:
Output:
Function:
Logic:
*/
int count_msg(message *head){
	//stuffz
	message *iter_var = head;
	int count = 0;
	while(iter_var != NULL){
		count++;
		iter_var = iter_var->next;
	}
	return count;
}
