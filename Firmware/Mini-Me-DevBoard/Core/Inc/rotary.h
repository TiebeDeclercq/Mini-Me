/*
 * rotary.h
 *
 *  Created on: Feb 18, 2025
 *      Author: tiebe
 */

#ifndef INC_ROTARY_H_
#define INC_ROTARY_H_

#include "main.h"

// Pin definitions
#define ROTARY_CLK_PIN GPIO_PIN_3
#define ROTARY_DT_PIN GPIO_PIN_4
#define ROTARY_SW_PIN GPIO_PIN_5
#define ROTARY_GPIO_PORT GPIOB

// UDP submenu items
#define UDP_ITEMS_COUNT 3

// Bottango submenu items
#define BOTTANGO_ITEMS_COUNT 2

// Animaties submenu items - increased to 5 for extra options
#define ANIMATIES_ITEMS_COUNT 5

// Animation details submenu items
#define ANIM_DETAILS_ITEMS_COUNT 3

// Main menu items
typedef enum {
    UDP,
    BOTTANGO,
    ANIMATIES,
    MENU_ITEMS_COUNT
} MainMenuItem;

typedef enum {
    MAIN_MENU,
    UDP_SUBMENU,
    BOTTANGO_SUBMENU,
    ANIMATIES_SUBMENU,
    ANIM_DETAILS_SUBMENU  // New submenu for animation details
} MenuLevel;

extern volatile uint8_t in_debug_mode;
void exit_debug_mode(void);
void ProcessJsonMessage(void);

// Function declarations
void rotary_read(void);

// ESP32 communication functions
void set_esp32_bottango_mode(void);
void set_esp32_animation_mode(void);

// Menu action functions
void debug_mode(void);
void servo_control(void);
void connect_bottango(void);

// Animation functions
void play_animation1(void);
void play_animation2(void);
void play_animation3(void);
void play_animation1_loop(void);
void play_animation2_loop(void);
void play_animation3_loop(void);
void stop_animation(void);

void show_animation_details(uint8_t animation_index);

// External variables
extern uint8_t lastCLK;
extern uint8_t menuPosition;

#endif /* INC_ROTARY_H_ */
