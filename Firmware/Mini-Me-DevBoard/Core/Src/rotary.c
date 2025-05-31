/*
 * rotary.c
 *
 *  Created on: Feb 18, 2025
 *      Author: tiebe
 */

#include "rotary.h"
#include "display.h"
#include "buzzer.h"
#include <stdio.h>

// Global variables
uint8_t lastCLK = 1;
uint8_t menuPosition = 0;
MenuLevel currentMenu = MAIN_MENU;
volatile uint8_t in_debug_mode = 0;
static uint8_t selected_animation = 0;  // Track which animation is selected

// Function to set GPIO pin high for ESP32 (Bottango mode)
void set_esp32_bottango_mode(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);  // PA0 -> ESP32 GPIO13
}

// Function to set GPIO pin low for ESP32 (Animation mode)
void set_esp32_animation_mode(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);  // PA0 -> ESP32 GPIO13
}

void rotary_read(void) {
   static uint8_t lastButtonState = 1;
   uint8_t currentCLK = HAL_GPIO_ReadPin(ROTARY_GPIO_PORT, ROTARY_CLK_PIN);
   uint8_t currentDT = HAL_GPIO_ReadPin(ROTARY_GPIO_PORT, ROTARY_DT_PIN);
   uint8_t currentButtonState = HAL_GPIO_ReadPin(ROTARY_GPIO_PORT, ROTARY_SW_PIN);

   // Handle encoder rotation
   if (currentCLK != lastCLK && currentCLK == 1) {
       if (currentMenu == MAIN_MENU) {
    	   uint8_t oldMenuPosition = menuPosition; // Renamed variable

           if (currentDT != currentCLK) {
               menuPosition = (menuPosition + 1) % MENU_ITEMS_COUNT;
           } else {
               menuPosition = (menuPosition > 0) ? menuPosition - 1 : MENU_ITEMS_COUNT - 1;
           }

           // Play sound if position changed
           if (oldMenuPosition != menuPosition) {
               buzzer_menu_change();
           }

           switch(menuPosition) {
               case UDP:
            	   display_menu_item("UDP");
            	   send_uart_message("UDP_MODE\n");
                   break;
               case BOTTANGO:
            	   display_menu_item("BOTTANGO");
            	   send_uart_message("BOTTANGO_MODE\n");
                   break;
               case ANIMATIES:
            	   display_menu_item("ANIMATIES");
            	   send_uart_message("ANIMATIES_MODE\n");
                   break;
           }
       }
       else if (currentMenu == UDP_SUBMENU) {
           uint8_t oldMenuPosition = menuPosition;

           if (currentDT != currentCLK) {
               menuPosition = (menuPosition + 1) % UDP_ITEMS_COUNT;
           } else {
               menuPosition = (menuPosition > 0) ? menuPosition - 1 : UDP_ITEMS_COUNT - 1;
           }

           // Play sound if position changed
           if (oldMenuPosition != menuPosition) {
               buzzer_menu_change();
           }

           switch(menuPosition) {
               case 0:
                   display_message("DEBUG MODE");
                   break;
               case 1:
                   display_message("SERVO GRADEN");
                   break;
               case 2:
                   display_message("TERUG");
                   break;
           }
       }
       else if (currentMenu == BOTTANGO_SUBMENU) {
           uint8_t oldMenuPosition = menuPosition;

           if (currentDT != currentCLK) {
               menuPosition = (menuPosition + 1) % BOTTANGO_ITEMS_COUNT;
           } else {
               menuPosition = (menuPosition > 0) ? menuPosition - 1 : BOTTANGO_ITEMS_COUNT - 1;
           }

           // Play sound if position changed
           if (oldMenuPosition != menuPosition) {
               buzzer_menu_change();
           }

           switch(menuPosition) {
               case 0:
                   display_message("VERBIND");
                   break;
               case 1:
                   display_message("TERUG");
                   break;
           }
       }
       else if (currentMenu == ANIMATIES_SUBMENU) {
           uint8_t oldMenuPosition = menuPosition;

           if (currentDT != currentCLK) {
               menuPosition = (menuPosition + 1) % ANIMATIES_ITEMS_COUNT;
           } else {
               menuPosition = (menuPosition > 0) ? menuPosition - 1 : ANIMATIES_ITEMS_COUNT - 1;
           }

           // Play sound if position changed
           if (oldMenuPosition != menuPosition) {
               buzzer_menu_change();
           }

           switch(menuPosition) {
               case 0:
                   display_message("ANIMATIE 1");
                   break;
               case 1:
                   display_message("ANIMATIE 2");
                   break;
               case 2:
                   display_message("ANIMATIE 3");
                   break;
               case 3:
                   display_message("STOP ANIMATIE");
                   break;
               case 4:
                   display_message("TERUG");
                   break;
           }
       }
       else if (currentMenu == ANIM_DETAILS_SUBMENU) {
           uint8_t oldMenuPosition = menuPosition;

           if (currentDT != currentCLK) {
               menuPosition = (menuPosition + 1) % ANIM_DETAILS_ITEMS_COUNT;
           } else {
               menuPosition = (menuPosition > 0) ? menuPosition - 1 : ANIM_DETAILS_ITEMS_COUNT - 1;
           }

           // Play sound if position changed
           if (oldMenuPosition != menuPosition) {
               buzzer_menu_change();
           }

           switch(menuPosition) {
               case 0:
                   display_message("SPEEL 1X");
                   break;
               case 1:
                   display_message("SPEEL LOOP");
                   break;
               case 2:
                   display_message("TERUG");
                   break;
           }
       }
   }
   lastCLK = currentCLK;

   // Handle button press (falling edge)
   if(lastButtonState == 1 && currentButtonState == 0) {
       HAL_Delay(50);  // Debounce delay
       currentButtonState = HAL_GPIO_ReadPin(ROTARY_GPIO_PORT, ROTARY_SW_PIN);
       if(currentButtonState == 0) {  // Check if still pressed after delay
           buzzer_menu_select();

           // Button press handling code
           if (currentMenu == MAIN_MENU) {
               switch(menuPosition) {
                   case UDP:
                       currentMenu = UDP_SUBMENU;
                       menuPosition = 0;
                       display_message("DEBUG MODE");
                       break;
                   case BOTTANGO:
                       currentMenu = BOTTANGO_SUBMENU;
                       menuPosition = 0;
                       display_message("VERBIND");
                       break;
                   case ANIMATIES:
                       // Set ESP32 to animation mode when entering animation menu
                       set_esp32_animation_mode();
                       currentMenu = ANIMATIES_SUBMENU;
                       menuPosition = 0;
                       display_message("ANIMATIE 1");
                       break;
               }
           }
           else if (currentMenu == UDP_SUBMENU) {
               if (menuPosition == UDP_ITEMS_COUNT - 1) {  // Back option
                   currentMenu = MAIN_MENU;
                   menuPosition = UDP;
                   display_menu_item("UDP");
                   buzzer_menu_back();
               } else {
                   switch(menuPosition) {
                       case 0:
                           debug_mode();
                           break;
                       case 1:
                           servo_control();
                           break;
                   }
               }
           }
           else if (currentMenu == BOTTANGO_SUBMENU) {
               if (menuPosition == BOTTANGO_ITEMS_COUNT - 1) {  // Back option
                   currentMenu = MAIN_MENU;
                   menuPosition = BOTTANGO;
                   display_menu_item("BOTTANGO");
                   buzzer_menu_back();
               } else {
                   switch(menuPosition) {
                       case 0:
                           connect_bottango();
                           break;
                   }
               }
           }
           else if (currentMenu == ANIMATIES_SUBMENU) {
               if (menuPosition == ANIMATIES_ITEMS_COUNT - 1) {  // Back option
                   currentMenu = MAIN_MENU;
                   menuPosition = ANIMATIES;
                   display_menu_item("ANIMATIES");
                   buzzer_menu_back();
               } else {
                   switch(menuPosition) {
                       case 0:  // Animatie 1
                           selected_animation = 0;  // Store which animation was selected
                           show_animation_details(0);
                           break;
                       case 1:  // Animatie 2
                           selected_animation = 1;  // Store which animation was selected
                           show_animation_details(1);
                           break;
                       case 2:  // Animatie 3
                           selected_animation = 2;  // Store which animation was selected
                           show_animation_details(2);
                           break;
                       case 3:  // Stop animatie
                           stop_animation();
                           break;
                   }
               }
           }
           else if (currentMenu == ANIM_DETAILS_SUBMENU) {
               if (menuPosition == ANIM_DETAILS_ITEMS_COUNT - 1) {  // Back option
                   currentMenu = ANIMATIES_SUBMENU;
                   menuPosition = selected_animation;  // Return to the animation that was selected

                   // Update display based on which animation we're going back to
                   switch(menuPosition) {
                       case 0:
                           display_message("ANIMATIE 1");
                           break;
                       case 1:
                           display_message("ANIMATIE 2");
                           break;
                       case 2:
                           display_message("ANIMATIE 3");
                           break;
                   }
                   buzzer_menu_back();
               } else {
                   switch(menuPosition) {
                       case 0:  // Speel 1x
                           switch(selected_animation) {
                               case 0:
                                   play_animation1();
                                   break;
                               case 1:
                                   play_animation2();
                                   break;
                               case 2:
                                   play_animation3();
                                   break;
                           }
                           // Return to animation menu after starting
                           currentMenu = ANIMATIES_SUBMENU;
                           menuPosition = selected_animation;
                           break;
                       case 1:  // Speel in loop
                           switch(selected_animation) {
                               case 0:
                                   play_animation1_loop();
                                   break;
                               case 1:
                                   play_animation2_loop();
                                   break;
                               case 2:
                                   play_animation3_loop();
                                   break;
                           }
                           // Return to animation menu after starting
                           currentMenu = ANIMATIES_SUBMENU;
                           menuPosition = selected_animation;
                           break;
                   }
               }
           }
       }
   }

   lastButtonState = currentButtonState;
}

