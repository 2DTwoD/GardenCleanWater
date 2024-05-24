#include "all_tasks.h"

enum DiagPeriod{
	MIN = 200,
	MID = 1000,
	MAX = 2000,
	DELAY = 500
};

static DiagPeriod serial[]{MAX, MIN, MID, MIN, MID, MIN, MID, MIN};

extern Coil led;

void diagTask(void *pvParameters){
	led = false;
	uint8_t position = 0;
	uint16_t time = 0;
	int8_t dir = 1;
	while(1){
		if(time <= 0){
			time = 0;
			dir = 1;
			position++;
			if(position >= 8){
				position = 0;
			}
		}
		time += dir;
		if(dir > 0 && time > serial[position]){
			time = DELAY;
			dir = -1;
		}
		led = dir < 0;
		vTaskDelay(1);
	}
}
