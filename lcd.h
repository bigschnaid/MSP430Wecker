/*
 * lcd.h
 *
 *  Created on: 14.05.2020
 *      Author: adrianschmidt
 */

#ifndef LCD_H_
#define LCD_H_
#include <stdbool.h>
const bool right;
const bool left;

void lcd_init();
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcd_put_char(char c);
void lcd_write(const char *str);
void lcd_writeTime_and_Date();
void lcd_put_char_on_Position(uint8_t zeichen, uint8_t xpos, uint8_t ypos);
void lcd_put_char_in_Row(uint8_t arr[], uint8_t xpos, uint8_t yposxs );
void lcd_move_Cursor(bool richtung); //notwendig?
void lcd_cursor_on();
void lcd_cursor_off();
void lcd_set_cursor_Position(uint8_t x, uint8_t y);
void lcd_clear_Display();



#endif /* LCD_H_ */
