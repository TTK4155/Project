/*
 * OLED_menu.h
 *
 * Created: 26/09/2019 14:16:00
 *  Author: tedes
 */ 


#ifndef OLED_MENU_H_
#define OLED_MENU_H_
#include <avr/interrupt.h>


void MENU_init(void);
void print_cursor(void);
void clear_cursor();
void move_cursor(char dir);

void selected_menu(void);

void STARTMENU_init(void);



#endif /* OLED_MENU_H_ */