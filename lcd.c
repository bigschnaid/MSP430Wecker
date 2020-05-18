/*
 * lcd.c
 *
 *  Created on: 14.05.2020
 *      Author: adrianschmidt
 */

#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

#include "lcd.h"
#include "time.h"

typedef enum {
    LCD_COMMAND, LCD_DATA
} lcd_command_t;

// Prototypen
static void send_8bit(uint8_t data, lcd_command_t type);
static void send_4bit(uint8_t data, lcd_command_t type);
static void pin_mode_read();
static void pin_mode_write();
static void set_rs_by_type(lcd_command_t type);
static void set_en();
static void clear_en();
static void set_data_pins(uint8_t data);

/**
 * Initialsierung des LCDs
 */
void lcd_init() {
    // Datenflussrichtung der Pins setzen
    pin_mode_write();

    __delay_cycles(15000);
    send_8bit(0x3, LCD_COMMAND);    // Initialisierungsschlüssel
    __delay_cycles(41000);
    send_8bit(0x3, LCD_COMMAND);    // Initialisierungsschlüssel
    __delay_cycles(100);
    send_8bit(0x3, LCD_COMMAND);    // Initialisierungsschlüssel
    send_8bit(0x2, LCD_COMMAND);    // Function set: 4Bit

    send_4bit(0x28, LCD_COMMAND);   // Function set: 4bit, 2Line
    send_4bit(0x0F, LCD_COMMAND);
    send_4bit(0x06, LCD_COMMAND);// Entry mode set: Links nach rechts, überschreiben
    send_4bit(0x01, LCD_COMMAND);   // Clear Display

    __delay_cycles(40000);
}

/**
 * Bewegen des Cursors an die angegebene Position
 * @param x Spalte (0 ... 15)
 * @param y Zeile (0, 1)
 */
void lcd_gotoxy(uint8_t x, uint8_t y) {
    uint8_t address;

    if (y == 0) {
        address = 0x80;
    } else {
        address = 0xC0;
    }

    address += x;

    send_4bit(address, LCD_COMMAND);
}

/**
 * Ausgeben eines Ascii-Zeichens auf dem LCD
 * @param c Zeichen
 */

void lcd_put_char(char c) {
    send_4bit(c, LCD_DATA);
}

/**
 * Ausgeben einer Zeichenkette auf dem LCD
 * @param str   Zeichenkette
 */
void lcd_write(const char *str) {
    while (*str != 0) {
        lcd_put_char(*str);
        str++;
    }
}

// Funktionen zur Datenübertragung

/**
 * Senden eines Bytes an das LCD mit Hilfe der 8-Bit-Kommunikation
 * @param data  Byte
 * @param type  Typ des Bytes (LCD_COMMAND, LCD_DATA)
 */
static void send_8bit(uint8_t data, lcd_command_t type) {
    __delay_cycles(40);

    set_rs_by_type(type);

    set_en();
    set_data_pins(data);
    clear_en();
}

/**
 * Senden eines Bytes an das LCD mit Hilfe der 4-Bit-Kommunikation
 * @param data  Byte
 * @param type  Typ des Bytes (LCD_COMMAND, LCD_DATA)
 */
static void send_4bit(uint8_t data, lcd_command_t type) {
    __delay_cycles(40);

    set_rs_by_type(type);

    set_en();
    set_data_pins(data >> 4);
    clear_en();

    set_en();
    set_data_pins(data);
    clear_en();
}

/**
 * Bewegen des Cursors in eine Richtung
 * 1: nach rechts, 0:nach links
 */
void lcd_move_Cursor(bool richtung){
    if(richtung)
        send_4bit(0x14, LCD_COMMAND);
    else
        send_4bit(0x10, LCD_COMMAND);
}


//cursor on
void lcd_cursor_on(){
    send_4bit(0x0E, LCD_COMMAND); //Display on, Cursor on, no blink
}

//cursor off
void lcd_cursor_off(){
    send_4bit(0x0C, LCD_COMMAND); //Display on, Cursor off, no blink
}

/**
 * Cursor Position wechseln und Cursor anschalten.
 * ÜbergabeParameter sind x und y Koordinaten auf dem LCD Display
 */

