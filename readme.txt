AIRPORT SIMULATOR

Airport simulator has the following files:
	1. main.c
	2. ip_op.h
	3. ip_op.c
	4. beautify.h
	5. beautify.c
	6. decisions.h
	7. decisions.c
	8. sort.h
	9. sort.c

main.c:
	The main function is in this file.

ip_op.h/ip_op.c:
	Handles input and output - related functions.

beautify.h/beautify.c:
	Handles the formatting, text colour, etc.

decisions.h/decisions.c:
	Contains all the decision-making functions, as well as functions relating to counting the number of nodes in a linked list.

sort.h/sort.c:
	Contains sorting functions.

Rules for deciding which plane gets to use the runway(s):
	1. Sort both the queues (tk_off and land), based on cartain parameters.
		Parameters are:
			tk_off: The order of the queue doesn't change, unless there is a plane with an emergency.
					Then that plane gets sent to the top.
			Land:	The order of the queue first depends on air_time (number of iterations the plane has spent in air).
					After this, and planes with an emergency get pushed to the front.
	2. The first planes from both queues are compared. The parameters for comparison are as follows:
		1. If either of the planes have an emergency, that plane gets a priority.
		2. If both planes have an emergency, the plane with most passengers gets a priority.
		3. If none of the planes have an emergency:
			a. If the plane in air has an air_time of more than an arbitrary threshold value, it gets a priority.
			b. If the number of planes in the air is more than an arbitrary threshold value, the plane in air is prioritized.
			c. If the above two conditions are false, and the number of passengers in the ground plane are more than the number of passengers in the air,
				The ground plane comes first.
			d. If not, finally, the plane in the air gets the runway.

Use:
	Compilation:
		The makefile has to be run in order to get a .exe file.
		The file generated will be named airport.exe (airport on linux machines).
		
	Requirements:
		A .csv file with the appropriate data is required to run the program.
		In this case, it is named "data.csv", and is generated using a python script.
		It contains details of 30 aeroplanes.
	
	Execution:
		The program will ask the user for the number of runways to use in the simulation. The input must be an integer.
		Next, the user will be prompted for the probability of failure (probability that a plane cannot complete it's required task). It must be a floating point number between 
			0 and 1.
		Now, the user will be prompted to enter the name of the csv file with the data of the planes in it. The user can enter "data.csv", or the name of any other
			.csv file that contains the appropriate data. The program will keep iterating this step till a proper file name is provided.
		Once this is done, the simulation is ready to run.
		Two tables, corresponding to planes on land and in air can be seen. The tables show first 20 planes in each category.
		Below this, the user is prompted to select an appropriate choice.
			The choice is to add a new plane, or to just continue the simulation.
			The user can also input 'x', which will disable any inputs for the rest of the simulation of the program.
			If the user chooses to add another plane, they'll be prompted to a screen which asks them to key in information about the plane they wish to add.
		After a few iterations, the user can see a string of red/yellow/green messages below the table. The red ones signify failure, and the green ones signify success.
		The most recent 8 messages can be seen. However, the code can be altered to show any number of messages.
		At the end of the run, the code stops after giving an appropriate message.

Bugs:
	> Cannot yet figure out why the refreshing of screens is not very smooth in windows.
		This can be made smoother in Linux using curses, but I'm unable to find any alternative for that in windows.
	> Some inputs are not validated. 
	> The program works correctly as long as the name of the plane falls under 10 characters. This could be easily improved, but there is no point in having a plane name with
		more than 7 characters.

-Gall1frey
