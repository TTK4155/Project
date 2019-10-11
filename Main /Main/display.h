/*
This is the display header
*/


#ifndef DISPLAY_H_
#define DISPLAY_H_


#define NUM_LINES    							8
#define NUM_COLUMNS							128
#define FONTWIDTH                 5   //For normal font




void OLED_init(void);
void OLED_write_command(uint8_t cmnd);
void OLED_write_data (uint8_t data );
void OLED_print_char(char c);
void OLED_print_char2(char c,int font);
void OLED_printf(char *data,int font);
void OLED_print(char *data);
void OLED_goto_line(uint8_t line);
void OLED_clear_line(uint8_t line);
void OLED_goto_column(uint8_t column);
void OLED_home(void);
void OLED_reset(void);
void OLED_pos(uint8_t row, uint8_t column);
void OLED_set_brightness(uint8_t level);
int OLED_draw_circle(uint8_t x, uint8_t y, uint8_t r);

#endif /* OLED_H_ */
