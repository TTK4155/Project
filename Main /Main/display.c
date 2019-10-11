/*
This is the display driver
*/

#include <avr/pgmspace.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#define F_CPU 4915200
#include <util/delay.h>
#include "display.h"
#include "Fonts.h"





// Address for the OLED command
volatile uint8_t *OLED_cmnd = (uint8_t *) 0x1000;

// Address for the OLED data
volatile uint8_t *OLED_data = (uint8_t *) 0x1200;

//we may not need this...
uint8_t line = 0;
uint8_t actual_line=0;


// Initialization of the display
void OLED_init()
{

  OLED_write_command(0xae);  //display off
  OLED_write_command(0xa1);  //segment remap

  OLED_write_command(0xda);  //common pads hardware: alternative

  OLED_write_command(0x12);
  OLED_write_command(0xc8);  //common output scan direction:com63~com0
  OLED_write_command(0xa8);  //multiplex ration mode:63
  OLED_write_command(0x3f);
  OLED_write_command(0xd5);  //display divide ratio/osc. freq. mode
  OLED_write_command(0x80);
  OLED_write_command(0x81);  //contrast control
  OLED_write_command(0x50);
  OLED_write_command(0xd9);  //set pre-charge period
  OLED_write_command(0x21);
  OLED_write_command(0x20);  //Set Memory Addressing Mode
  OLED_write_command(0x02);
  OLED_write_command(0xdb);  //VCOM deselect level mode
  OLED_write_command(0x30);
  OLED_write_command(0xad);  //master configuration
  OLED_write_command(0x00);
  OLED_write_command(0xa4);  //out follows RAM content
  OLED_write_command(0xa6);  //set normal display
  OLED_write_command(0xaf);  // display on

}


void OLED_write_command(uint8_t cmnd){
  *OLED_cmnd = cmnd;
}


void OLED_write_data (uint8_t data ){
	*OLED_data = data;
}

//print only one character
void OLED_print_char(char c)
{
	if (c == '\n')
	{
		OLED_goto_line(actual_line+1);
	}
	else{
	//Write the complete character
	for (int i = 0; i < FONTWIDTH; i++) {
		*OLED_data = pgm_read_byte(&font5[c - ' '][i]);
	}
	}
}

void OLED_print_char2(char c, int font)
{
	if (c == '\n')
	{
		OLED_goto_line(actual_line+1);
	}
	else{
		
	switch (font){
		case 1: 
			//Write the complete character
			for (int i = 0; i < 4; i++) {
				*OLED_data = pgm_read_byte(&font4[c - ' '][i]);
			}
			break;
		case 2:
			for (int i = 0; i < 5; i++) {
				*OLED_data = pgm_read_byte(&font5[c - ' '][i]);
			}
			break;
		case 3:
			for (int i = 0; i < 8; i++) {
				*OLED_data = pgm_read_byte(&font8[c - ' '][i]);
			}
			break;
		default:
			for (int i = 0; i < 5; i++) {
				*OLED_data = pgm_read_byte(&font5[c - ' '][i]);
			}
			break;
	}
}
}

//Prints a string
void OLED_printf(char *data, int font)
{
	int i = 0;
	
	//Write the complete string
	while(data[i] != '\0'){
		OLED_print_char2(data[i], font);
		i++;
	}
}

//Prints a string
void OLED_print(char *data) 
{
	int i = 0;
	
	//Write the complete string
	while(data[i] != '\0'){
		OLED_print_char(data[i]);
		i++;
	}
}

//Go to page
void OLED_goto_line(uint8_t line) 
{
    actual_line=line;
  	//Check if it's a valid page
	if (line < NUM_LINES) {
		//Save the page we are moving to
		//page = line;
		//Set lower column address
    OLED_write_command(0x00);
		//Set higher column address
    OLED_write_command(0x10);
		//Set page address
    OLED_write_command(0xB0 | line);
	}
}

//Clear the page
void OLED_clear_line(uint8_t line) {
	OLED_goto_line(line);

	for (int i = 0; i < NUM_COLUMNS; i++) {
    OLED_write_data(0x00);
	}
}


void OLED_goto_column(uint8_t column){
  if(column < NUM_COLUMNS){
	uint8_t high = (column>>4);
    //unsigned *uint8_t high=(column >> 4);
    uint8_t low = column & 0xf;
    //unsigned uint8_t low = column & 0xf;

    OLED_write_command(high);
    OLED_write_command(low | 0b00010000);

	}
}


void OLED_home()
{ actual_line=0;
  OLED_goto_line(0);
  OLED_goto_column(0);
}


void OLED_reset(){
  //Resets the brightness of the display
  //OLED_write_command(0x7F);

  //clears the display
  for (uint8_t line = 0; line < NUM_LINES; line++)
  {
    OLED_clear_line(line);
  }
  OLED_home();
}

void OLED_pos(uint8_t row, uint8_t column)
{
  actual_line=row;
  OLED_goto_line(row);
  OLED_goto_column(column);
}


//I don't know if this is right ??
void OLED_set_brightness(uint8_t level){
  OLED_write_command(0x81);
  OLED_write_command(level);
}


int OLED_draw_circle(uint8_t x, uint8_t y, uint8_t r) {
	int circle;
	
	if (r < 8) {
		circle = r - 1;
		} else {
		return -1;
	}
	
	//Set position
	OLED_goto_line(x);
	//OLED_goto_column(y);
	if (y < 128) {
		*OLED_cmnd = 0x00 + (y >> 4);
		*OLED_cmnd = 0x10 + (y >> 4);
	}

	//Draw circle (first part)
	for(int i = 0; i < 16; i++) {
		*OLED_data = pgm_read_byte(&circles[circle][i]);
		_delay_ms(20);
	}
	
	//Set position
		OLED_goto_line(x+1);
		OLED_goto_column(y);
		if (y < 128) {
			*OLED_cmnd = 0x00 + (y >> 4);
			*OLED_cmnd = 0x10 + (y >> 4);
		}
		
		//Draw circle (second part)
		for(int i = 16; i < 32; i++) {
			*OLED_data = pgm_read_byte(&circles[circle][i]);
			_delay_ms(20);
	
		}

	return 0;
}