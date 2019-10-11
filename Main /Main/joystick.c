/*
 * joystick.c
 *
 * Created: 20/09/2019 11:44:24
 *  Author: tedes
 */ 
#include <avr/io.h>
#include "Joystick.h"


uint8_t mid_x=0;
uint8_t mid_y=0;


void joystick_init(void)
{   //INTERRUPT INIT
	// set the pin E0 as an imput interrupt for the putton of the analog 
	//DDRE = (1<< DDE0);  //setting PE0 as aninput with internal pull up
	PORTE = (1<PE0);
	EMCUCR = (0<< ISC2);  //get the interupt signal when the button is pressed (not released)
	SREG = (1 << 7);      //global enable interrupt
	GICR = (1 << INT2);   // enable interrupt INT2 in pin e0 
	
	mid_x= adc_read(2);
	mid_y= adc_read(1);
}

void joystick_calibrate(void)
{
	mid_x= adc_read(2);
	mid_y= adc_read(1);
	
}

joy_position get_joy_pos(void)
{
	joy_position position;
	uint8_t x, y;
	
	x = adc_read(2);
	y = adc_read(1);
	
	if (x > mid_x){
		position.x = 100 * (x - mid_x) / (mid_x);
	}else if (x < mid_x){
		position.x = 100 * (x - mid_x) / (mid_x);	
	}else{
		position.x = 0;
	}
	
	if (y > mid_y){
		position.y = 100 * (y - mid_y) / (mid_y);
		}else if (y < mid_y){
		position.y = 100 * (y - mid_y) / (mid_y);
		}else{
		position.y = 0;
	}
	
	//printf("X-POSITION: %d, Y-POSITION: %d", position.x, position.y);
	return position;
	
}

joy_position get_joy_direction(){
	joy_position position;
	
	position = get_joy_pos();
	
	
	if (position.x <= -1){
		position.direction_x = 'L';
	}else if(position.x >= 1)
	{
		position.direction_x = 'R';
	}
	
	if (position.y <= -1){
		position.direction_y = 'D';
	}else if (position.y >= 1)
	{
		position.direction_y = 'U';
	}
	
	if (position.x == 0)
	{
		position.direction_x = 'N';
	}
	
	if (position.y == 0)
	{
		position.direction_y = 'N';
	}
	
	return position;
}


slider_position get_slider_pos(){
	slider_position position;
	
	uint8_t left, right;
	
	right = adc_read(3);
	left = adc_read(4);
	
	
	position.left_slider = 100 * left / 0xFF;
	position.right_slider = 100 * right / 0xFF;
	
	return position;
}
/*
joy_position get_joy_pos(void)
{
	char direction_x;
	char direction_y;

    int x=adc_read(2);
	int y=adc_read(1);
	
   if (x>mid_x_anal-2 & x<mid_x_anal+2)
   {
	   direction_x="neutral";
   }
   else if (x>mid_x_anal+2)
   {
	   direction_x="right";
   }
   else 
   {
	   direction_x="left";
   }
   
    
	
	 if (y>mid_y_anal-2 & y<mid_y_anal+2)
     {
	     direction_y="neutral";
     }
     else if (y>mid_y_anal+2)
     {
	     direction_y="right";
     }
     else
     {
	     direction_y="left";
     }
	 
	 char direction= direction_y+direction_x;
	 
	 return {x,y,direction};
     
} */ 