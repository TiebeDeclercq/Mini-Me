/*
 * display.h
 *
 *  Created on: Feb 18, 2025
 *      Author: tiebe
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "main.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"

void display_init(void);
void display_message(const char* str);
void display_menu_item(const char* item);


#endif /* INC_DISPLAY_H_ */