void lcd_set_cursor_Position(uint8_t x, uint8_t y){
    lcd_gotoxy(x,y);
    lcd_cursor_on();
}


// Pin-Funktionen

/**
 * Setzen der Datenflussrichtung aller Pins der MSP430, die zur Steuerung des LCDs benötigt werden
 */
static void pin_mode_write() {
    // Datenpins als Ausgang
    P1DIR |= BIT0 + BIT1 + BIT2 + BIT3;
    P1OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3);

    // RS + EN als Ausgang
    P2DIR |= BIT3 + BIT4;
    P2OUT &= ~(BIT3 + BIT4);
}

static void pin_mode_read(){
    P1DIR &= ~(BIT0 + BIT1 + BIT2 + BIT3);
    P1IN &= ~(BIT0 + BIT1 + BIT2 + BIT3);

        // RS + EN als Ausgang
   P2DIR |= BIT3 + BIT4;
   P2OUT &= ~(BIT3 + BIT4);
}
/**
 * Setzen des RS-Pins entsprechend des Befehlstyps
 * @param type  LCD_COMMAND -> RS = LOW
 *              LCD_DATA    -> RS = HIGH
 */
static void set_rs_by_type(lcd_command_t type) {
    if (type == LCD_COMMAND) {
        P2OUT &= ~ BIT3;
    } else {
        P2OUT |= BIT3;
    }
}

/**
 * Setzen des EN-Pins auf HIGH
 */
static void set_en() {
    P2OUT |= BIT4;
}

/**
 * Setzen des EN-Pins auf LOW
 */
static void clear_en() {
    P2OUT &= ~BIT4;
}

/**
 * Setzen der Datenpins entsprechend der angebenen 4 Bits
 * @param data Die 4 niederwertigsten Bits werden an den Pins angelegt.
 */
static void set_data_pins(uint8_t data) {
    P1OUT = (P1OUT & 0xf0) + (data & 0x0f);
}


//Cursor Position wechseln und an die Stelle Zeichen ausgeben
void lcd_put_char_on_Position(uint8_t zeichen, uint8_t xpos, uint8_t ypos){
    lcd_gotoxy(xpos, ypos);
    lcd_put_char(zeichen);
}

/**
 * Funktion zeigt Zeit und Datum abhängig von den Startpositionen xposT,yposT, xPOsD und xposD an.
 */
void lcd_writeTime_and_Date(){

    lcd_clear_Display();
    lcd_cursor_off();

    uint8_t xposT =4;
    uint8_t yposT =1;

    uint8_t xposD =3;
    uint8_t yposD =0;

    lcd_put_char_on_Position(hours_zehner,xposT,yposT);xposT++;
    lcd_put_char_on_Position(hours_einer,xposT,yposT);xposT++;
    lcd_put_char_on_Position(':',xposT,yposT);xposT++;
    lcd_put_char_on_Position(minutes_zehner,xposT,yposT);xposT++;
    lcd_put_char_on_Position(minutes_einer,xposT,yposT);xposT++;
    lcd_put_char_on_Position(':',xposT,yposT);xposT++;
    lcd_put_char_on_Position(seconds_zehner,xposT,yposT);xposT++;
    lcd_put_char_on_Position(seconds_einer,xposT,yposT);xposT++;

    lcd_put_char_on_Position(days_zehner,xposD,yposD);xposD++;
    lcd_put_char_on_Position(days_einer,xposD,yposD);xposD++;
    lcd_put_char_on_Position('.',xposD,yposD);xposD++;
    lcd_put_char_on_Position(month_zehner,xposD,yposD);xposD++;
    lcd_put_char_on_Position(month_einer,xposD,yposD);xposD++;
    lcd_put_char_on_Position('.',xposD,yposD);xposD++;
    lcd_put_char_on_Position(years_tausender,xposD,yposD);xposD++;
    lcd_put_char_on_Position(years_hunderter,xposD,yposD);xposD++;
    lcd_put_char_on_Position(years_zehner,xposD,yposD);xposD++;
    lcd_put_char_on_Position(years_einer,xposD,yposD);xposD++;

    }

//Löscht alle Ausgaben auf dem Display
void lcd_clear_Display(){
   lcd_gotoxy(0,0);
   lcd_write("                ");
   lcd_gotoxy(0,1);
   lcd_write("                ");
}




