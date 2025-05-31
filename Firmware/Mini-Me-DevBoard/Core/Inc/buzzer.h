/*
 * buzzer.h
 *
 *  Created on: May 14, 2025
 *      Author: tiebe
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"
#include <stdint.h>

// Buzzer op PD3
#define BUZZER_PIN GPIO_PIN_3
#define BUZZER_GPIO_PORT GPIOD

// Functie prototypes
void buzzer_init(void);
void buzzer_beep(uint16_t frequency, uint16_t duration);
void buzzer_menu_change(void);
void buzzer_menu_select(void);
void buzzer_menu_back(void);

#endif /* INC_BUZZER_H_ */
