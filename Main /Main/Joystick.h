/*
 * IncFile1.h
 *
 * Created: 20/09/2019 11:43:45
 *  Author: tedes
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_
#define F_CPU 4915200
#define ADC_OFFSET 0x1400
#include <util/delay.h>
#include "ADC.h"


typedef struct {
	int8_t x;
	int8_t y;
	char direction_x;
	char direction_y;
} joy_position;

typedef struct {
	int8_t right_slider;
	int8_t left_slider;
} slider_position;


void joystick_init(void);
void joystick_calibrate(void);  //we may not need this one 
//int joystick_button(int button);
joy_position get_joy_pos(void);
joy_position get_joy_direction(void);
slider_position get_slider_pos(void);




#endif /* INCFILE1_H_ */