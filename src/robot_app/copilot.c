// copilot.c

#include "copilot.h"
#include "../utils.h"
#include <stdlib.h>
#include <stdio.h>


static move_status path_status = IDLE;

static move *path = NULL;
static int current_step = 0;
static int path_steps = 0;


extern void copilot_start_path(void) {
  if ((path_status == IDLE) && (path_steps > 0)) {
    path_status = IN_PROGRESS;
    pilot_start_move(path[0]);
  }
}

extern void copilot_next_step(void)
{
	current_step++;
	if( current_step >= path_steps )
	{
		path_status = DONE;
	}
	else
	{
		pilot_start_move(path[current_step]);
	}
}

extern move_status copilot_stop_at_step_completion(void)
{
	if( pilot_get_status()!=DONE && pilot_stop_at_target()==DONE )
	{
		path_status = IN_PROGRESS;
		copilot_next_step();
	}
	else if( pilot_get_status()==OBSTACLE && path_status != OBSTACLE )
	{
		path_status = OBSTACLE;
		copilot_next_step();
	}
	return pilot_get_status();
}

extern int copilot_is_path_completed(void) {
  return path_status == DONE ? 1 : 0;
}


extern int copilot_create_path(int steps_nb) {
  if ((path == NULL) && (steps_nb > 0)) // dont'allocate if path already existing
  {

    /*TODO: allocate path, */
    /* why calloc is better than malloc ? */

	path = (move *) calloc(steps_nb, sizeof(move));

    if (path != NULL) {
	/*TODO: Update path_steps */
	  path_steps = steps_nb;
	  TRACE("Copilot created a new path with %d steps.\n", path_steps);
      return EXIT_SUCCESS;
    }
  }
  return EXIT_FAILURE;
}

extern int copilot_destroy_path(void) {
  if (path != NULL) {
	/*TODO: free memory */
	free(path);
    path = NULL;
	/*TODO: update path_steps */
	path_steps = 0;
    TRACE("Copilot destroyed the current path.\n");
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

extern int copilot_add_step(int index, move step) {
	/*TODO: check index validity before adding step */
	if( index < path_steps ){
		path[index] = step;
		return EXIT_SUCCESS;
	}
	else{
		return EXIT_FAILURE;
	}
}

move copilot_get_step(int index) {
	move step = {0};
	/*TODO: check index validity before returning step */
	if( index < path_steps){
		step = path[index];
	}
  	return step;
}

extern int copilot_get_number_steps_in_path() { return path_steps; }
