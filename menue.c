/*
 * menue.c
 *
 *  Created on: 17.05.2020
 *      Author: adrianschmidt
 */
#include <msp430.h>
#include <stdint.h>
#include "menue.h"
#include "lcd.h"

extern uint8_t menue_counter=0;
extern uint8_t menue_option=0;


void menue_print_options(const char *str1, const char *str2){
    lcd_gotoxy(0,0);
    lcd_put_char('>');
    lcd_write(str1);

    lcd_gotoxy(0,1);
    lcd_put_char('>');
    lcd_write(str2);
}
void menue_count_up(){
    if(menue_counter<3){
        menue_counter++;
    }
}
void menue_count_down(){
    if(menue_counter>0){
            menue_counter--;
        }
};

void menue_refresh_display(){
    switch(menue_counter){
    case 0: menue_print_options(MENUE_OPTION1, MENUE_OPTION2);
            lcd_set_cursor_Position(0,0);
        break;
    case 1: menue_print_options(MENUE_OPTION1, MENUE_OPTION2);
            lcd_set_cursor_Position(0,1);
        break;
    case 2: menue_print_options(MENUE_OPTION3, MENUE_OPTION4);
            lcd_set_cursor_Position(0,0);
        break;
    case 3: menue_print_options(MENUE_OPTION1, MENUE_OPTION2);
            lcd_set_cursor_Position(0,1);
        break;
    }
}

void menue_select(){
    switch(menue_counter){
    case 0:menue_option=0;
        break;
    case 1:menue_option=1;
        break;
    case 2:menue_option=2;
        break;
    case 3:menue_option=3;
        break;
    }
}

void menue_back(){
    lcd_clear_Display();
    menue_refresh_display();
    menue_option=0;
}



