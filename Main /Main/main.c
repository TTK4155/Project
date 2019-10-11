/*
 * Testproject.c
 *
 * Created: 05/09/2019 13:33:01
 * Author : tedes
 */ 



#include <avr/io.h>
#define F_CPU 4915200
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "communication.h"
#include "RAMtest.h"
#include "Joystick.h"
#include "display.h"
#include "OLEDmenu.h"
#include "ADC.h"
#include "spi_driver.h"
#include "mcp2515_driver.h"
#include "CAN_driver.h"

#define FOSC 49152000   // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main( void )
{   
	// initialization of the serial port, function is in communication.h
	My_serial_Init ( MYUBRR );
	
	// initialization of the ram, function is in RAMtest.h
	RAM_init();
	joystick_init();
	// test programm for the RAM
	//SRAM_test();
// 	joy_position dir;
// 	slider_position slider;
	
    //volatile uint8_t *OLED_cmnd = (uint8_t *) 0x1000;
	
	OLED_init();
	OLED_reset();
	MENU_init();
	CAN_init();
	
	CAN_message message;
	message.id = 1;
	message.length = 3;
	message.data[0] = 5;
	message.data[1] = 2;
	message.data[2] = 7;
	while (1)
	{
		CAN_message_send(&message);
		_delay_ms(30);
		//CAN_data_receive();
		CAN_message msg = CAN_data_receive();
		printf("THE MESSAGE IS: %d %d %d \n\r", msg.data[0], msg.data[1], msg.data[2]);
		       
// 		printf("Printing the first data in the message: %d \n", msg.data);
	}
	

	
// while(1)
// {   //printf("a");
// 	//pos = get_joy_pos();
// 	dir = get_joy_direction();
// 	slider = get_slider_pos();
// 	
//  	move_cursor(dir.direction_y);
// 	 printf("value x = %d \n\r",dir.x);
// 	 printf("direction x = %c \n\n\n\r",dir.direction_x);
// 	 printf("value y = %d \n\r",dir.y);
// 	 printf("direction y = %c \n\n\n\r",dir.direction_y);
// // 	
// // 	//printf("  X-POSITION: %d, Y-POSITION: %d , DIRECTION-X: %c \n\r", pos.x, pos.y, dir.direction_x ,dir.direction_y);
// // 	printf("\n\r ---------------------------------------------\n\r");
//  	printf("LEFT SLIDER: %d, RIGHT SLIDER: %d   \n\r", slider.left_slider, slider.right_slider);
//  	printf("\n\r -------------------------- \\ -------------------\n\r");
// // 	
//  	_delay_ms(250);
// // }
// 	// function to print trough the serial port, function is in communication.h
// 	//printf("\n\r after SRAM test \n\r");
// 	
// 	// test program to print trough the serial port
//     /*
// 	while(1){
// 		printf("heello");		 
// 		_delay_ms(1000);
// 	}
// 	*/
}


