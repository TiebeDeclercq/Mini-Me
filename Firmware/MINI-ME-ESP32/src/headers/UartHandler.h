#include <Arduino.h>

#define MODE_NORMAL 0    // UDP mode
#define MODE_BOTTANGO 1  // Bottango Live
#define MODE_ANIMATION 2 // SD card animation

void setupUart();
void processCommand(String command);
void serialEvent2();
void stelModusIn(int mode);
int getModus();