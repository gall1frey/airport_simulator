#include "ip_op.h"
#include "decisions.h"

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

int random_decider(float rate){
	int random_no = rand();
	if(random_no % (int) (1/rate))
		return 1;
	return 0;
}

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
