/**
 * hello robot main program
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "robot_app/copilot.h"
#include "robot_app/robot.h"
#include "robot_app/pilot.h"

#define TEMPO	2000000

#define POLLING_PERIOD	10000

							
/* Custom type for process state management */
typedef enum{
	STOPPED = 0,
	LIVE
}process_state;

static void robot_loop(void);

/* global variable used for program clean exit */
static process_state running = LIVE;

/**
 * Function for CTRL+C signal management
 */
static void sigint_handler(int dummy)
{
    running = STOPPED;
}

int main (void)
{

  	
	if (robot_start() == -1) {
		return EXIT_FAILURE;
	}

	/* Interception d'un Ctrl+C pour arrêter le programme proprement. */
	signal(SIGINT, sigint_handler);
	
	/* Procédure hello de manipulation du robot. */
	robot_loop();

	/* Arrêt du robot. */
	robot_stop();

	return EXIT_SUCCESS;
}

/**
 * Robot control function
 *
 * Send commands to the robot and display status data with a specific period
 */
static void robot_loop()
{
	
	robot_status my_status;

	while(running)
	{
		
		copilot_start_path();
		
		my_status = robot_get_status();

		fprintf(stdout, "codeurs: g = %d, d = %d\n", my_status.left_encoder, my_status.right_encoder);
		fprintf(stdout, "proxy: g = %d, c = %d, d = %d\n", my_status.left_sensor, my_status.center_sensor, my_status.right_sensor);
		fprintf(stdout, "batterie: %d %%\n", my_status.battery);
		
		/* Encoders polling */
		for(int i=0;i<TEMPO/POLLING_PERIOD;i++)
		{
			usleep(POLLING_PERIOD);
			copilot_stop_at_step_completion();
		}
	}
}




