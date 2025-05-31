/*
 * buzzer.c
 *
 *  Created on: May 14, 2025
 *      Author: tiebe
 */
#include "buzzer.h"
#include "main.h"

// Genereer een toon met bepaalde frequentie en duur
void buzzer_beep(uint16_t frequency, uint16_t duration) {
    uint32_t delay_time = 500000 / frequency; // Halve periode in microseconden
    uint32_t num_cycles = (duration * frequency) / 1000;

    for (uint32_t i = 0; i < num_cycles; i++) {
        HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_PIN, GPIO_PIN_SET);
        for (volatile uint32_t j = 0; j < delay_time; j++) {
            __NOP(); // Kleine vertraging
        }

        HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_PIN, GPIO_PIN_RESET);
        for (volatile uint32_t j = 0; j < delay_time; j++) {
            __NOP(); // Kleine vertraging
        }
    }
}

// Geluid bij menu verandering (korte piep)
void buzzer_menu_change(void) {
    buzzer_beep(300, 50); // 2000 Hz, 50 ms
}

// Geluid bij menu selectie (dubbele piep)
void buzzer_menu_select(void) {
    buzzer_beep(2500, 50); // 2500 Hz, 50 ms
    HAL_Delay(50);
    buzzer_beep(3000, 50); // 3000 Hz, 50 ms
}

// Geluid bij teruggaan in menu (dalende toon)
void buzzer_menu_back(void) {
    buzzer_beep(2000, 50); // 2000 Hz, 50 ms
    HAL_Delay(20);
    buzzer_beep(1500, 50); // 1500 Hz, 50 ms
}
