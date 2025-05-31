/*
 * display.c
 *
 *  Created on: Feb 18, 2025
 *      Author: tiebe
 */

#include "display.h"

void display_init(void) {
    ssd1306_Init();
    HAL_Delay(100);
}

void display_message(const char* str) {
    ssd1306_Fill(Black);
    int x = 0;
    int y = 0;
    int charWidth = 6;
    int lineHeight = 8;
    int maxWidth = 128;
    int maxLines = 8;
    int currentLine = 0;

    for(int i = 0; str[i] != '\0' && currentLine < maxLines; i++) {
        if(x + charWidth > maxWidth) {
            x = 0;
            y += lineHeight;
            currentLine++;
        }

        if(currentLine < maxLines) {
            ssd1306_SetCursor(x, y);
            char currentChar[2] = {str[i], '\0'};
            ssd1306_WriteString(currentChar, Font_6x8, White);
            x += charWidth;
        }
    }
    ssd1306_UpdateScreen();
}

void display_menu_item(const char* item) {
    ssd1306_Fill(Black);

    // Bereken de lengte van de string
    int stringLength = 0;
    while(item[stringLength] != '\0') {
        stringLength++;
    }

    // Bereken de breedte van de tekst in pixels (Font_11x18 is 11 pixels breed per karakter)
    int textWidth = stringLength * 11;

    // Bereken x-positie om horizontaal te centreren (scherm is 128 pixels breed)
    int x = (128 - textWidth) / 2;
    if(x < 0) x = 0; // Voorkom negatieve x-waarden

    // Bereken y-positie om verticaal te centreren (scherm is 64 pixels hoog, lettertype is 18 pixels hoog)
    int y = (64 - 18) / 2;

    ssd1306_SetCursor(x, y);
    ssd1306_WriteString(item, Font_11x18, White);
    ssd1306_UpdateScreen();
}
