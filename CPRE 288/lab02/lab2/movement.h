/*
 * movement.h
 *
 *  Created on: Jan 26, 2017
 *      Author: lmandrew
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

void move_forward(oi_t *sensor, int centimeters);
void move_back(oi_t *sensor, int centimeters);
void turn_clockwise(oi_t *sensor, int degrees);
void turn_counterclockwise(oi_t *sensor, int degrees);



#endif /* MOVEMENT_H_ */
