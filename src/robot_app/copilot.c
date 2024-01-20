// copilot.c

#include "copilot.h"
#include "../utils.h"
#include <stdlib.h>
#include <stdio.h>

#define PATH_STEPS	6
#define AVOIDANCE_STEPS 7

static move_status path_status = IDLE;
static move path[PATH_STEPS]=
{
	{ROTATION,{U_TURN},20},
	{FORWARD,{1},20},
	{ROTATION,{LEFT},20},
	{FORWARD,{.distance=1},20},
	{ROTATION,{RIGHT},50},
	{FORWARD,{10},80}
	
};


static move avoidance_path[AVOIDANCE_STEPS] =
{
    {ROTATION, {RIGHT}, 15},
    {FORWARD, {2}, 15},
    {ROTATION, {LEFT}, 15},
    {FORWARD, {2}, 15},
    {ROTATION, {LEFT}, 15},
    {FORWARD, {2}, 15},
    {ROTATION, {RIGHT}, 15}
};

static int current_step = 0;

extern void copilot_start_path(void) {
	/*TODO: Start the path with move path[0] */
	/*HINT: A path can only start if a path is not already in progress */
	if (pilot_get_status() != IN_PROGRESS){
		current_step = 0;
		pilot_start_move(path[current_step]);
	}
}

extern void copilot_next_step(void)
{
	/*TODO: Start next move if it exists, otherwise the path is DONE */
	/*HINT: Update current_step index */

	if (current_step < PATH_STEPS){
		current_step+=1;
		pilot_start_move(path[current_step]);
	}
	else{
		path_status = DONE;
	}	
}

extern move_status copilot_stop_at_step_completion(void)
{
	/*TODO: if pilot status is !DONE and target is reached, then go to next step */
	/*HINT: It might be useful for the future to reset path_status here to IN_PROGRESS */
	
	/*Special management of obstacle detection, no effect yet */
	if( pilot_get_status()==OBSTACLE && path_status != OBSTACLE)
	{
		path_status = OBSTACLE;
		copilot_insert_avoidance();
		printf("ici obstacle \n");
	}
	else if (pilot_get_status()!= DONE && pilot_stop_at_target() == DONE){
		copilot_next_step();
		path_status=IN_PROGRESS;

	}
	return pilot_get_status();
}

extern int copilot_is_path_completed(void) {
  return path_status == DONE ? 1 : 0;
}




extern void copilot_insert_avoidance(void)
{
	/*TODO: Allocate a temp_path to save the current path before deletion (error management if allocation fails) */
	/*Copy the current path steps to the temp_path */
	/*Destroy the path and create a new one with its previous size plus AVOIDANCE_STEPS */
	/*3 intelligent for loops with complementary indexes are enough to copy the previous path steps up to the current step (when obstacle has been detected) + the avoidance steps + the remaining path steps */
	

	//int temp_path=copilot_get_number_steps_in_path(); 
	//copilot_stop_at_step_completion()
	printf("debut evitement \n");
	int avoidance_step=0;
	do{
		pilot_start_move(avoidance_path[avoidance_step]);
		if(pilot_get_status()==OBSTACLE && path_status != OBSTACLE){
			copilot_insert_avoidance();
		}
		avoidance_step+=1;
	}while( avoidance_step < AVOIDANCE_STEPS);	
	printf("fin evitement \n");	
	}





