/*
 * menue.h
 *
 *  Created on: 17.05.2020
 *      Author: adrianschmidt
 */
#include <stdint.h>
#ifndef MENUE_H_
#define MENUE_H_

#define MENUE_OPTION1 "MENUE1"
#define MENUE_OPTION2 "MENUE2"
#define MENUE_OPTION3 "MENUE3"
#define MENUE_OPTION4 "MENUE4"

extern uint8_t menue_counter;
extern uint8_t menue_option;

void menue_print_options(const char *str1, const char *str2);
void menue_refresh_display();
void menue_count_up();
void menue_count_down();
void menue_select();
void menue_back();
#endif /* MENUE_H_ */
