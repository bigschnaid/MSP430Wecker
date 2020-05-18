#include <msp430.h>
#include <stdint.h>
#include "lcd.h"
#include "time.h"
#include "button.h"
#include "menue.h"

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    lcd_init();
    button_init();
    setTimerA0Settings();


    __enable_interrupt();


   while (1){
       switch(menue_option){
       case 0:
           menue_refresh_display();
           __low_power_mode_3();
           break;
       case 1:
           __low_power_mode_3();
           break;
       case 2:
           break;
       case 3:
           break;
       }
    }
}

#pragma vector= TIMER0_A0_VECTOR
__interrupt void TIMERA0_ISR() {
    CCR0 += clockA;
    countTime_and_Date();
    if (menue_option==1){
        lcd_writeTime_and_Date();
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR() {
    if (P1IFG & BIT4) {
        P1IFG &= ~BIT4;
        __low_power_mode_off_on_exit();
        menue_count_up();
        __delay_cycles(50000L);
        }
    if (P1IFG & BIT5) {
        P1IFG &= ~BIT5;
        __low_power_mode_off_on_exit();
        menue_count_down();
        __delay_cycles(50000L);
        }

    if (P1IFG & BIT6) {
        P1IFG &= ~BIT6;
        __low_power_mode_off_on_exit();
        menue_select();
        __delay_cycles(50000L);
        }
    if (P1IFG & BIT7) {
        P1IFG &= ~BIT7;
        __low_power_mode_off_on_exit();
        menue_back();
        __delay_cycles(50000L);
        }
}
