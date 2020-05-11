#include "ip_op.h"
#include "decisions.h"
#include "beautify.h"

void change_text_color(int color){
	char command[15];
	#ifdef __linux__
		if(color == 4)
			color = 7;
		sprintf(command,"tput setaf %d",color);
		system(command);
	#endif
	#ifdef _WIN32
		printf("%s",col[color-1]);
	#endif
}

void display(plane *take_off_head, plane *landing_head, message *msg_head){
	//display stuffz
	int i;
	char ch_tk, ch_la;
	plane *tk_iter, *land_iter;
	tk_iter = take_off_head; land_iter = landing_head;
	printf("\n\t\t\t+"); for(i=0;i<70;i++) printf("-"); printf("+\t"); printf("+"); for(i=0;i<82;i++) printf("-"); printf("+\n\t\t\t");
	printf("|%-70s|\t|%-82s|","ON GROUND","IN AIR");
	printf("\n\t\t\t+"); for(i=0;i<70;i++) printf("-"); printf("+\t"); printf("+"); for(i=0;i<82;i++) printf("-"); printf("+\n\t\t\t");
	printf("|%-24s|%-22s|%-22s|\t","PLANE_NAME","EMERGENCY","PASSENGERS"); printf("|%-20s|%-19s|%-20s|%-20s|\n\t\t\t+","PLANE_NAME","AIR_TIME","EMERGENCY","PASSENGERS");
	for( i=0;i<70;i++) printf("-");	printf("+\t+"); for( i=0;i<82;i++) printf("-"); printf("+\n\t\t\t");
	for(i=0;i<15;i++){		
		if(tk_iter != NULL && tk_iter->emergency) ch_tk = 'Y';
		else ch_tk = 'N';
		if(land_iter != NULL && land_iter->emergency) ch_la = 'Y';
		else ch_la = 'N';
		if(tk_iter && land_iter){
			printf(table_entry,tk_iter->name,ch_tk,tk_iter->no_of_passengers,land_iter->name,land_iter->air_time,ch_la,land_iter->no_of_passengers);
		}else if(tk_iter && !land_iter){
			printf(table_entry,tk_iter->name,ch_tk,tk_iter->no_of_passengers," -",0,'*',0);
		}else if(!tk_iter && land_iter){
			printf(table_entry," -",'*',0,land_iter->name,land_iter->air_time,ch_la,land_iter->no_of_passengers);
		}else{
			printf(table_entry," -",'*',0," -",0,'*',0);
		}
		if(tk_iter != NULL) tk_iter = tk_iter->next;
		if(land_iter != NULL) land_iter = land_iter->next;
	}
	printf("+"); for(i=0;i<70;i++) printf("-"); printf("+\t"); printf("+"); for(i=0;i<82;i++) printf("-"); printf("+\n");
	
	message *msg_iter = msg_head;
	int msg_count = count_msg(msg_head);

	while(msg_iter != NULL){
		if(msg_count <= 10){
			change_text_color(msg_iter->col);
			printf("\t\t\t%s",msg_iter->msg);
			change_text_color(4);
		}
		msg_count--;
		msg_iter = msg_iter->next;
	}
}

void clear_screen(){
	#ifdef _WIN32
		system("cls");
		printf(banner_win);
	#endif
	#ifdef __linux__
		system("clear");
		printf(banner_linux);
	#endif
}

void wait(int sec){
	#ifdef _WIN32
		Sleep(sec*1000);
	#else
		sleep(sec);
	#endif
}