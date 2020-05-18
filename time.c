/*
 * time.c
 *
 *  Created on: 14.05.2020
 *      Author: adrianschmidt
 */

#include "time.h"
#include <msp430.h>
#include <stdint.h>

const uint32_t clockA=0x8000;
const uint32_t clockA1=0x8000;
uint8_t seconds_einer=48;
uint8_t seconds_zehner=48;
uint8_t minutes_einer=48;
uint8_t minutes_zehner=48;
uint8_t hours_einer=48;
uint8_t hours_zehner=48;
uint8_t days_einer='5';
uint8_t days_zehner='1';
uint8_t month_einer='5';
uint8_t month_zehner='0';
uint8_t years_einer='0';
uint8_t years_zehner='2';
uint8_t years_hunderter='0';
uint8_t years_tausender='2';


void setTimerA0Settings(){
    CCTL0 = CCIE;
    TACTL = TASSEL_1 + MC_2 + TACLR;
    CCR0=clockA;
}

void countTime_and_Date(){
        if(seconds_einer<=56){
            seconds_einer++;
        }
        else{
            seconds_einer=48;
            seconds_zehner++;
        }

        if(seconds_zehner==54){
            seconds_zehner=48;
            minutes_einer++;
        }

        if (minutes_einer==56){
            minutes_einer=48;
            minutes_zehner++;
        }

        if (minutes_zehner==54){
            minutes_zehner=48;
            hours_einer++;
        }

        if (hours_einer==54){
            minutes_einer=48;
            hours_zehner++;
         }

        if (hours_einer == 52 && hours_zehner==50){
           hours_zehner=48;
           hours_einer=48;
           days_einer++;
         }

        //Datum
        if (days_einer==54){
            days_einer=48;
            days_zehner++;
         }

        if (days_zehner==51&&days_einer==49){
             days_zehner=48;
             days_einer=48;
             month_einer++;
          }

        if (month_einer == 54){
             month_einer=48;
             month_zehner++;
          }

        if (month_zehner==49&&days_einer==50){
             years_einer++;
             month_einer=48;
             month_zehner=48;
        }

        if (years_einer == 54){
             years_einer=48;
             years_zehner++;
        }

        if (years_zehner == 54){
            years_zehner=48;
            years_hunderter++;
        }

        if (years_hunderter == 54){
           years_hunderter=48;
           years_tausender++;
        }
}

