/*
 * OLEDmenu.c
 *
 * Created: 26/09/2019 14:16:38
 *  Author: tedes
 */ 
#include <avr/pgmspace.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#define F_CPU 4915200
#include <util/delay.h>
#include "display.h"
#include "OLEDmenu.h"

char* menuList[] = {"START", "Players", "Score","circle"};
char* STARTmenuList[] = {"COLOUR", "POINT", "BACK"};
int menu=0;	
uint8_t cursorLine = 0;

int length = sizeof(menuList)/sizeof(menuList[0]);

ISR (INT2_vect)
{
	printf("BUTTTON pressed \n");
	printf("CURSOR POSITION: %d \n",cursorLine+1);   // the cursorLine start from 0 while the rows on the OLED start from one 
	selected_menu();
}

void MENU_init(void)
{  
	OLED_reset();
	menu=0;
	for (int i=0; i<length; i++)
	{
		OLED_goto_column(1);
		OLED_printf(menuList[i],3);
		OLED_print("\n");
	}
	
	print_cursor();
	
}

void STARTMENU_init(void)
{   
	OLED_reset();
	menu=1;
	for (int i=0; i<length; i++)
	{
		OLED_goto_column(1);
		OLED_printf(STARTmenuList[i],2);
		OLED_print("\n");
	}
	
	print_cursor();
	
}

void print_cursor(){
	//OLED_pos(cursorLine, 0);
	OLED_draw_circle(cursorLine,3,2);
}

void clear_cursor(){
	OLED_goto_line(cursorLine);
	for (int i = 0; i < 5; i++) {
		OLED_write_data(0x00);
	}
}

void move_cursor(char dir){
	if (dir == 'D'){
		
		clear_cursor();
		if(cursorLine < length - 1)
		{
			cursorLine += 1;
		}else{
			cursorLine = 0;
		}
		print_cursor();
		
	}else if (dir == 'U' && cursorLine >= 0 ){
		clear_cursor();
		cursorLine -= 1;
		print_cursor();
	}
}

void selected_menu(void)
{
	if (cursorLine==0 && menu==0)
	{
		STARTMENU_init();
	}
	if (cursorLine==3 && menu==0)
	{   OLED_reset();
		OLED_draw_circle(3,60,7);
		_delay_ms(2000);
		MENU_init();
		
	}
	
	if (cursorLine==2 && menu==1)
	{
		MENU_init();
	}
}


