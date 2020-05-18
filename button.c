/*
 * button.c
 *
 *  Created on: 16.05.2020
 *      Author: adrianschmidt
 */
#include "button.h"
#include <msp430.h>
void button_init(){
    P1DIR &= ~(BIT4+BIT5+BIT6+BIT7);
    P1IES |= BIT4 +BIT5+BIT6+BIT7;
    P1IFG &= ~(BIT4 +BIT5+BIT6+BIT7);
    P1IE |= BIT4 +BIT5 +BIT6+BIT7;
}


