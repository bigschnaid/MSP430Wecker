/*
 * time.h
 *
 *  Created on: 14.05.2020
 *      Author: adrianschmidt
 */
#include <stdint.h>

#ifndef TIME_H_
#define TIME_H_

extern const uint32_t clockA;
extern const uint32_t clockA1;
extern uint8_t seconds_einer;
extern uint8_t seconds_zehner;
extern uint8_t minutes_einer;
extern uint8_t minutes_zehner;
extern uint8_t hours_einer;
extern uint8_t hours_zehner;
extern uint8_t days_einer;
extern uint8_t days_zehner;
extern uint8_t month_einer;
extern uint8_t month_zehner;
extern uint8_t years_einer;
extern uint8_t years_zehner;
extern uint8_t years_hunderter;
extern uint8_t years_tausender;


void setTimerA0Settings();
void countTime_and_Date();
#endif /* TIME_H_ */
