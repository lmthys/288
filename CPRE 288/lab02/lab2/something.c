#include "open_interface.h"
#include "movement.h"

void main() {
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

   int d = 0;
   while( d < 2000){

	   oi_update(sensor_data);
	   d += sensor_data->distance;
	   oi_setWheels(250, 250);

	   if (sensor_data->bumpLeft) {
	       d = d + sensor_data->distance;
	       move_back(sensor_data, -15);
	       d = d - 150;
	       turn_clockwise(sensor_data, -90);
	       move_forward(sensor_data, 25);
	       turn_counterclockwise(sensor_data, -90);
	    }
	   if (sensor_data->bumpRight) {
		   d = d + sensor_data->distance;
		   move_back(sensor_data, -15);
		   d = d - 150;
		   turn_counterclockwise(sensor_data, -90);
		   move_forward(sensor_data, 25);
		   turn_clockwise(sensor_data, -90);
	   }
	   if (sensor_data->bumpLeft && sensor_data->bumpRight ) {
		   d = d + sensor_data->distance;
		   move_back(sensor_data, -15);
		   d = d - 150;
		   turn_clockwise(sensor_data, -90);
		   move_forward(sensor_data, 25);
		   turn_counterclockwise(sensor_data, -90);
	   }
	   oi_update(sensor_data);
	   d += sensor_data->distance;
   }
   oi_setWheels(0, 0);







}
