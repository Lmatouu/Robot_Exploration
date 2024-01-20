// copilot.h

#ifndef COPILOT_H
#define COPILOT_H

#include "pilot.h"

/**
 * @file copilot.h
 * @brief Declaration of the Copilot class.
 * @license MIT
 */

/**
 * @brief Initiates a path for the robot to follow.
 */
extern void copilot_start_path(void);

/**
 * @brief Moves the robot to the next step in the path.
 */
extern void copilot_next_step(void);

/**
 * @brief Stops the robot when the current step in the path is completed.
 *
 * @return The status of stopping at the step completion.
 */
extern move_status copilot_stop_at_step_completion(void);

extern void copilot_insert_avoidance(void);
#endif // COPILOT_H