void debug_mode(void) {
    in_debug_mode = 1;
    display_message("DEBUG MODE ON");

    // Reset the button state to avoid immediate exit
    HAL_Delay(500);  // Debounce delay

    while(in_debug_mode) {
        // Read rotary encoder for exit condition
        uint8_t currentButtonState = HAL_GPIO_ReadPin(ROTARY_GPIO_PORT, ROTARY_SW_PIN);

        // Check for long press to exit (1 second)
        if(currentButtonState == 0) {  // Button is pressed
            HAL_Delay(1000);  // Wait for 1 second
            currentButtonState = HAL_GPIO_ReadPin(ROTARY_GPIO_PORT, ROTARY_SW_PIN);
            if(currentButtonState == 0) {  // Still pressed after 1 second
                exit_debug_mode();
                break;
            }
        }

        // Check if there's a message to process
        extern volatile uint8_t message_received;
        if(message_received) {
            ProcessJsonMessage();
        }
    }
}

void exit_debug_mode(void) {
    in_debug_mode = 0;
    display_message("DEBUG MODE OFF");
    HAL_Delay(500);

    // Return to UDP submenu
    currentMenu = UDP_SUBMENU;
    menuPosition = 0;
    display_message("DEBUG MODE");
}

void play_animation1(void) {
   set_esp32_animation_mode();
   display_message("ANIM 1 SPELEN");
   // Send command to play animation 1
   send_uart_message("PLAY_ANIMATION:0\n");
}

