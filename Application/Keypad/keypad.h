/*
 * keypad.h
 *
 *  Created on: Mar 12, 2024
 *      Author: phamh
 */

#ifndef KEYPAD_KEYPAD_H_
#define KEYPAD_KEYPAD_H_

#include "main.h"

//Keypad row & column
#define KEYPAD_ROW 4
#define KEYPAD_COL 4

void keypad_init();

void keypad_handle();


#endif /* KEYPAD_KEYPAD_H_ */
