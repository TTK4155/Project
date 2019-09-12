/*
 * Testproject.c
 *
 * Created: 05/09/2019 13:33:01
 * Author : tedes
 */ 



#include <avr/io.h>
#define F_CPU 4915200UL
#include <util/delay.h>
#include "communication.h"
#include "RAMtest.h"
#include <stdio.h>

#include <stdlib.h>

#define FOSC 49152000   // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main( void )
{   
	// initialization of the serial port, function is in communication.h
	My_serial_Init ( MYUBRR );
	// initialization of the ram, function is in RAMtest.h
	RAM_init();
	// test programm for the RAM
	SRAM_test();
	// function to print trough the serial port, function is in communication.h
	//printf("\n\r after SRAM test \n\r");
	
	// test program to print trough the serial port
    /*
	while(1){
		printf("heello");		 
		_delay_ms(1000);
	}
	*/
}

