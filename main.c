#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "ip_op.h"
#include "decisions.h"
#include "beautify.h"

int main(){

	srand(time(0));

	//initializing most variables
	int runways = 1,i;
	float rate = 0.5;
	char ch = 'x',decision;
	char filename[10];
	plane new,runway_hog;
	plane *tk_off = NULL, *land = NULL;
	message tmp_msg;
	message *msg_head = (message*)malloc(sizeof(message));
	strcpy(msg_head->msg,"START\n");
	msg_head->col = 2;
	msg_head->next = NULL;
	
	//Taking in setup values
	clear_screen();
	printf("\tEnter number of runways: ");
	scanf("%d",&runways);
	printf("\tEnter probability of planes failing to land/takeoff (0-1): ");
	scanf(" %f",&rate);
	
	//Taking in name of the file.
	//If no such file exists, it promots again
	do{
		printf("\tEnter name of data file: ");
		scanf("%s",filename);
		tk_off = read_from_file(filename,'t');
		land = read_from_file(filename,'l');
	}while(tk_off == NULL && land == NULL);
	change_text_color(2);
	printf("\n\t\tFLIGHTS HAVE BEEN ADDED.\n");
	change_text_color(4);
	wait(1);

	clear_screen();
	sort_tk_off(&tk_off);
	sort_land(&land);
	display(tk_off,land,msg_head);

	//simulation starts here
	ch = menu();
	while(ch != 'x'){
		clear_screen();
		if(ch == 'a' || ch == 'A'){
			new = user_input();
			if(new.status == air)
				add_flight(new,land);
			else
				add_flight(new,tk_off);
			sprintf(tmp_msg.msg,"FLIGHT HAS BEEN ADDED.\n");
			tmp_msg.col = 2;
			add_msg(tmp_msg,msg_head);
			wait(1);
			clear_screen();
			sort_tk_off(&tk_off);
			sort_land(&land);
			display(tk_off,land,msg_head);
		}else if(ch == 'c' || ch == 'C'){
			sort_tk_off(&tk_off);
			sort_land(&land);
			for(i = 0; i < runways; i++){
				if(count_planes(land) == 0 && count_planes(tk_off) == 0){
					sprintf(tmp_msg.msg,"NO MORE PLANES, SHUTTING DOWN AIRPORT.\n");
					tmp_msg.col = 1;
					add_msg(tmp_msg,msg_head);
					clear_screen();
					display(tk_off,land,msg_head);
					exit(0);				
				}
				if(count_planes(land) > 0 && count_planes(tk_off) > 0)
					decision = decide(tk_off[0],land[0],count_planes(land));
				else if(count_planes(land) == 0)
					decision = 't';
				else if(count_planes(tk_off) == 0)
					decision = 'l';
				if(decision == 'l'){
					runway_hog = pop(&land);
					sprintf(tmp_msg.msg,"PLANE %s GETTING READY TO LAND ON RUNWAY %d.\n",runway_hog.name,i+1);
					tmp_msg.col = 3;
					add_msg(tmp_msg,msg_head);
					clear_screen();
					sort_tk_off(&tk_off);
					sort_land(&land);
					display(tk_off,land,msg_head);
					if(random_decider(rate)){
						sprintf(tmp_msg.msg,"PLANE %s HAS LANDED SUCCESSFULLY ON RUNWAY %d.\n",runway_hog.name,i+1);
						tmp_msg.col = 2;
						add_msg(tmp_msg,msg_head);
					}else{
						sprintf(tmp_msg.msg,"PLANE %s COULDN'T LAND ON RUNWAY %d.\n",runway_hog.name,i+1);
						tmp_msg.col = 1;
						add_msg(tmp_msg,msg_head);
						add_flight(runway_hog,land);
					}
				}else{
					runway_hog = pop(&tk_off);
					sprintf(tmp_msg.msg,"PLANE %s GETTING READY TO TAKE OFF ON RUNWAY %d.\n",runway_hog.name,i+1);
					tmp_msg.col = 3;
					add_msg(tmp_msg,msg_head);
					clear_screen();
					sort_tk_off(&tk_off);
					sort_land(&land);
					display(tk_off,land,msg_head);
					if(random_decider(rate)){
						sprintf(tmp_msg.msg,"PLANE %s HAS TAKEN OFF SUCCESSFULLY OFF RUNWAY %d.\n",runway_hog.name,i);
						tmp_msg.col = 2;
						add_msg(tmp_msg,msg_head);
					}else{
						sprintf(tmp_msg.msg,"PLANE %s COULDN'T TAKE OFF OFF RUNWAY %d.\n",runway_hog.name,i+1);
						tmp_msg.col = 1;
						add_msg(tmp_msg,msg_head);
						add_flight(runway_hog,tk_off);
					}
				}
				clear_screen();
				sort_tk_off(&tk_off);
				sort_land(&land);
				display(tk_off,land,msg_head);
			}
			update_air_time(land);
		}
			ch = menu();
	}
	//when user wants to run the simulation on its own and then quit
	while(1){
		sort_tk_off(&tk_off);
		sort_land(&land);
		for(i = 0; i < runways; i++){
				if(count_planes(land) == 0 && count_planes(tk_off) == 0){
					sprintf(tmp_msg.msg,"NO MORE PLANES, SHUTTING DOWN AIRPORT.\n");
					tmp_msg.col = 1;
					add_msg(tmp_msg,msg_head);
					clear_screen();
					display(tk_off,land,msg_head);
					exit(0);				
				}
				if(count_planes(land) > 0 && count_planes(tk_off) > 0)
					decision = decide(tk_off[0],land[0],count_planes(land));
				else if(count_planes(land) == 0)
					decision = 't';
				else if(count_planes(tk_off) == 0)
					decision = 'l';
				if(decision == 'l'){
					runway_hog = pop(&land);
					sprintf(tmp_msg.msg,"PLANE %s GETTING READY TO LAND ON RUNWAY %d.\n",runway_hog.name,i+1);
					tmp_msg.col = 3;
					add_msg(tmp_msg,msg_head);
					clear_screen();
					sort_tk_off(&tk_off);
					sort_land(&land);
					display(tk_off,land,msg_head);
					if(random_decider(rate)){
						sprintf(tmp_msg.msg,"PLANE %s HAS LANDED SUCCESSFULLY ON RUNWAY %d.\n",runway_hog.name,i+1);
						tmp_msg.col = 2;
						add_msg(tmp_msg,msg_head);
					}else{
						sprintf(tmp_msg.msg,"PLANE %s COULDN'T LAND ON RUNWAY %d.\n",runway_hog.name,i+1);
						tmp_msg.col = 1;
						add_msg(tmp_msg,msg_head);
						add_flight(runway_hog,land);
					}
				}else{
					runway_hog = pop(&tk_off);
					sprintf(tmp_msg.msg,"PLANE %s GETTING READY TO TAKE OFF ON RUNWAY %d.\n",runway_hog.name,i+1);
					tmp_msg.col = 3;
					add_msg(tmp_msg,msg_head);
					clear_screen();
					sort_tk_off(&tk_off);
					sort_land(&land);
					display(tk_off,land,msg_head);
					if(random_decider(rate)){
						sprintf(tmp_msg.msg,"PLANE %s HAS TAKEN OFF SUCCESSFULLY OFF RUNWAY %d.\n",runway_hog.name,i);
						tmp_msg.col = 2;
						add_msg(tmp_msg,msg_head);
					}else{
						sprintf(tmp_msg.msg,"PLANE %s COULDN'T TAKE OFF OFF RUNWAY %d.\n",runway_hog.name,i+1);
						tmp_msg.col = 1;
						add_msg(tmp_msg,msg_head);
						add_flight(runway_hog,tk_off);
					}
				}
				clear_screen();
				sort_tk_off(&tk_off);
				sort_land(&land);
				display(tk_off,land,msg_head);
				wait(1);
			}
			wait(1);
			update_air_time(land);
	}
	
	return 0;
}

//Features Test
/*
	clear_screen();
	char filename[10];
	printf("Enter name of data file: ");
	scanf("%s",filename);
	plane* tk_off = read_from_file(filename,'t');
	plane* land = read_from_file(filename,'l');
	display(tk_off,land);
	plane new = user_input();
	if(new.status == air)
		add_flight(new,land);
	else
		add_flight(new,tk_off);
	clear_screen();
	change_text_color(2);
	printf("FLIGHT HAS BEEN ADDED.\n");
	wait(2);
	change_text_color(4);
	clear_screen();
	printf("\n\nPLANES ON GROUND: %d\n",count_planes(tk_off));
	printf("PLANES IN AIR:    %d\n\n",count_planes(land));
	printf("ORDERED PLANES:\n\n");
	sort_tk_off(&tk_off);
	sort_land(&land);
	display(tk_off,land);
	printf("\n\nDecision: %c\n",decide(tk_off[0],land[0],count_planes(land)));
*/
