/*
	This arbitrary constant decides how much air time (iterations) is too much
*/
#define arbitrary_air_time_const 9

/*
	This arbitrary constant decides how many planes in air at a time are too many
*/
#define arbitrary_planes_in_air_const 6

/*
Function name: decide
Input: take_off_plane and landing_plane (plane type), int planes_in_air (no. of planes currently in air)
Output: character, 't' or 'l'
Function: chooses which plane gets to use the runway
Logic: makes decision based on whether either of the planes have an emergency situation, the number of planes in air, time of plane in air, and number of passengers
*/
char decide(plane take_off_plane, plane landing_plane, int planes_in_air);

/*
Function name: random_decider
Input: float rate
Output: integer 
Function: randomly decides whether a plane could successfully land/takeoff
			(simulates natural unforeseen difficulties in landing/takeoff, like wind speed)
Logic: Uses the rate variable to add weights to the random number generator, this is better
		choosing a random number between 0 and 1 as that would give a 50% chance, which isn't 
		realistic.
*/
int random_decider(float rate);

/*
Function name: count_msg
Input: message pointer head
Output: integer
Function: Counts the number of messages 
Logic: Linked lists
*/
int count_msg(message *head);