void play_animation2(void) {
   set_esp32_animation_mode();
   display_message("ANIM 2 SPELEN");
   // Send command to play animation 2
   send_uart_message("PLAY_ANIMATION:1\n");
}

void play_animation3(void) {
   set_esp32_animation_mode();
   display_message("ANIM 3 SPELEN");
   // Send command to play animation 3
   send_uart_message("PLAY_ANIMATION:2\n");
}

// Functions to play animations in loop mode
void play_animation1_loop(void) {
   set_esp32_animation_mode();
   display_message("ANIM 1 LOOPING");
   // Send command to play animation 1 in loop mode
   send_uart_message("LOOP_ANIMATION:0\n");
}

void play_animation2_loop(void) {
   set_esp32_animation_mode();
   display_message("ANIM 2 LOOPING");
   // Send command to play animation 2 in loop mode
   send_uart_message("LOOP_ANIMATION:1\n");
}

void play_animation3_loop(void) {
   set_esp32_animation_mode();
   display_message("ANIM 3 LOOPING");
   // Send command to play animation 3 in loop mode
   send_uart_message("LOOP_ANIMATION:2\n");
}

// Function to stop playing an animation
void stop_animation(void) {
   display_message("ANIM GESTOPT");
   // Send command to stop the current animation
   send_uart_message("STOP_ANIMATION\n");
}

void show_animation_details(uint8_t animation_index) {
    selected_animation = animation_index;  // Store which animation is selected

    currentMenu = ANIM_DETAILS_SUBMENU;
    menuPosition = 0;  // Start at the first option
    display_message("SPEEL 1X");
}

void servo_control(void) {
   // Implement servo control functionality
   display_message("SERVO CONTROL");
   HAL_Delay(1000);
}

void connect_bottango(void) {
   // Set GPIO high to signal ESP32 to enter Bottango mode
   set_esp32_bottango_mode();
   display_message("VERBONDEN MET BOTTANGO");
   send_uart_message("BOTTANGO_CONNECTED\n");
   HAL_Delay(1000);
}
