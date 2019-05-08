/*
 * movement.c
 *
 *  Created on: Jan 26, 2017
 *      Author: lmandrew
 */

#include "open_interface.h"

void move_forward(oi_t *sensor, int centimeters){

		int sum = 0;
	    oi_setWheels(250, 250); // move forward; full speed
	    while (sum < centimeters*10) {
	        oi_update(sensor);
	        sum += sensor->distance;
	    }
	    oi_setWheels(0, 0); // stop

	    //oi_free(sensor);
}
void move_back(oi_t *sensor, int centimeters){

		int sum = 0;
	    oi_setWheels(-250, -250); // move forward; full speed
	    while (sum > centimeters*10) {
	        oi_update(sensor);
	        sum += sensor->distance;
	    }
	    oi_setWheels(0, 0); // stop

	    //oi_free(sensor);
}
void turn_clockwise(oi_t *sensor, int degrees){

			int sum = 0;
		    oi_setWheels(-200, 250); // move forward; full speed
		    while (sum > degrees) {
		        oi_update(sensor);
		        sum += sensor->angle;
		    }
		    oi_setWheels(0, 0); // stop

		   // oi_free(sensor);
}
void turn_counterclockwise(oi_t *sensor, int degrees){

			int sum = 0;
		    oi_setWheels(250, -200); // move forward; full speed
		    while (sum > degrees) {
		        oi_update(sensor);
		        sum -= sensor->angle;
		    }
		    oi_setWheels(0, 0); // stop

		   // oi_free(sensor);
}
